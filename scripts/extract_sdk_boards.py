#!/usr/bin/env python3
"""Extract and classify boards added between consecutive mikroSDK releases.

Given a current release such as ``mikroSDK-2.19.0``, the script:

1. Finds the highest semantic-versioned ``mikroSDK-X.Y.Z`` tag below it.
2. Reads the release date of that previous tag and the current tag.
3. Reads the previous and current version changelog indexes as they exist in
   the current tag.
4. Processes every linked ``new_hw/YYYY-MM-DD.md`` file where:

       previous_release_date < file_date <= current_release_date

5. Downloads and extracts the NECTO development database (or uses an explicitly
   supplied database file).
6. Looks up each board by ``Boards.name`` and classifies it using
   ``Boards.mikrobus_count``.
7. Determines SDK support from the board's devices:
   - When ``Boards.soldered_device`` is set, that ``Devices.uid`` is checked.
   - Otherwise, unique devices linked through ``BoardToDevice`` are checked.
   A board has SDK support when at least one checked device has
   ``Devices.sdk_support = 1``.
8. Marks a board as EmbeddedWiki eligible only when it has both at least one
   mikroBUS socket and device-confirmed mikroSDK support. Every other board is
   preserved and reported with the reason it is not eligible.

Changelog files are read directly with ``git show``. The working tree is never
changed. Downloaded database files are cached between invocations.
"""

from __future__ import annotations

import argparse
import json
import posixpath
import re
import shutil
import sqlite3
import subprocess
import sys
import urllib.error
import urllib.request
from dataclasses import asdict, dataclass, replace
from datetime import date
from pathlib import Path
from typing import Iterable


DEFAULT_DATABASE_URL = (
    "https://github.com/MikroElektronika/core_packages/releases/download/"
    "v2.0.0/database_dev.7z"
)
DEFAULT_DATABASE_CACHE_DIR = Path(".cache/sdk-board-support/database")
DATABASE_ARCHIVE_NAME = "database_dev.7z"
DATABASE_RELATIVE_PATH = Path("necto_db.db")

RELEASE_DATE_RE = re.compile(
    r"^\s*[-+*]\s*released\s*:\s*(\d{4}-\d{2}-\d{2})\s*$",
    re.IGNORECASE | re.MULTILINE,
)
HEADING_RE = re.compile(r"^(#{1,6})\s+(.+?)\s*$", re.MULTILINE)
MARKDOWN_LINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")
BULLET_RE = re.compile(r"^\s*[-+*]\s+(.+?)\s*$")
DATE_RE = re.compile(r"^\d{4}-\d{2}-\d{2}$")
TAG_RE = re.compile(r"^mikroSDK-(\d+)\.(\d+)\.(\d+)$")
HTML_TAG_RE = re.compile(r"<[^>]+>")


class ExtractionError(RuntimeError):
    """Raised when changelog or database processing cannot continue safely."""


@dataclass(frozen=True)
class Board:
    name: str
    url: str | None
    added_date: str
    source_file: str
    database_match: bool = False
    board_uid: str | None = None
    mikrobus_count: int | None = None
    has_mikrobus: bool | None = None
    soldered_device: str | None = None
    sdk_support_source: str | None = None
    checked_device_uids: tuple[str, ...] = ()
    sdk_supported_device_uids: tuple[str, ...] = ()
    missing_device_uids: tuple[str, ...] = ()
    has_sdk_support: bool | None = None
    embedded_wiki_eligible: bool = False
    eligibility_note: str | None = None


@dataclass(frozen=True)
class HardwareChangelog:
    date: str
    path: str
    board_count: int


@dataclass(frozen=True)
class DatabaseMetadata:
    source_url: str
    database_file: str
    boards_table: str
    board_name_column: str
    board_uid_column: str
    mikrobus_count_column: str
    soldered_device_column: str
    devices_table: str
    device_uid_column: str
    device_sdk_support_column: str
    board_to_device_table: str
    board_to_device_board_uid_column: str
    board_to_device_device_uid_column: str
    matched_boards: int
    unmatched_boards: int
    sdk_supported_boards: int
    sdk_unsupported_boards: int
    embedded_wiki_eligible_boards: int
    other_boards: int


@dataclass(frozen=True)
class ReleaseBoards:
    sdk_version: str
    tag: str
    release_date: str
    release_changelog: str
    previous_sdk_version: str
    previous_tag: str
    previous_release_date: str
    previous_release_changelog: str
    date_range: str
    hardware_changelogs: list[HardwareChangelog]
    database: DatabaseMetadata
    boards: list[Board]
    embedded_wiki_eligible_boards: list[Board]
    other_boards: list[Board]


