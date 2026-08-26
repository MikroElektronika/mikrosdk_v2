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
   ``Boards.mikrobus_count`` and the optional ``_MSDK_SHIELD_`` entry from
   ``Boards.sdk_config``. It also reads ``Boards.installer_package`` and links
   to ``bsp/board/include/boards/<package>/board.h`` in the selected tag.
7. Determines SDK support from the board's devices:
   - When ``Boards.soldered_device`` is set, that ``Devices.uid`` is checked.
   - Otherwise, unique devices linked through ``BoardToDevice`` are checked.
   A board has SDK support when at least one checked device has
   ``Devices.sdk_support = 1``.
   Each selected device is also mapped to its unique package values through
   ``DeviceToPackage(device_uid, package_uid)``.
8. Classifies supported boards into two EmbeddedWiki categories:
   - directly eligible when at least one mikroBUS socket is present;
   - eligible with shield when no socket is present but ``sdk_config`` declares
     an ``_MSDK_SHIELD_`` expansion option.
   Every other board is preserved and reported with the reason it is not
   eligible.

Changelog files are read directly with ``git show``. The working tree is never
changed. Downloaded database files are cached between invocations.
"""

from __future__ import annotations

import argparse
import json
import os
import posixpath
import re
import shutil
import sqlite3
import subprocess
import sys
import urllib.error
import urllib.request
from urllib.parse import parse_qs, quote, urlparse
from dataclasses import asdict, dataclass, replace
from datetime import date
from pathlib import Path
from typing import Iterable


DEFAULT_DATABASE_URL = (
    "https://github.com/MikroElektronika/general_packages/releases/download/"
    "general_packages_assets/database_dev.7z"
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

SHEETS_READWRITE_SCOPES = [
    "https://www.googleapis.com/auth/spreadsheets",
]



class ExtractionError(RuntimeError):
    """Raised when changelog or database processing cannot continue safely."""


@dataclass(frozen=True)
class McuPackage:
    """One board MCU/device, its vendor and unique package relationships."""

    mcu_uid: str
    vendor: str | None = None
    package_uids: tuple[str, ...] = ()


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
    sdk_config: str | None = None
    installer_package: str | None = None
    board_package: str | None = None
    board_header_path: str | None = None
    board_header_url: str | None = None
    board_header_exists: bool | None = None
    shield_uid: str | None = None
    has_shield: bool = False
    soldered_device: str | None = None
    sdk_support_source: str | None = None
    checked_device_uids: tuple[str, ...] = ()
    sdk_supported_device_uids: tuple[str, ...] = ()
    missing_device_uids: tuple[str, ...] = ()
    mcu_packages: tuple[McuPackage, ...] = ()
    has_sdk_support: bool | None = None
    embedded_wiki_eligible: bool = False
    embedded_wiki_eligible_with_shield: bool = False
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
    sdk_config_column: str
    installer_package_column: str
    soldered_device_column: str
    devices_table: str
    device_uid_column: str
    device_sdk_support_column: str
    board_to_device_table: str
    board_to_device_board_uid_column: str
    board_to_device_device_uid_column: str
    device_to_package_table: str
    device_to_package_device_uid_column: str
    device_to_package_package_uid_column: str
    matched_boards: int
    unmatched_boards: int
    sdk_supported_boards: int
    sdk_unsupported_boards: int
    embedded_wiki_eligible_boards: int
    embedded_wiki_eligible_with_shield_boards: int
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
    github_repository_url: str
    database: DatabaseMetadata
    boards: list[Board]
    embedded_wiki_eligible_boards: list[Board]
    embedded_wiki_eligible_with_shield_boards: list[Board]
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
) -> tuple[str, ...]:
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
        (
            "name",
            "uid",
            "mikrobus_count",
            "sdk_config",
            "installer_package",
            "soldered_device",
        ),
    )

    devices_table = find_table("Devices")
    devices_columns = find_columns(
        devices_table,
        ("uid", "sdk_support", "vendor"),
    )

    board_to_device_table = find_table("BoardToDevice")
    board_to_device_columns = find_columns(
        board_to_device_table,
        ("board_uid", "device_uid"),
    )

    device_to_package_table = find_table("DeviceToPackage")
    device_to_package_columns = find_columns(
        device_to_package_table,
        ("device_uid", "package_uid"),
    )

    return (
        boards_table,
        boards_columns["name"],
        boards_columns["uid"],
        boards_columns["mikrobus_count"],
        boards_columns["sdk_config"],
        boards_columns["installer_package"],
        boards_columns["soldered_device"],
        devices_table,
        devices_columns["uid"],
        devices_columns["sdk_support"],
        devices_columns["vendor"],
        board_to_device_table,
        board_to_device_columns["board_uid"],
        board_to_device_columns["device_uid"],
        device_to_package_table,
        device_to_package_columns["device_uid"],
        device_to_package_columns["package_uid"],
    )


def normalize_nullable_uid(raw_value: object) -> str | None:
    if raw_value is None:
        return None
    value = str(raw_value).strip()
    return value or None


def parse_sdk_config(raw_value: object, board_name: str) -> tuple[str | None, str | None, bool]:
    """Return normalized JSON text, shield uid, and shield-key presence."""
    if raw_value is None or str(raw_value).strip() == "":
        return None, None, False

    raw_text = str(raw_value).strip()
    try:
        config = json.loads(raw_text)
    except json.JSONDecodeError as exc:
        raise ExtractionError(
            f"Board '{board_name}' has invalid JSON in sdk_config: {exc.msg}"
        ) from exc

    if not isinstance(config, dict):
        raise ExtractionError(
            f"Board '{board_name}' has sdk_config JSON that is not an object"
        )

    normalized_text = json.dumps(config, sort_keys=True, separators=(",", ":"))
    has_shield = "_MSDK_SHIELD_" in config
    shield_uid = normalize_nullable_uid(config.get("_MSDK_SHIELD_")) if has_shield else None
    return normalized_text, shield_uid, has_shield


def parse_installer_package(
    raw_value: object,
    board_name: str,
) -> tuple[str | None, str | None]:
    """Return normalized installer_package JSON and its package value."""
    if raw_value is None or str(raw_value).strip() == "":
        return None, None

    raw_text = str(raw_value).strip()
    try:
        config = json.loads(raw_text)
    except json.JSONDecodeError as exc:
        raise ExtractionError(
            f"Board '{board_name}' has invalid JSON in installer_package: {exc.msg}"
        ) from exc

    if not isinstance(config, dict):
        raise ExtractionError(
            f"Board '{board_name}' has installer_package JSON that is not an object"
        )

    package = normalize_nullable_uid(config.get("package"))
    normalized_text = json.dumps(config, sort_keys=True, separators=(",", ":"))
    return normalized_text, package


def git_path_exists(repo: Path, ref: str, path: str) -> bool:
    result = subprocess.run(
        ["git", "-C", str(repo), "cat-file", "-e", f"{ref}:{path}"],
        text=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
        check=False,
    )
    return result.returncode == 0


def normalize_repository_web_url(raw_url: str) -> str:
    value = raw_url.strip().rstrip("/")
    if value.endswith(".git"):
        value = value[:-4]

    scp_match = re.fullmatch(r"git@([^:]+):(.+)", value)
    if scp_match:
        host, repository = scp_match.groups()
        return f"https://{host}/{repository.strip('/')}"

    parsed = urlparse(value)
    if parsed.scheme in {"http", "https"} and parsed.netloc:
        clean_path = parsed.path.strip("/")
        return f"{parsed.scheme}://{parsed.netloc}/{clean_path}"

    if parsed.scheme == "ssh" and parsed.hostname:
        clean_path = parsed.path.strip("/")
        return f"https://{parsed.hostname}/{clean_path}"

    raise ExtractionError(f"Unable to convert Git remote URL to a web URL: {raw_url}")


def resolve_github_repository_url(repo: Path, override: str | None = None) -> str:
    if override and override.strip():
        return normalize_repository_web_url(override)

    github_repository = os.environ.get("GITHUB_REPOSITORY", "").strip()
    if github_repository:
        server_url = os.environ.get("GITHUB_SERVER_URL", "https://github.com").rstrip("/")
        return f"{server_url}/{github_repository.strip('/')}"

    try:
        remote_url = run_git(repo, "remote", "get-url", "origin").strip()
    except ExtractionError as exc:
        raise ExtractionError(
            "Could not determine the GitHub repository URL. Configure an origin "
            "remote or pass --github-repository-url."
        ) from exc

    if not remote_url:
        raise ExtractionError(
            "Git remote 'origin' has no URL; pass --github-repository-url."
        )
    return normalize_repository_web_url(remote_url)


def build_board_header_reference(
    repo: Path,
    ref: str,
    repository_url: str,
    board_package: str | None,
) -> tuple[str | None, str | None, bool | None]:
    if board_package is None:
        return None, None, None

    header_path = f"bsp/board/include/boards/{board_package}/board.h"
    exists = git_path_exists(repo, ref, header_path)
    if not exists:
        return header_path, None, False

    encoded_ref = quote(ref, safe="")
    encoded_path = quote(header_path, safe="/")
    header_url = f"{repository_url}/blob/{encoded_ref}/{encoded_path}"
    return header_path, header_url, True


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
    repo: Path,
    ref: str,
    repository_url: str,
) -> tuple[
    list[Board],
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
            sdk_config_column,
            installer_package_column,
            soldered_device_column,
            devices_table,
            device_uid_column,
            device_sdk_support_column,
            device_vendor_column,
            board_to_device_table,
            board_to_device_board_uid_column,
            board_to_device_device_uid_column,
            device_to_package_table,
            device_to_package_device_uid_column,
            device_to_package_package_uid_column,
        ) = resolve_database_schema(connection)

        board_query = (
            f"SELECT {quote_identifier(board_uid_column)}, "
            f"{quote_identifier(mikrobus_column)}, "
            f"{quote_identifier(sdk_config_column)}, "
            f"{quote_identifier(installer_package_column)}, "
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
            f"SELECT {quote_identifier(device_sdk_support_column)}, "
            f"{quote_identifier(device_vendor_column)} "
            f"FROM {quote_identifier(devices_table)} "
            f"WHERE TRIM({quote_identifier(device_uid_column)}) = TRIM(?) COLLATE NOCASE"
        )
        device_packages_query = (
            f"SELECT DISTINCT {quote_identifier(device_to_package_package_uid_column)} "
            f"FROM {quote_identifier(device_to_package_table)} "
            f"WHERE TRIM({quote_identifier(device_to_package_device_uid_column)}) "
            f"= TRIM(?) COLLATE NOCASE"
        )

        classified: list[Board] = []
        eligible_boards: list[Board] = []
        shield_eligible_boards: list[Board] = []
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
                    sdk_config=None,
                    installer_package=None,
                    board_package=None,
                    board_header_path=None,
                    board_header_url=None,
                    board_header_exists=None,
                    shield_uid=None,
                    has_shield=False,
                    soldered_device=None,
                    sdk_support_source=None,
                    checked_device_uids=(),
                    sdk_supported_device_uids=(),
                    missing_device_uids=(),
                    mcu_packages=(),
                    has_sdk_support=None,
                    embedded_wiki_eligible=False,
                    embedded_wiki_eligible_with_shield=False,
                    eligibility_note="Database match not found",
                )
                classified.append(updated)
                other_boards.append(updated)
                unmatched_count += 1
                continue

            normalized_counts: set[int] = set()
            normalized_uids: dict[str, str] = {}
            normalized_sdk_configs: dict[
                str, tuple[str | None, str | None, bool]
            ] = {}
            normalized_installer_packages: dict[
                str, tuple[str | None, str | None]
            ] = {}
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

                sdk_config, shield_uid, has_shield = parse_sdk_config(row[2], board.name)
                normalized_sdk_configs.setdefault(
                    sdk_config or "",
                    (sdk_config, shield_uid, has_shield),
                )

                installer_package, board_package = parse_installer_package(
                    row[3], board.name
                )
                normalized_installer_packages.setdefault(
                    installer_package or "",
                    (installer_package, board_package),
                )

                soldered_device = normalize_nullable_uid(row[4])
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

            if len(normalized_sdk_configs) > 1:
                values = ", ".join(
                    value[0] or "(empty)" for value in normalized_sdk_configs.values()
                )
                raise ExtractionError(
                    f"Board name '{board.name}' matches multiple database rows with "
                    f"different sdk_config values: {values}"
                )

            if len(normalized_installer_packages) > 1:
                values = ", ".join(
                    value[0] or "(empty)"
                    for value in normalized_installer_packages.values()
                )
                raise ExtractionError(
                    f"Board name '{board.name}' matches multiple database rows with "
                    f"different installer_package values: {values}"
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
            sdk_config, shield_uid, has_shield = next(
                iter(normalized_sdk_configs.values())
            )
            installer_package, board_package = next(
                iter(normalized_installer_packages.values())
            )
            board_header_path, board_header_url, board_header_exists = (
                build_board_header_reference(
                    repo,
                    ref,
                    repository_url,
                    board_package,
                )
            )
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
            mcu_packages: list[McuPackage] = []

            for device_uid in device_uids:
                package_rows = connection.execute(
                    device_packages_query,
                    (device_uid,),
                ).fetchall()
                packages_by_key: dict[str, str] = {}
                for package_row in package_rows:
                    package_uid = normalize_nullable_uid(package_row[0])
                    if package_uid is not None:
                        packages_by_key.setdefault(package_uid.casefold(), package_uid)
                package_uids = tuple(
                    sorted(packages_by_key.values(), key=str.casefold)
                )

                support_rows = connection.execute(
                    device_support_query,
                    (device_uid,),
                ).fetchall()

                if not support_rows:
                    mcu_packages.append(
                        McuPackage(
                            mcu_uid=device_uid,
                            vendor=None,
                            package_uids=package_uids,
                        )
                    )
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

                vendors_by_key: dict[str, str] = {}
                for row in support_rows:
                    vendor_name = normalize_nullable_uid(row[1])
                    if vendor_name is not None:
                        vendors_by_key.setdefault(vendor_name.casefold(), vendor_name)

                if len(vendors_by_key) > 1:
                    raise ExtractionError(
                        f"Device uid '{device_uid}' matches multiple Devices rows with "
                        "conflicting vendor values: "
                        + ", ".join(sorted(vendors_by_key.values(), key=str.casefold))
                    )

                vendor_name = next(iter(vendors_by_key.values()), None)
                mcu_packages.append(
                    McuPackage(
                        mcu_uid=device_uid,
                        vendor=vendor_name,
                        package_uids=package_uids,
                    )
                )

                if True in support_values:
                    supported_devices.append(device_uid)

            # A board without a soldered device may map to several possible devices.
            # Any supported linked device is sufficient to confirm board SDK support.
            has_sdk_support = bool(supported_devices)
            embedded_wiki_eligible = has_mikrobus and has_sdk_support
            embedded_wiki_eligible_with_shield = (
                not has_mikrobus and has_shield and has_sdk_support
            )

            if has_sdk_support:
                sdk_supported_count += 1
            else:
                sdk_unsupported_count += 1

            if embedded_wiki_eligible:
                eligibility_note = "mikroBUS present and device-confirmed mikroSDK support"
            elif embedded_wiki_eligible_with_shield:
                eligibility_note = (
                    "No onboard mikroBUS, but shield expansion and "
                    "device-confirmed mikroSDK support are available"
                )
            elif not device_uids:
                eligibility_note = "No devices linked for SDK support verification"
            elif missing_devices and len(missing_devices) == len(device_uids):
                eligibility_note = "Linked device records were not found in Devices"
            elif not has_sdk_support and has_shield and not has_mikrobus:
                eligibility_note = (
                    "mikroBUS expansion shield available but no device-confirmed "
                    "mikroSDK support"
                )
            elif not has_sdk_support:
                eligibility_note = "No device-confirmed mikroSDK support"
            elif not has_mikrobus:
                eligibility_note = "No onboard mikroBUS or shield expansion option"
            else:
                eligibility_note = "Not EmbeddedWiki eligible"

            updated = replace(
                board,
                database_match=True,
                board_uid=board_uid,
                mikrobus_count=mikrobus_count,
                has_mikrobus=has_mikrobus,
                sdk_config=sdk_config,
                installer_package=installer_package,
                board_package=board_package,
                board_header_path=board_header_path,
                board_header_url=board_header_url,
                board_header_exists=board_header_exists,
                shield_uid=shield_uid,
                has_shield=has_shield,
                soldered_device=soldered_device,
                sdk_support_source=sdk_support_source,
                checked_device_uids=tuple(device_uids),
                sdk_supported_device_uids=tuple(supported_devices),
                missing_device_uids=tuple(missing_devices),
                mcu_packages=tuple(mcu_packages),
                has_sdk_support=has_sdk_support,
                embedded_wiki_eligible=embedded_wiki_eligible,
                embedded_wiki_eligible_with_shield=(
                    embedded_wiki_eligible_with_shield
                ),
                eligibility_note=eligibility_note,
            )
            classified.append(updated)

            if embedded_wiki_eligible:
                eligible_boards.append(updated)
            elif embedded_wiki_eligible_with_shield:
                shield_eligible_boards.append(updated)
            else:
                other_boards.append(updated)

        metadata = DatabaseMetadata(
            source_url=database_url,
            database_file=str(database_path),
            boards_table=boards_table,
            board_name_column=board_name_column,
            board_uid_column=board_uid_column,
            mikrobus_count_column=mikrobus_column,
            sdk_config_column=sdk_config_column,
            installer_package_column=installer_package_column,
            soldered_device_column=soldered_device_column,
            devices_table=devices_table,
            device_uid_column=device_uid_column,
            device_sdk_support_column=device_sdk_support_column,
            board_to_device_table=board_to_device_table,
            board_to_device_board_uid_column=board_to_device_board_uid_column,
            board_to_device_device_uid_column=board_to_device_device_uid_column,
            device_to_package_table=device_to_package_table,
            device_to_package_device_uid_column=(
                device_to_package_device_uid_column
            ),
            device_to_package_package_uid_column=(
                device_to_package_package_uid_column
            ),
            matched_boards=len(classified) - unmatched_count,
            unmatched_boards=unmatched_count,
            sdk_supported_boards=sdk_supported_count,
            sdk_unsupported_boards=sdk_unsupported_count,
            embedded_wiki_eligible_boards=len(eligible_boards),
            embedded_wiki_eligible_with_shield_boards=len(shield_eligible_boards),
            other_boards=len(other_boards),
        )
        return (
            classified,
            eligible_boards,
            shield_eligible_boards,
            other_boards,
            metadata,
        )
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
    github_repository_url: str | None = None,
) -> ReleaseBoards:
    version = normalize_version(raw_version)
    tag = f"mikroSDK-{version}"
    release_changelog = f"changelog/v{version}/changelog.md"
    verify_tag(repo, tag)
    repository_url = resolve_github_repository_url(repo, github_repository_url)

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
        embedded_wiki_eligible_with_shield_boards,
        other_boards,
        database_metadata,
    ) = classify_boards_with_database(
        boards,
        database_path,
        database_url,
        repo=repo,
        ref=tag,
        repository_url=repository_url,
    )

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
        github_repository_url=repository_url,
        database=database_metadata,
        boards=classified_boards,
        embedded_wiki_eligible_boards=embedded_wiki_eligible_boards,
        embedded_wiki_eligible_with_shield_boards=(
            embedded_wiki_eligible_with_shield_boards
        ),
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
        if board.has_shield:
            shield_details = (
                f" (`shield: {board.shield_uid}`)" if board.shield_uid else ""
            )
            return f"**mikroBUS expandable with shield**{shield_details}"
        return f"**NO mikroBUS** (`mikrobus_count: {board.mikrobus_count}`)"
    return "**mikroBUS status unknown**"


def sdk_markdown_status(board: Board) -> str:
    if board.has_sdk_support is True:
        return "**SDK supported**"
    if board.has_sdk_support is False:
        return "**NO SDK support**"
    return "**SDK status unknown**"


def board_header_markdown_link(board: Board) -> str:
    if board.board_header_url:
        return f" — [board.h]({board.board_header_url})"
    if board.board_package and board.board_header_exists is False:
        return " — **board.h not found in selected tag**"
    if board.database_match and not board.board_package:
        return " — **installer package not defined**"
    return ""


def mcu_package_markdown_status(board: Board) -> str:
    """Return a compact MCU-to-package mapping for Markdown outputs."""
    if not board.database_match:
        return ""
    if not board.mcu_packages:
        return " — **MCU/package data not found**"

    mappings: list[str] = []
    for item in board.mcu_packages:
        if item.package_uids:
            packages = ", ".join(f"`{value}`" for value in item.package_uids)
        else:
            packages = "**package not found**"
        mappings.append(f"`{item.mcu_uid}` → {packages}")

    return " — **MCU / package:** " + "; ".join(mappings)


def eligible_markdown_board_line(board: Board) -> str:
    return (
        f"- {markdown_board_name(board)} — {mikrobus_markdown_status(board)}"
        f"{mcu_package_markdown_status(board)}"
        f"{board_header_markdown_link(board)}"
    )


def other_markdown_board_line(board: Board) -> str:
    if not board.database_match:
        return (
            f"- {markdown_board_name(board)} — **DATABASE MATCH NOT FOUND (MIGHT NOT BE A BOARD)** "
            "— **EmbeddedWiki eligibility could not be confirmed**"
        )

    return (
        f"- {markdown_board_name(board)} — {mikrobus_markdown_status(board)} "
        f"— {sdk_markdown_status(board)}{mcu_package_markdown_status(board)}"
        f"{board_header_markdown_link(board)}"
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
        f"- **GitHub repository:** {result.github_repository_url}",
        f"- **Processed hardware files:** {len(result.hardware_changelogs)}",
        f"- **Unique boards:** {len(result.boards)}",
        (
            "- **EmbeddedWiki eligible boards:** "
            f"{len(result.embedded_wiki_eligible_boards)}"
        ),
        (
            "- **EmbeddedWiki eligible boards - with shield:** "
            f"{len(result.embedded_wiki_eligible_with_shield_boards)}"
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
            "### EmbeddedWiki eligible boards - with shield",
            "",
            (
                "> These boards have no onboard mikroBUS socket, but their SDK "
                "configuration declares a shield expansion option and they have "
                "device-confirmed mikroSDK support."
            ),
            "",
        ]
    )
    if result.embedded_wiki_eligible_with_shield_boards:
        lines.extend(
            eligible_markdown_board_line(board)
            for board in result.embedded_wiki_eligible_with_shield_boards
        )
    else:
        lines.append(
            "No newly added boards are EmbeddedWiki eligible through a shield."
        )

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

    return "\n".join(lines) + "\n\n---\n"


def format_mattermost(result: ReleaseBoards) -> str:
    """Format a concise Mattermost report containing eligible boards only."""
    total_eligible = (
        len(result.embedded_wiki_eligible_boards)
        + len(result.embedded_wiki_eligible_with_shield_boards)
    )

    lines = [
        "# BOARDS",
        "",
        f"## mikroSDK {result.sdk_version} EmbeddedWiki board candidates",
        "",
        f"- **Release tag:** `{result.tag}`",
        f"- **Release date:** {result.release_date}",
        f"- **Total eligible boards:** {total_eligible}",
        (
            "- **Directly eligible:** "
            f"{len(result.embedded_wiki_eligible_boards)}"
        ),
        (
            "- **Eligible with shield:** "
            f"{len(result.embedded_wiki_eligible_with_shield_boards)}"
        ),
        "",
        "### EmbeddedWiki eligible boards",
        "",
    ]

    if result.embedded_wiki_eligible_boards:
        lines.extend(
            eligible_markdown_board_line(board)
            for board in result.embedded_wiki_eligible_boards
        )
    else:
        lines.append("No directly eligible boards were added in this release interval.")

    lines.extend(
        [
            "",
            "### EmbeddedWiki eligible boards - with shield",
            "",
        ]
    )

    if result.embedded_wiki_eligible_with_shield_boards:
        lines.extend(
            eligible_markdown_board_line(board)
            for board in result.embedded_wiki_eligible_with_shield_boards
        )
    else:
        lines.append(
            "No shield-based EmbeddedWiki candidates were added in this release interval."
        )

    return "\n".join(lines) + "\n\n---\n"


def mcu_package_plain_status(board: Board) -> str:
    if not board.mcu_packages:
        return "MCU/package unavailable"
    mappings: list[str] = []
    for item in board.mcu_packages:
        packages = ",".join(item.package_uids) if item.package_uids else "package not found"
        mappings.append(f"{item.mcu_uid} -> {packages}")
    return "; ".join(mappings)


def format_plain(result: ReleaseBoards) -> str:
    lines: list[str] = []
    for board in result.embedded_wiki_eligible_boards:
        lines.append(
            f"[EMBEDDEDWIKI ELIGIBLE] [mikroBUS x{board.mikrobus_count}] "
            f"[{mcu_package_plain_status(board)}] {board.name}"
        )

    for board in result.embedded_wiki_eligible_with_shield_boards:
        shield_status = (
            f"shield {board.shield_uid}" if board.shield_uid else "shield available"
        )
        lines.append(
            f"[EMBEDDEDWIKI ELIGIBLE WITH SHIELD] [{shield_status}] "
            f"[{mcu_package_plain_status(board)}] {board.name}"
        )

    for board in result.other_boards:
        if board.has_mikrobus is True:
            mikrobus_status = f"mikroBUS x{board.mikrobus_count}"
        elif board.has_mikrobus is False:
            if board.has_shield:
                mikrobus_status = (
                    f"mikroBUS expandable with shield {board.shield_uid}"
                    if board.shield_uid
                    else "mikroBUS expandable with shield"
                )
            else:
                mikrobus_status = "NO mikroBUS"
        else:
            mikrobus_status = "mikroBUS status unknown"

        if board.has_sdk_support is True:
            sdk_status = "SDK supported"
        elif board.has_sdk_support is False:
            sdk_status = "NO SDK support"
        else:
            sdk_status = "SDK status unknown"

        lines.append(
            f"[OTHER] [{mikrobus_status}] [{sdk_status}] "
            f"[{mcu_package_plain_status(board)}] {board.name}"
        )

    return "\n".join(lines) + ("\n" if lines else "")


def _extract_google_sheet_ids(sheet_url: str) -> tuple[str | None, str | None]:
    """Extract a spreadsheet ID and optional gid from normal/export Google Sheet URLs."""
    parsed = urlparse(sheet_url)
    parts = parsed.path.split("/")

    spreadsheet_id = None
    try:
        d_index = parts.index("d")
        candidate = parts[d_index + 1]
        if candidate != "e":
            spreadsheet_id = candidate
    except (ValueError, IndexError):
        spreadsheet_id = None

    gid = None
    if parsed.fragment:
        fragment_values = parse_qs(parsed.fragment)
        gid = (fragment_values.get("gid") or [None])[0]
        if not gid:
            match = re.search(r"gid=(\d+)", parsed.fragment)
            gid = match.group(1) if match else None

    if not gid:
        query_values = parse_qs(parsed.query)
        gid = (query_values.get("gid") or [None])[0]

    return spreadsheet_id, gid


def _quote_sheet_title(title: str) -> str:
    return "'" + title.replace("'", "''") + "'"


def _column_number_to_a1(column_number: int) -> str:
    if column_number < 1:
        raise ValueError("column_number must be >= 1")

    result = ""
    while column_number:
        column_number, remainder = divmod(column_number - 1, 26)
        result = chr(65 + remainder) + result
    return result


def collect_sheet_mcu_package_pairs(
    result: ReleaseBoards,
) -> tuple[list[tuple[str, str, str]], list[str], list[str]]:
    """Collect unique vendor/MCU/package rows from EmbeddedWiki-eligible boards.

    MCU + PACKAGE remains the spreadsheet uniqueness key. Vendor is metadata
    fetched from Devices.vendor and is required for every new row.
    """
    eligible_boards = (
        result.embedded_wiki_eligible_boards
        + result.embedded_wiki_eligible_with_shield_boards
    )

    rows_by_key: dict[tuple[str, str], tuple[str, str, str]] = {}
    missing_package_mcus: dict[str, str] = {}
    missing_vendor_mcus: dict[str, str] = {}

    for board in eligible_boards:
        supported_device_keys = {
            device_uid.casefold() for device_uid in board.sdk_supported_device_uids
        }

        for mapping in board.mcu_packages:
            # A multi-device board can contain both supported and unsupported devices.
            # Only device-confirmed SDK-supported MCUs belong in the work queue.
            if mapping.mcu_uid.casefold() not in supported_device_keys:
                continue

            if not mapping.package_uids:
                missing_package_mcus.setdefault(
                    mapping.mcu_uid.casefold(), mapping.mcu_uid
                )
                continue

            if not mapping.vendor:
                missing_vendor_mcus.setdefault(
                    mapping.mcu_uid.casefold(), mapping.mcu_uid
                )
                continue

            for package_uid in mapping.package_uids:
                key = (mapping.mcu_uid.casefold(), package_uid.casefold())
                row = (mapping.vendor, mapping.mcu_uid, package_uid)

                existing = rows_by_key.get(key)
                if existing is not None and existing[0].casefold() != mapping.vendor.casefold():
                    raise ExtractionError(
                        f"MCU/package combination '{mapping.mcu_uid}' / "
                        f"'{package_uid}' has conflicting vendors: "
                        f"'{existing[0]}' and '{mapping.vendor}'"
                    )

                rows_by_key.setdefault(key, row)

    rows = sorted(
        rows_by_key.values(),
        key=lambda item: (
            item[0].casefold(),
            item[1].casefold(),
            item[2].casefold(),
        ),
    )
    missing_packages = sorted(missing_package_mcus.values(), key=str.casefold)
    missing_vendors = sorted(missing_vendor_mcus.values(), key=str.casefold)
    return rows, missing_packages, missing_vendors


def update_google_sheet(
    result: ReleaseBoards,
    sheet_url: str,
    credentials_path: Path,
    sheet_name: str | None = None,
    date_added: str | None = None,
    dry_run: bool = False,
) -> dict[str, object]:
    """Synchronize eligible vendor/MCU/package rows with the Google Sheet.

    Existing MCU/package pairs are skipped, so completed rows are never reset to NO.
    Existing vendor and package logo links are propagated into blank cells for all
    rows that share the same VENDOR or PACKAGE value. Populated logo cells are never
    overwritten.
    """
    spreadsheet_id, gid = _extract_google_sheet_ids(sheet_url)
    if not spreadsheet_id:
        raise ExtractionError(
            "Could not extract a Google spreadsheet ID from --sheet-url. "
            "Use a normal /spreadsheets/d/<ID>/... URL."
        )

    resolved_credentials = credentials_path.expanduser().resolve()

    if date_added is None:
        date_added = date.today().isoformat()
    try:
        date.fromisoformat(date_added)
    except ValueError as exc:
        raise ExtractionError(
            f"Invalid sheet date '{date_added}'. Expected YYYY-MM-DD."
        ) from exc

    (
        candidate_rows,
        missing_package_mcus,
        missing_vendor_mcus,
    ) = collect_sheet_mcu_package_pairs(result)

    if dry_run:
        return {
            "dry_run": True,
            "candidate_pairs": len(candidate_rows),
            "appended": 0,
            "existing": 0,
            "missing_package_mcus": missing_package_mcus,
            "missing_vendor_mcus": missing_vendor_mcus,
            "rows": [
                {
                    "VENDOR": vendor,
                    "MCU": mcu,
                    "PACKAGE": package,
                    "VENDOR LOGO LINK": "",
                    "PACKAGE LOGO LINK": "",
                    "IS IT DONE": "NO",
                    "DATE ADDED": date_added,
                }
                for vendor, mcu, package in candidate_rows
            ],
        }

    if not resolved_credentials.is_file():
        raise ExtractionError(
            f"Google service-account credentials file does not exist: "
            f"{resolved_credentials}"
        )

    try:
        from google.oauth2.service_account import Credentials
        from googleapiclient.discovery import build
    except ImportError as exc:
        raise ExtractionError(
            "Google Sheet editing requires google-api-python-client and google-auth. "
            "Install them with: pip install google-api-python-client google-auth"
        ) from exc

    credentials = Credentials.from_service_account_file(
        str(resolved_credentials),
        scopes=SHEETS_READWRITE_SCOPES,
    )
    service = build(
        "sheets",
        "v4",
        credentials=credentials,
        cache_discovery=False,
    )

    requested_sheet_name = (
        sheet_name.strip() if sheet_name and sheet_name.strip() else None
    )

    metadata = service.spreadsheets().get(
        spreadsheetId=spreadsheet_id,
    ).execute()

    available_sheets: list[tuple[str, str]] = []
    for sheet in metadata.get("sheets", []):
        properties = sheet.get("properties", {})
        title = str(properties.get("title") or "").strip()
        sheet_id = str(properties.get("sheetId"))
        if title:
            available_sheets.append((title, sheet_id))

    resolved_sheet_name: str | None = None

    # First try the explicitly provided worksheet tab name.
    if requested_sheet_name:
        for title, _sheet_id in available_sheets:
            if title.casefold() == requested_sheet_name.casefold():
                resolved_sheet_name = title
                break

    # If the provided value was the spreadsheet document title rather than a
    # worksheet tab name, fall back to the gid from the URL.
    if not resolved_sheet_name and gid is not None:
        for title, sheet_id in available_sheets:
            if sheet_id == str(gid):
                resolved_sheet_name = title
                break

    if not resolved_sheet_name:
        available_titles = ", ".join(
            repr(title) for title, _sheet_id in available_sheets
        ) or "<none>"

        if requested_sheet_name:
            raise ExtractionError(
                f"Google Sheet tab '{requested_sheet_name}' was not found and "
                f"gid={gid!s} could not be resolved. Available tabs: "
                f"{available_titles}"
            )

        raise ExtractionError(
            "Could not determine the target Google Sheet tab. Use a URL "
            "containing gid=<number> or pass --sheet-name with an actual "
            f"worksheet tab name. Available tabs: {available_titles}"
        )

    quoted_title = _quote_sheet_title(resolved_sheet_name)
    header_response = service.spreadsheets().values().get(
        spreadsheetId=spreadsheet_id,
        range=f"{quoted_title}!A1:ZZ1",
    ).execute()
    header_rows = header_response.get("values", [])
    if not header_rows:
        raise ExtractionError(
            f"No headers were found in row 1 of sheet '{resolved_sheet_name}'."
        )

    headers = [str(value).strip() for value in header_rows[0]]
    header_indexes = {
        header.casefold(): index
        for index, header in enumerate(headers)
        if header
    }
    required_headers = (
        "VENDOR",
        "MCU",
        "PACKAGE",
        "VENDOR LOGO LINK",
        "PACKAGE LOGO LINK",
        "IS IT DONE",
        "DATE ADDED",
    )
    missing_headers = [
        header for header in required_headers if header.casefold() not in header_indexes
    ]
    if missing_headers:
        raise ExtractionError(
            f"Google Sheet '{resolved_sheet_name}' is missing required columns: "
            f"{', '.join(missing_headers)}. Found: {headers}"
        )

    vendor_index = header_indexes["vendor"]
    mcu_index = header_indexes["mcu"]
    package_index = header_indexes["package"]
    vendor_logo_index = header_indexes["vendor logo link"]
    package_logo_index = header_indexes["package logo link"]
    done_index = header_indexes["is it done"]
    date_index = header_indexes["date added"]

    last_column = _column_number_to_a1(len(headers))
    vendor_column = _column_number_to_a1(vendor_index + 1)
    mcu_column = _column_number_to_a1(mcu_index + 1)
    package_column = _column_number_to_a1(package_index + 1)
    vendor_logo_column = _column_number_to_a1(vendor_logo_index + 1)
    package_logo_column = _column_number_to_a1(package_logo_index + 1)
    done_column = _column_number_to_a1(done_index + 1)
    date_column = _column_number_to_a1(date_index + 1)

    # Find the selected worksheet metadata and, when available, the Google
    # Sheets table that contains the required columns. A table GridRange uses
    # zero-based, end-exclusive indexes. For a table starting on row 1,
    # endRowIndex is also the last 1-based row number covered by the table.
    selected_sheet_metadata = next(
        (
            sheet
            for sheet in metadata.get("sheets", [])
            if str(sheet.get("properties", {}).get("title") or "").strip()
            == resolved_sheet_name
        ),
        None,
    )

    table_data_start_row = 2
    table_data_end_row: int | None = None
    selected_table_name: str | None = None

    if selected_sheet_metadata:
        required_last_column_index = max(
            vendor_index,
            mcu_index,
            package_index,
            vendor_logo_index,
            package_logo_index,
            done_index,
            date_index,
        ) + 1

        matching_tables: list[dict[str, object]] = []
        for table in selected_sheet_metadata.get("tables", []):
            table_range = table.get("range", {})
            start_row_index = int(table_range.get("startRowIndex", 0))
            end_row_index = table_range.get("endRowIndex")
            start_column_index = int(table_range.get("startColumnIndex", 0))
            end_column_index = table_range.get("endColumnIndex")

            if end_row_index is None or end_column_index is None:
                continue

            # The table must include header row 1 and all required columns.
            if (
                start_row_index == 0
                and start_column_index <= min(
                    vendor_index,
                    mcu_index,
                    package_index,
                    vendor_logo_index,
                    package_logo_index,
                    done_index,
                    date_index,
                )
                and int(end_column_index) >= required_last_column_index
            ):
                matching_tables.append(table)

        if matching_tables:
            selected_table = matching_tables[0]
            selected_table_range = selected_table.get("range", {})
            table_data_start_row = int(
                selected_table_range.get("startRowIndex", 0)
            ) + 2
            table_data_end_row = int(selected_table_range["endRowIndex"])
            selected_table_name = str(selected_table.get("name") or "").strip() or None

    # Read existing values. Internal empty rows are returned as empty lists,
    # while trailing empty rows are omitted by the values API.
    existing_range = (
        f"{quoted_title}!A{table_data_start_row}:{last_column}{table_data_end_row}"
        if table_data_end_row is not None
        else f"{quoted_title}!A{table_data_start_row}:{last_column}"
    )
    existing_response = service.spreadsheets().values().get(
        spreadsheetId=spreadsheet_id,
        range=existing_range,
    ).execute()
    existing_rows = existing_response.get("values", [])

    existing_pairs: set[tuple[str, str]] = set()

    # Shared metadata maps. A non-empty logo link already present anywhere in
    # the sheet becomes the canonical value for that vendor/package.
    vendor_logo_links: dict[str, str] = {}
    vendor_logo_sources: dict[str, tuple[str, int]] = {}
    package_logo_links: dict[str, str] = {}
    package_logo_sources: dict[str, tuple[str, int]] = {}

    for offset, row in enumerate(existing_rows):
        row_number = table_data_start_row + offset
        vendor = str(row[vendor_index]).strip() if len(row) > vendor_index else ""
        mcu = str(row[mcu_index]).strip() if len(row) > mcu_index else ""
        package = (
            str(row[package_index]).strip() if len(row) > package_index else ""
        )
        vendor_logo = (
            str(row[vendor_logo_index]).strip()
            if len(row) > vendor_logo_index
            else ""
        )
        package_logo = (
            str(row[package_logo_index]).strip()
            if len(row) > package_logo_index
            else ""
        )

        if mcu and package:
            existing_pairs.add((mcu.casefold(), package.casefold()))

        if vendor and vendor_logo:
            vendor_key = vendor.casefold()
            existing_logo = vendor_logo_links.get(vendor_key)
            if existing_logo is not None and existing_logo != vendor_logo:
                source_vendor, source_row = vendor_logo_sources[vendor_key]
                raise ExtractionError(
                    f"Vendor '{vendor}' has conflicting VENDOR LOGO LINK values "
                    f"in rows {source_row} and {row_number}: "
                    f"'{existing_logo}' vs '{vendor_logo}'"
                )
            vendor_logo_links.setdefault(vendor_key, vendor_logo)
            vendor_logo_sources.setdefault(vendor_key, (vendor, row_number))

        if package and package_logo:
            package_key = package.casefold()
            existing_logo = package_logo_links.get(package_key)
            if existing_logo is not None and existing_logo != package_logo:
                source_package, source_row = package_logo_sources[package_key]
                raise ExtractionError(
                    f"Package '{package}' has conflicting PACKAGE LOGO LINK values "
                    f"in rows {source_row} and {row_number}: "
                    f"'{existing_logo}' vs '{package_logo}'"
                )
            package_logo_links.setdefault(package_key, package_logo)
            package_logo_sources.setdefault(package_key, (package, row_number))

    # Keep MCU + PACKAGE as the uniqueness key. Logo links are inferred from
    # existing sheet rows and attached to new rows when available.
    new_rows: list[tuple[str, str, str, str, str]] = []
    skipped_existing = 0
    for vendor, mcu, package in candidate_rows:
        key = (mcu.casefold(), package.casefold())
        if key in existing_pairs:
            skipped_existing += 1
            continue

        new_rows.append(
            (
                vendor,
                mcu,
                package,
                vendor_logo_links.get(vendor.casefold(), ""),
                package_logo_links.get(package.casefold(), ""),
            )
        )
        existing_pairs.add(key)

    # Determine the rows that can be reused. Prefer the declared Google Sheets
    # table range. Without table metadata, inspect through the last returned
    # value row and ensure enough top rows are considered for a new empty sheet.
    if table_data_end_row is not None:
        reusable_row_count = max(
            0,
            table_data_end_row - table_data_start_row + 1,
        )
    else:
        reusable_row_count = max(len(existing_rows), len(new_rows))

    padded_rows = list(existing_rows)
    if len(padded_rows) < reusable_row_count:
        padded_rows.extend([[] for _ in range(reusable_row_count - len(padded_rows))])

    empty_row_numbers: list[int] = []
    for offset, row in enumerate(padded_rows):
        # Only reuse a truly empty row. Formatting and data validation do not
        # appear as cell values, so formatted dropdown rows still count as empty.
        if not any(str(value).strip() for value in row):
            empty_row_numbers.append(table_data_start_row + offset)

    fill_count = min(len(new_rows), len(empty_row_numbers))
    rows_to_fill = new_rows[:fill_count]
    rows_to_append = new_rows[fill_count:]

    # Backfill blank logo cells in all existing rows before inserting new data.
    # The script writes only blank cells and never replaces a populated logo link.
    batch_data: list[dict[str, object]] = []
    vendor_logo_backfilled_rows: list[int] = []
    package_logo_backfilled_rows: list[int] = []

    for offset, row in enumerate(padded_rows):
        row_number = table_data_start_row + offset
        vendor = str(row[vendor_index]).strip() if len(row) > vendor_index else ""
        package = (
            str(row[package_index]).strip() if len(row) > package_index else ""
        )
        vendor_logo = (
            str(row[vendor_logo_index]).strip()
            if len(row) > vendor_logo_index
            else ""
        )
        package_logo = (
            str(row[package_logo_index]).strip()
            if len(row) > package_logo_index
            else ""
        )

        if vendor and not vendor_logo:
            shared_vendor_logo = vendor_logo_links.get(vendor.casefold())
            if shared_vendor_logo:
                batch_data.append(
                    {
                        "range": f"{quoted_title}!{vendor_logo_column}{row_number}",
                        "values": [[shared_vendor_logo]],
                    }
                )
                vendor_logo_backfilled_rows.append(row_number)

        if package and not package_logo:
            shared_package_logo = package_logo_links.get(package.casefold())
            if shared_package_logo:
                batch_data.append(
                    {
                        "range": f"{quoted_title}!{package_logo_column}{row_number}",
                        "values": [[shared_package_logo]],
                    }
                )
                package_logo_backfilled_rows.append(row_number)

    # Fill specific cells in the first empty table rows. Existing formatting and
    # dropdown validation are preserved because only target value cells are set.
    filled_row_numbers: list[int] = []
    for (
        vendor,
        mcu,
        package,
        vendor_logo,
        package_logo,
    ), row_number in zip(rows_to_fill, empty_row_numbers):
        filled_row_numbers.append(row_number)
        batch_data.extend(
            [
                {
                    "range": f"{quoted_title}!{vendor_column}{row_number}",
                    "values": [[vendor]],
                },
                {
                    "range": f"{quoted_title}!{mcu_column}{row_number}",
                    "values": [[mcu]],
                },
                {
                    "range": f"{quoted_title}!{package_column}{row_number}",
                    "values": [[package]],
                },
                {
                    "range": f"{quoted_title}!{done_column}{row_number}",
                    "values": [["NO"]],
                },
                {
                    "range": f"{quoted_title}!{date_column}{row_number}",
                    "values": [[date_added]],
                },
            ]
        )

        if vendor_logo:
            batch_data.append(
                {
                    "range": f"{quoted_title}!{vendor_logo_column}{row_number}",
                    "values": [[vendor_logo]],
                }
            )

        if package_logo:
            batch_data.append(
                {
                    "range": f"{quoted_title}!{package_logo_column}{row_number}",
                    "values": [[package_logo]],
                }
            )

    batch_response: dict[str, object] | None = None
    if batch_data:
        batch_response = service.spreadsheets().values().batchUpdate(
            spreadsheetId=spreadsheet_id,
            body={
                "valueInputOption": "USER_ENTERED",
                "data": batch_data,
            },
        ).execute()

    # Normally the existing table has enough blank rows. If it does not, append
    # only the overflow, allowing Google Sheets to expand the table as before.
    append_response: dict[str, object] | None = None
    if rows_to_append:
        append_values: list[list[object]] = []
        for vendor, mcu, package, vendor_logo, package_logo in rows_to_append:
            row: list[object] = [""] * len(headers)
            row[vendor_index] = vendor
            row[mcu_index] = mcu
            row[package_index] = package
            row[vendor_logo_index] = vendor_logo
            row[package_logo_index] = package_logo
            row[done_index] = "NO"
            row[date_index] = date_added
            append_values.append(row)

        append_response = service.spreadsheets().values().append(
            spreadsheetId=spreadsheet_id,
            range=f"{quoted_title}!A:{last_column}",
            valueInputOption="USER_ENTERED",
            insertDataOption="INSERT_ROWS",
            body={"values": append_values},
        ).execute()

    return {
        "dry_run": False,
        "sheet_name": resolved_sheet_name,
        "table_name": selected_table_name,
        "candidate_pairs": len(candidate_rows),
        "written": len(new_rows),
        "filled_existing_rows": len(rows_to_fill),
        "filled_row_numbers": filled_row_numbers,
        "appended": len(rows_to_append),
        "existing": skipped_existing,
        "missing_package_mcus": missing_package_mcus,
        "missing_vendor_mcus": missing_vendor_mcus,
        "known_vendor_logo_links": len(vendor_logo_links),
        "known_package_logo_links": len(package_logo_links),
        "vendor_logo_backfilled": len(vendor_logo_backfilled_rows),
        "vendor_logo_backfilled_rows": vendor_logo_backfilled_rows,
        "package_logo_backfilled": len(package_logo_backfilled_rows),
        "package_logo_backfilled_rows": package_logo_backfilled_rows,
        "batch_updated_cells": (
            batch_response.get("totalUpdatedCells", 0)
            if batch_response
            else 0
        ),
        "appended_range": (
            append_response.get("updates", {}).get("updatedRange")
            if append_response
            else None
        ),
    }


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Extract boards added after the previous highest mikroSDK release, "
            "up to the selected release date, then determine EmbeddedWiki "
            "eligibility from onboard mikroBUS presence or an SDK-configured "
            "shield expansion option, together with device-confirmed mikroSDK "
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
        "--github-repository-url",
        help=(
            "Override the GitHub repository web URL used for board.h links. "
            "By default, GITHUB_REPOSITORY or the origin remote is used."
        ),
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
        "--update-google-sheet",
        action="store_true",
        help=(
            "Fill the first empty table rows with unique MCU/package pairs from "
            "EmbeddedWiki-eligible boards, appending only if the table is full"
        ),
    )
    parser.add_argument(
        "--sheet-url",
        default=(
            os.environ.get("MCU_LIST_SHEET_URL")
            or os.environ.get("GOOGLE_SHEET_URL")
            or os.environ.get("SHEET_URL")
        ),
        help=(
            "Editable Google Sheet URL. Defaults to MCU_LIST_SHEET_URL, "
            "GOOGLE_SHEET_URL, or SHEET_URL"
        ),
    )
    parser.add_argument(
        "--sheet-name",
        default=(
            os.environ.get("MCU_LIST_SHEET_NAME")
            or os.environ.get("GOOGLE_SHEET_NAME")
            or os.environ.get("SHEET_NAME")
        ),
        help="Target Google Sheet tab name; otherwise the URL gid is resolved",
    )
    parser.add_argument(
        "--google-credentials-path",
        type=Path,
        default=(
            Path(os.environ["GOOGLE_CREDENTIALS_PATH"])
            if os.environ.get("GOOGLE_CREDENTIALS_PATH")
            else (
                Path(os.environ["GOOGLE_APPLICATION_CREDENTIALS"])
                if os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
                else None
            )
        ),
        help=(
            "Path to Google service-account JSON. Defaults to "
            "GOOGLE_CREDENTIALS_PATH or GOOGLE_APPLICATION_CREDENTIALS"
        ),
    )
    parser.add_argument(
        "--sheet-date-added",
        help="DATE ADDED value in YYYY-MM-DD format (default: today's date)",
    )
    parser.add_argument(
        "--sheet-dry-run",
        action="store_true",
        help="Build and log Google Sheet rows without writing them",
    )
    parser.add_argument(
        "--format",
        choices=("json", "markdown", "mattermost", "plain"),
        default="json",
        help="Output format: json, full markdown, Mattermost markdown, or plain text (default: json)",
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
            github_repository_url=args.github_repository_url,
        )

        formatter = {
            "json": format_json,
            "markdown": format_markdown,
            "mattermost": format_mattermost,
            "plain": format_plain,
        }[args.format]
        output = formatter(result)

        if args.output:
            destination = args.output.expanduser()
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(output, encoding="utf-8")
        else:
            sys.stdout.write(output)

        if args.update_google_sheet or args.sheet_dry_run:
            if not args.sheet_url:
                raise ExtractionError(
                    "Google Sheet update requested, but no sheet URL was provided. "
                    "Pass --sheet-url or set MCU_LIST_SHEET_URL."
                )

            credentials_path = args.google_credentials_path
            if credentials_path is None:
                local_credentials = Path(__file__).with_name("service-account.json")
                if local_credentials.is_file():
                    credentials_path = local_credentials
                elif args.sheet_dry_run:
                    credentials_path = local_credentials
                else:
                    raise ExtractionError(
                        "Google Sheet update requested, but no service-account JSON "
                        "path was provided. Pass --google-credentials-path or set "
                        "GOOGLE_CREDENTIALS_PATH."
                    )

            sheet_result = update_google_sheet(
                result=result,
                sheet_url=args.sheet_url,
                credentials_path=credentials_path,
                sheet_name=args.sheet_name,
                date_added=args.sheet_date_added,
                dry_run=args.sheet_dry_run,
            )
            print(
                "Google Sheet update: "
                + json.dumps(sheet_result, ensure_ascii=False),
                file=sys.stderr,
            )

        return 0
    except ExtractionError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