def run_git(repo: Path, *args: str) -> str:
    command = ["git", "-C", str(repo), *args]
    try:
        result = subprocess.run(
            command,
            check=True,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
    except FileNotFoundError as exc:
        raise ExtractionError("git is not installed or is not available in PATH") from exc
    except subprocess.CalledProcessError as exc:
        detail = exc.stderr.strip() or exc.stdout.strip() or "unknown Git error"
        raise ExtractionError(f"Git command failed: {' '.join(command)}\n{detail}") from exc
    return result.stdout


def normalize_version(raw: str) -> str:
    version = raw.strip()
    if version.startswith("mikroSDK-"):
        version = version.removeprefix("mikroSDK-")
    version = version.removeprefix("v")

    if not re.fullmatch(r"\d+\.\d+\.\d+", version):
        raise ExtractionError(
            f"Invalid version '{raw}'. Expected a value such as 2.19.0, "
            "v2.19.0, or mikroSDK-2.19.0."
        )
    return version


def version_tuple(version: str) -> tuple[int, int, int]:
    return tuple(int(part) for part in version.split("."))  # type: ignore[return-value]


def find_previous_version(repo: Path, current_version: str) -> str:
    current = version_tuple(current_version)
    candidates: list[tuple[tuple[int, int, int], str]] = []

    for tag in run_git(repo, "tag", "--list", "mikroSDK-*").splitlines():
        match = TAG_RE.fullmatch(tag.strip())
        if not match:
            continue
        candidate_tuple = tuple(int(value) for value in match.groups())
        if candidate_tuple < current:
            candidates.append((candidate_tuple, ".".join(match.groups())))

    if not candidates:
        raise ExtractionError(
            f"No earlier mikroSDK-X.Y.Z tag was found before mikroSDK-{current_version}"
        )

    return max(candidates, key=lambda item: item[0])[1]


def clean_heading(text: str) -> str:
    text = HTML_TAG_RE.sub("", text)
    text = text.replace("`", "").replace("*", "").strip()
    return re.sub(r"\s+", " ", text).upper()


def extract_section(markdown: str, title: str) -> str:
    headings = list(HEADING_RE.finditer(markdown))
    wanted = title.strip().upper()

    for index, heading in enumerate(headings):
        if clean_heading(heading.group(2)) != wanted:
            continue

        level = len(heading.group(1))
        section_start = heading.end()
        section_end = len(markdown)

        for following in headings[index + 1 :]:
            if len(following.group(1)) <= level:
                section_end = following.start()
                break

        return markdown[section_start:section_end]

    raise ExtractionError(f"Section '{title}' was not found")


def get_release_date(markdown: str) -> str:
    match = RELEASE_DATE_RE.search(markdown)
    if not match:
        raise ExtractionError("The release changelog has no '+ released: YYYY-MM-DD' entry")

    value = match.group(1)
    try:
        date.fromisoformat(value)
    except ValueError as exc:
        raise ExtractionError(f"Invalid release date '{value}'") from exc
    return value


def get_dated_hardware_links(section: str) -> list[tuple[str, str]]:
    links: list[tuple[str, str]] = []
    for label, target in MARKDOWN_LINK_RE.findall(section):
        label = label.strip().strip("`*")
        if not DATE_RE.fullmatch(label):
            continue
        try:
            date.fromisoformat(label)
        except ValueError:
            continue
        links.append((label, target.strip()))
    return links


def resolve_git_path(parent_file: str, linked_file: str) -> str:
    if re.match(r"^[a-zA-Z][a-zA-Z0-9+.-]*://", linked_file):
        raise ExtractionError(f"Expected a repository-relative file, got URL: {linked_file}")

    linked_file = linked_file.split("#", 1)[0]
    resolved = posixpath.normpath(posixpath.join(posixpath.dirname(parent_file), linked_file))
    if resolved == ".." or resolved.startswith("../"):
        raise ExtractionError(f"Linked file resolves outside the repository: {linked_file}")
    return resolved


def strip_markdown_emphasis(text: str) -> str:
    text = text.strip()
    while len(text) >= 2:
        changed = False
        for marker in ("**", "__", "*", "_", "`"):
            if text.startswith(marker) and text.endswith(marker) and len(text) > 2 * len(marker):
                text = text[len(marker) : -len(marker)].strip()
                changed = True
                break
        if not changed:
            break
    return text


def parse_boards(section: str, added_date: str, source_file: str) -> list[Board]:
    boards: list[Board] = []
    seen: set[tuple[str, str | None]] = set()

    for line in section.splitlines():
        bullet = BULLET_RE.match(line)
        if not bullet:
            continue

        item = bullet.group(1).strip()
        links = MARKDOWN_LINK_RE.findall(item)

        if links:
            for name, url in links:
                board = Board(
                    name=strip_markdown_emphasis(name),
                    url=url.strip(),
                    added_date=added_date,
                    source_file=source_file,
                )
                key = (board.name.casefold(), board.url)
                if key not in seen:
                    boards.append(board)
                    seen.add(key)
            continue

        name = strip_markdown_emphasis(item)
        if name:
            board = Board(
                name=name,
                url=None,
                added_date=added_date,
                source_file=source_file,
            )
            key = (board.name.casefold(), board.url)
            if key not in seen:
                boards.append(board)
                seen.add(key)

    return boards


def read_tag_file(repo: Path, tag: str, path: str) -> str:
    try:
        return run_git(repo, "show", f"{tag}:{path}")
    except ExtractionError as exc:
        raise ExtractionError(f"Cannot read '{path}' from tag '{tag}'.\n{exc}") from exc


def verify_tag(repo: Path, tag: str) -> None:
    try:
        run_git(repo, "cat-file", "-e", f"{tag}^{{commit}}")
    except ExtractionError as exc:
        raise ExtractionError(
            f"Tag '{tag}' was not found. Fetch tags first with 'git fetch --tags'.\n{exc}"
        ) from exc


def validate_hardware_file_heading(markdown: str, expected_date: str, path: str) -> None:
    file_heading = next(
        (
            clean_heading(match.group(2))
            for match in HEADING_RE.finditer(markdown)
            if len(match.group(1)) == 1
        ),
        "",
    )
    if file_heading and file_heading != expected_date:
        raise ExtractionError(
            f"Hardware file '{path}' is linked as '{expected_date}', "
            f"but its H1 heading is '{file_heading}'"
        )


def collect_interval_links(
    repo: Path,
    current_tag: str,
    changelog_paths: Iterable[str],
    previous_release_date: str,
    current_release_date: str,
) -> list[tuple[str, str]]:
    lower = date.fromisoformat(previous_release_date)
    upper = date.fromisoformat(current_release_date)
    selected: dict[str, str] = {}

    if upper <= lower:
        raise ExtractionError(
            f"Current release date {current_release_date} must be later than "
            f"previous release date {previous_release_date}"
        )

    for changelog_path in changelog_paths:
        markdown = read_tag_file(repo, current_tag, changelog_path)
        section = extract_section(markdown, "NEW HARDWARE")
        for link_date, linked_file in get_dated_hardware_links(section):
            parsed_date = date.fromisoformat(link_date)
            if not (lower < parsed_date <= upper):
                continue

            resolved = resolve_git_path(changelog_path, linked_file)
            existing_date = selected.get(resolved)
            if existing_date is not None and existing_date != link_date:
                raise ExtractionError(
                    f"Hardware file '{resolved}' is linked using conflicting dates: "
                    f"'{existing_date}' and '{link_date}'"
                )
            selected[resolved] = link_date

    return sorted(
        ((link_date, path) for path, link_date in selected.items()),
        key=lambda item: (date.fromisoformat(item[0]), item[1]),
    )


def download_database_archive(url: str, destination: Path, refresh: bool) -> None:
    if destination.is_file() and destination.stat().st_size > 0 and not refresh:
        return

    destination.parent.mkdir(parents=True, exist_ok=True)
    temporary = destination.with_suffix(destination.suffix + ".part")
    temporary.unlink(missing_ok=True)

    request = urllib.request.Request(
        url,
        headers={
            "User-Agent": "mikroSDK-board-support-extractor/1.0",
            "Accept": "application/octet-stream",
        },
    )

    try:
        with urllib.request.urlopen(request, timeout=180) as response, temporary.open("wb") as output:
            shutil.copyfileobj(response, output)
    except (urllib.error.URLError, urllib.error.HTTPError, TimeoutError, OSError) as exc:
        temporary.unlink(missing_ok=True)
        raise ExtractionError(f"Failed to download database archive from '{url}': {exc}") from exc

    if not temporary.is_file() or temporary.stat().st_size == 0:
        temporary.unlink(missing_ok=True)
        raise ExtractionError(f"Downloaded database archive from '{url}' is empty")

    temporary.replace(destination)


def extract_database_archive(archive: Path, cache_dir: Path, refresh: bool) -> Path:
    expected_database = cache_dir / DATABASE_RELATIVE_PATH

    if expected_database.is_file() and expected_database.stat().st_size > 0 and not refresh:
        return expected_database

    if refresh:
        shutil.rmtree(cache_dir / DATABASE_RELATIVE_PATH.parent, ignore_errors=True)

    cache_dir.mkdir(parents=True, exist_ok=True)

    extraction_error: Exception | None = None
    try:
        import py7zr  # type: ignore[import-not-found]

        with py7zr.SevenZipFile(archive, mode="r") as archive_file:
            archive_file.extractall(path=cache_dir)
    except ImportError as exc:
        extraction_error = exc
    except Exception as exc:  # py7zr exposes several archive-specific exceptions
        raise ExtractionError(f"Failed to extract '{archive}' with py7zr: {exc}") from exc

    if extraction_error is not None:
        executable = shutil.which("7z") or shutil.which("7za")
        if not executable:
            raise ExtractionError(
                "Cannot extract the database archive. Install py7zr "
                "('python3 -m pip install py7zr') or install 7z/p7zip."
            ) from extraction_error

        command = [executable, "x", "-y", f"-o{cache_dir}", str(archive)]
        try:
            subprocess.run(
                command,
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )
        except subprocess.CalledProcessError as exc:
            detail = exc.stderr.strip() or exc.stdout.strip() or "unknown 7z error"
            raise ExtractionError(
                f"Failed to extract database archive with {' '.join(command)}\n{detail}"
            ) from exc

    if not expected_database.is_file() or expected_database.stat().st_size == 0:
        raise ExtractionError(
            f"Archive extraction completed, but '{expected_database}' was not found"
        )

    return expected_database


def prepare_database(
    database_url: str,
    cache_dir: Path,
    database_path: Path | None,
    refresh: bool,
) -> Path:
    if database_path is not None:
        resolved = database_path.expanduser().resolve()
        if not resolved.is_file():
            raise ExtractionError(f"Database file does not exist: {resolved}")
        return resolved

    resolved_cache = cache_dir.expanduser().resolve()
    archive = resolved_cache / DATABASE_ARCHIVE_NAME
    database = resolved_cache / DATABASE_RELATIVE_PATH

    if refresh or not database.is_file() or database.stat().st_size == 0:
        download_database_archive(database_url, archive, refresh=refresh)
        database = extract_database_archive(archive, resolved_cache, refresh=refresh)

    return database


def quote_identifier(identifier: str) -> str:
    return '"' + identifier.replace('"', '""') + '"'


def resolve_database_schema(
    connection: sqlite3.Connection,
) -> tuple[str, str, str, str, str, str, str, str, str, str, str]:
    def find_table(expected_name: str) -> str:
        row = connection.execute(
            "SELECT name FROM sqlite_master "
            "WHERE type = 'table' AND lower(name) = lower(?)",
            (expected_name,),
        ).fetchone()
        if row is None:
            raise ExtractionError(f"Database table '{expected_name}' was not found")
        return str(row[0])

    def find_columns(table_name: str, required: tuple[str, ...]) -> dict[str, str]:
        rows = connection.execute(
            f"PRAGMA table_info({quote_identifier(table_name)})"
        ).fetchall()
        by_lower_name = {str(row[1]).casefold(): str(row[1]) for row in rows}
        missing = [name for name in required if name.casefold() not in by_lower_name]
        if missing:
            available = ", ".join(sorted(by_lower_name.values()))
            raise ExtractionError(
                f"Table '{table_name}' must contain columns: {', '.join(required)}. "
                f"Missing: {', '.join(missing)}. "
                f"Available columns: {available or '(none)'}"
            )
        return by_lower_name

    boards_table = find_table("Boards")
    boards_columns = find_columns(
        boards_table,
        ("name", "uid", "mikrobus_count", "soldered_device"),
    )

    devices_table = find_table("Devices")
    devices_columns = find_columns(
        devices_table,
        ("uid", "sdk_support"),
    )

    board_to_device_table = find_table("BoardToDevice")
    board_to_device_columns = find_columns(
        board_to_device_table,
        ("board_uid", "device_uid"),
    )

    return (
        boards_table,
        boards_columns["name"],
        boards_columns["uid"],
        boards_columns["mikrobus_count"],
        boards_columns["soldered_device"],
        devices_table,
        devices_columns["uid"],
        devices_columns["sdk_support"],
        board_to_device_table,
        board_to_device_columns["board_uid"],
        board_to_device_columns["device_uid"],
    )


def normalize_nullable_uid(raw_value: object) -> str | None:
    if raw_value is None:
        return None
    value = str(raw_value).strip()
    return value or None


def normalize_sdk_support(raw_value: object, device_uid: str) -> bool:
    if raw_value is None or str(raw_value).strip() == "":
        return False

    try:
        value = int(raw_value)
    except (TypeError, ValueError) as exc:
        raise ExtractionError(
            f"Device '{device_uid}' has invalid sdk_support value '{raw_value}'"
        ) from exc

    if value not in (0, 1):
        raise ExtractionError(
            f"Device '{device_uid}' has unsupported sdk_support value {value}; "
            "expected 0 or 1"
        )
    return value == 1


def classify_boards_with_database(
    boards: list[Board],
    database_path: Path,
    database_url: str,
) -> tuple[
    list[Board],
    list[Board],
    list[Board],
    DatabaseMetadata,
]:
    try:
        connection = sqlite3.connect(f"file:{database_path}?mode=ro", uri=True)
    except sqlite3.Error as exc:
        raise ExtractionError(f"Failed to open SQLite database '{database_path}': {exc}") from exc

    try:
        (
            boards_table,
            board_name_column,
            board_uid_column,
            mikrobus_column,
            soldered_device_column,
            devices_table,
            device_uid_column,
            device_sdk_support_column,
            board_to_device_table,
            board_to_device_board_uid_column,
            board_to_device_device_uid_column,
        ) = resolve_database_schema(connection)

        board_query = (
            f"SELECT {quote_identifier(board_uid_column)}, "
            f"{quote_identifier(mikrobus_column)}, "
            f"{quote_identifier(soldered_device_column)} "
            f"FROM {quote_identifier(boards_table)} "
            f"WHERE TRIM({quote_identifier(board_name_column)}) = TRIM(?) COLLATE NOCASE"
        )
        linked_devices_query = (
            f"SELECT DISTINCT {quote_identifier(board_to_device_device_uid_column)} "
            f"FROM {quote_identifier(board_to_device_table)} "
            f"WHERE TRIM({quote_identifier(board_to_device_board_uid_column)}) "
            f"= TRIM(?) COLLATE NOCASE"
        )
        device_support_query = (
            f"SELECT {quote_identifier(device_sdk_support_column)} "
            f"FROM {quote_identifier(devices_table)} "
            f"WHERE TRIM({quote_identifier(device_uid_column)}) = TRIM(?) COLLATE NOCASE"
        )

        classified: list[Board] = []
        eligible_boards: list[Board] = []
        other_boards: list[Board] = []
        unmatched_count = 0
        sdk_supported_count = 0
        sdk_unsupported_count = 0

        for board in boards:
            rows = connection.execute(board_query, (board.name,)).fetchall()
            if not rows:
                updated = replace(
                    board,
                    database_match=False,
                    board_uid=None,
                    mikrobus_count=None,
                    has_mikrobus=None,
                    soldered_device=None,
                    sdk_support_source=None,
                    checked_device_uids=(),
                    sdk_supported_device_uids=(),
                    missing_device_uids=(),
                    has_sdk_support=None,
                    embedded_wiki_eligible=False,
                    eligibility_note="Database match not found",
                )
                classified.append(updated)
                other_boards.append(updated)
                unmatched_count += 1
                continue

            normalized_counts: set[int] = set()
            normalized_uids: dict[str, str] = {}
            normalized_soldered_devices: dict[str, str | None] = {}

            for row in rows:
                raw_uid = row[0]
                if raw_uid is None or str(raw_uid).strip() == "":
                    raise ExtractionError(
                        f"Board '{board.name}' has an empty uid value in database"
                    )
                uid = str(raw_uid).strip()
                normalized_uids.setdefault(uid.casefold(), uid)

                raw_count = row[1]
                if raw_count is None or str(raw_count).strip() == "":
                    count = 0
                else:
                    try:
                        count = int(raw_count)
                    except (TypeError, ValueError) as exc:
                        raise ExtractionError(
                            f"Board '{board.name}' has invalid mikrobus_count value "
                            f"'{raw_count}' in database"
                        ) from exc
                if count < 0:
                    raise ExtractionError(
                        f"Board '{board.name}' has negative mikrobus_count value {count}"
                    )
                normalized_counts.add(count)

                soldered_device = normalize_nullable_uid(row[2])
                soldered_key = soldered_device.casefold() if soldered_device else ""
                normalized_soldered_devices.setdefault(soldered_key, soldered_device)

            if len(normalized_counts) > 1:
                values = ", ".join(str(value) for value in sorted(normalized_counts))
                raise ExtractionError(
                    f"Board name '{board.name}' matches multiple database rows with "
                    f"different mikrobus_count values: {values}"
                )

            if len(normalized_uids) > 1:
                values = ", ".join(sorted(normalized_uids.values(), key=str.casefold))
                raise ExtractionError(
                    f"Board name '{board.name}' matches multiple database rows with "
                    f"different uid values: {values}"
                )

            if len(normalized_soldered_devices) > 1:
                values = ", ".join(
                    "(empty)" if value is None else value
                    for value in sorted(
                        normalized_soldered_devices.values(),
                        key=lambda item: "" if item is None else item.casefold(),
                    )
                )
                raise ExtractionError(
                    f"Board name '{board.name}' matches multiple database rows with "
                    f"different soldered_device values: {values}"
                )

            board_uid = next(iter(normalized_uids.values()))
            mikrobus_count = next(iter(normalized_counts))
            has_mikrobus = mikrobus_count > 0
            soldered_device = next(iter(normalized_soldered_devices.values()))

            if soldered_device is not None:
                sdk_support_source = "Boards.soldered_device"
                device_uids = [soldered_device]
            else:
                sdk_support_source = "BoardToDevice"
                linked_rows = connection.execute(
                    linked_devices_query,
                    (board_uid,),
                ).fetchall()
                devices_by_key: dict[str, str] = {}
                for linked_row in linked_rows:
                    device_uid = normalize_nullable_uid(linked_row[0])
                    if device_uid is not None:
                        devices_by_key.setdefault(device_uid.casefold(), device_uid)
                device_uids = sorted(devices_by_key.values(), key=str.casefold)

            supported_devices: list[str] = []
            missing_devices: list[str] = []

            for device_uid in device_uids:
                support_rows = connection.execute(
                    device_support_query,
                    (device_uid,),
                ).fetchall()

                if not support_rows:
                    missing_devices.append(device_uid)
                    continue

                support_values = {
                    normalize_sdk_support(row[0], device_uid) for row in support_rows
                }
                if len(support_values) > 1:
                    raise ExtractionError(
                        f"Device uid '{device_uid}' matches multiple Devices rows with "
                        "conflicting sdk_support values"
                    )
                if True in support_values:
                    supported_devices.append(device_uid)

            # A board without a soldered device may map to several possible devices.
            # Any supported linked device is sufficient to confirm board SDK support.
            has_sdk_support = bool(supported_devices)
            embedded_wiki_eligible = has_mikrobus and has_sdk_support

            if has_sdk_support:
                sdk_supported_count += 1
            else:
                sdk_unsupported_count += 1

            if embedded_wiki_eligible:
                eligibility_note = "mikroBUS present and device-confirmed mikroSDK support"
            elif not has_mikrobus and not has_sdk_support:
                eligibility_note = "No mikroBUS and no device-confirmed mikroSDK support"
            elif not has_mikrobus:
                eligibility_note = "No mikroBUS"
            elif not device_uids:
                eligibility_note = "No devices linked for SDK support verification"
            elif missing_devices and len(missing_devices) == len(device_uids):
                eligibility_note = "Linked device records were not found in Devices"
            else:
                eligibility_note = "No device-confirmed mikroSDK support"

            updated = replace(
                board,
                database_match=True,
                board_uid=board_uid,
                mikrobus_count=mikrobus_count,
                has_mikrobus=has_mikrobus,
                soldered_device=soldered_device,
                sdk_support_source=sdk_support_source,
                checked_device_uids=tuple(device_uids),
                sdk_supported_device_uids=tuple(supported_devices),
                missing_device_uids=tuple(missing_devices),
                has_sdk_support=has_sdk_support,
                embedded_wiki_eligible=embedded_wiki_eligible,
                eligibility_note=eligibility_note,
            )
            classified.append(updated)

            if embedded_wiki_eligible:
                eligible_boards.append(updated)
            else:
                other_boards.append(updated)

        metadata = DatabaseMetadata(
            source_url=database_url,
            database_file=str(database_path),
            boards_table=boards_table,
            board_name_column=board_name_column,
            board_uid_column=board_uid_column,
            mikrobus_count_column=mikrobus_column,
            soldered_device_column=soldered_device_column,
            devices_table=devices_table,
            device_uid_column=device_uid_column,
            device_sdk_support_column=device_sdk_support_column,
            board_to_device_table=board_to_device_table,
            board_to_device_board_uid_column=board_to_device_board_uid_column,
            board_to_device_device_uid_column=board_to_device_device_uid_column,
            matched_boards=len(classified) - unmatched_count,
            unmatched_boards=unmatched_count,
            sdk_supported_boards=sdk_supported_count,
            sdk_unsupported_boards=sdk_unsupported_count,
            embedded_wiki_eligible_boards=len(eligible_boards),
            other_boards=len(other_boards),
        )
        return classified, eligible_boards, other_boards, metadata
    except sqlite3.Error as exc:
        raise ExtractionError(f"SQLite query failed for '{database_path}': {exc}") from exc
    finally:
        connection.close()


def extract_release_boards(
    repo: Path,
    raw_version: str,
    database_path: Path,
    database_url: str,
    raw_previous_version: str | None = None,
) -> ReleaseBoards:
    version = normalize_version(raw_version)
    tag = f"mikroSDK-{version}"
    release_changelog = f"changelog/v{version}/changelog.md"
    verify_tag(repo, tag)

    if raw_previous_version:
        previous_version = normalize_version(raw_previous_version)
        if version_tuple(previous_version) >= version_tuple(version):
            raise ExtractionError(
                f"Previous version {previous_version} must be lower than current version {version}"
            )
    else:
        previous_version = find_previous_version(repo, version)

    previous_tag = f"mikroSDK-{previous_version}"
    previous_release_changelog = f"changelog/v{previous_version}/changelog.md"
    verify_tag(repo, previous_tag)

    current_release_markdown = read_tag_file(repo, tag, release_changelog)
    release_date = get_release_date(current_release_markdown)

    previous_release_markdown = read_tag_file(
        repo, previous_tag, previous_release_changelog
    )
    previous_release_date = get_release_date(previous_release_markdown)

    dated_files = collect_interval_links(
        repo=repo,
        current_tag=tag,
        changelog_paths=(previous_release_changelog, release_changelog),
        previous_release_date=previous_release_date,
        current_release_date=release_date,
    )

    hardware_changelogs: list[HardwareChangelog] = []
    boards: list[Board] = []
    seen_boards: set[tuple[str, str | None]] = set()

    for added_date, hardware_changelog in dated_files:
        hardware_markdown = read_tag_file(repo, tag, hardware_changelog)
        validate_hardware_file_heading(
            hardware_markdown, added_date, hardware_changelog
        )
        hardware_section = extract_section(hardware_markdown, "NEW HARDWARE")
        file_boards = parse_boards(
            hardware_section,
            added_date=added_date,
            source_file=hardware_changelog,
        )

        hardware_changelogs.append(
            HardwareChangelog(
                date=added_date,
                path=hardware_changelog,
                board_count=len(file_boards),
            )
        )

        for board in file_boards:
            key = (board.name.casefold(), board.url)
            if key not in seen_boards:
                boards.append(board)
                seen_boards.add(key)

    (
        classified_boards,
        embedded_wiki_eligible_boards,
        other_boards,
        database_metadata,
    ) = classify_boards_with_database(boards, database_path, database_url)

    return ReleaseBoards(
        sdk_version=version,
        tag=tag,
        release_date=release_date,
        release_changelog=release_changelog,
        previous_sdk_version=previous_version,
        previous_tag=previous_tag,
        previous_release_date=previous_release_date,
        previous_release_changelog=previous_release_changelog,
        date_range=f"({previous_release_date}, {release_date}]",
        hardware_changelogs=hardware_changelogs,
        database=database_metadata,
        boards=classified_boards,
        embedded_wiki_eligible_boards=embedded_wiki_eligible_boards,
        other_boards=other_boards,
    )


def format_json(result: ReleaseBoards) -> str:
    return json.dumps(asdict(result), indent=2, ensure_ascii=False) + "\n"


def markdown_board_name(board: Board) -> str:
    return f"[{board.name}]({board.url})" if board.url else board.name


def mikrobus_markdown_status(board: Board) -> str:
    if board.has_mikrobus is True:
        return f"**mikroBUS present** (`mikrobus_count: {board.mikrobus_count}`)"
    if board.has_mikrobus is False:
        return f"**NO mikroBUS** (`mikrobus_count: {board.mikrobus_count}`)"
    return "**mikroBUS status unknown**"


def sdk_markdown_status(board: Board) -> str:
    if board.has_sdk_support is True:
        return "**SDK supported**"
    if board.has_sdk_support is False:
        return "**NO SDK support**"
    return "**SDK status unknown**"


def eligible_markdown_board_line(board: Board) -> str:
    return f"- {markdown_board_name(board)} — {mikrobus_markdown_status(board)}"


def other_markdown_board_line(board: Board) -> str:
    if not board.database_match:
        return (
            f"- {markdown_board_name(board)} — **DATABASE MATCH NOT FOUND (MIGHT NOT BE A BOARD)** "
            "— **EmbeddedWiki eligibility could not be confirmed**"
        )

    return (
        f"- {markdown_board_name(board)} — {mikrobus_markdown_status(board)} "
        f"— {sdk_markdown_status(board)}"
    )


def format_markdown(result: ReleaseBoards) -> str:
    lines = [
        f"# BOARDS\n",
        f"## mikroSDK {result.sdk_version} board support",
        "",
        f"- **Current tag:** `{result.tag}`",
        f"- **Current release date:** {result.release_date}",
        f"- **Previous tag:** `{result.previous_tag}`",
        f"- **Previous release date:** {result.previous_release_date}",
        f"- **Included date range:** `{result.date_range}`",
        f"- **Processed hardware files:** {len(result.hardware_changelogs)}",
        f"- **Unique boards:** {len(result.boards)}",
        (
            "- **EmbeddedWiki eligible boards:** "
            f"{len(result.embedded_wiki_eligible_boards)}"
        ),
        f"- **Other boards:** {len(result.other_boards)}",
        "",
        "### EmbeddedWiki eligible boards",
        "",
        "> A board is eligible only when it has at least one mikroBUS socket and mikroSDK support.",
        "",
    ]

    if result.embedded_wiki_eligible_boards:
        lines.extend(
            eligible_markdown_board_line(board)
            for board in result.embedded_wiki_eligible_boards
        )
    else:
        lines.append("No newly added boards are EmbeddedWiki eligible.")

    lines.extend(
        [
            "",
            "### Other boards",
            "",
            "> These boards are preserved for review but do not satisfy both eligibility requirements.",
            "",
        ]
    )
    if result.other_boards:
        lines.extend(other_markdown_board_line(board) for board in result.other_boards)
    else:
        lines.append("No other newly added boards were found.")

    return "\n".join(lines) + "\n" + "\n---\n"


def format_plain(result: ReleaseBoards) -> str:
    lines: list[str] = []
    for board in result.embedded_wiki_eligible_boards:
        lines.append(
            f"[EMBEDDEDWIKI ELIGIBLE] [mikroBUS x{board.mikrobus_count}] {board.name}"
        )

    for board in result.other_boards:
        if board.has_mikrobus is True:
            mikrobus_status = f"mikroBUS x{board.mikrobus_count}"
        elif board.has_mikrobus is False:
            mikrobus_status = "NO mikroBUS"
        else:
            mikrobus_status = "mikroBUS status unknown"

        if board.has_sdk_support is True:
            sdk_status = "SDK supported"
        elif board.has_sdk_support is False:
            sdk_status = "NO SDK support"
        else:
            sdk_status = "SDK status unknown"

        lines.append(f"[OTHER] [{mikrobus_status}] [{sdk_status}] {board.name}")

    return "\n".join(lines) + ("\n" if lines else "")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Extract boards added after the previous highest mikroSDK release, "
            "up to the selected release date, then determine EmbeddedWiki "
            "eligibility from mikroBUS presence and device-confirmed mikroSDK "
            "support in the NECTO database."
        )
    )
    parser.add_argument(
        "version",
        help="Current SDK version or tag, e.g. 2.19.0 or mikroSDK-2.19.0",
    )
    parser.add_argument(
        "--previous-version",
        help=(
            "Override automatic previous-tag selection, e.g. mikroSDK-2.18.0. "
            "By default, the highest lower mikroSDK-X.Y.Z tag is used."
        ),
    )
    parser.add_argument(
        "--repo",
        type=Path,
        default=Path.cwd(),
        help="Path to the mikroSDK Git repository (default: current directory)",
    )
    parser.add_argument(
        "--database-url",
        default=DEFAULT_DATABASE_URL,
        help="URL of the database_dev.7z archive",
    )
    parser.add_argument(
        "--database-cache-dir",
        type=Path,
        default=DEFAULT_DATABASE_CACHE_DIR,
        help=(
            "Directory used to cache the downloaded archive and extracted database "
            f"(default: {DEFAULT_DATABASE_CACHE_DIR})"
        ),
    )
    parser.add_argument(
        "--database-path",
        type=Path,
        help="Use an existing necto_db.db file and skip download/extraction",
    )
    parser.add_argument(
        "--refresh-database",
        action="store_true",
        help="Force database archive re-download and re-extraction",
    )
    parser.add_argument(
        "--format",
        choices=("json", "markdown", "plain"),
        default="json",
        help="Output format (default: json)",
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="Write output to this file instead of stdout",
    )
    return parser


def main(argv: Iterable[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    repo = args.repo.expanduser().resolve()

    try:
        if not repo.is_dir():
            raise ExtractionError(f"Repository path does not exist: {repo}")

        database_path = prepare_database(
            database_url=args.database_url,
            cache_dir=args.database_cache_dir,
            database_path=args.database_path,
            refresh=args.refresh_database,
        )

        result = extract_release_boards(
            repo,
            args.version,
            database_path=database_path,
            database_url=args.database_url,
            raw_previous_version=args.previous_version,
        )

        formatter = {
            "json": format_json,
            "markdown": format_markdown,
            "plain": format_plain,
        }[args.format]
        output = formatter(result)

        if args.output:
            destination = args.output.expanduser()
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(output, encoding="utf-8")
        else:
            sys.stdout.write(output)

        return 0
    except ExtractionError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
