#!/usr/bin/env python3
"""Dispatch a mikroSDK database update to general_packages and optionally wait."""

from __future__ import annotations

import argparse
import json
import os
import time
import urllib.error
import urllib.request
import uuid

from database_assets import normalize_channel


TARGET_REPO = "MikroElektronika/general_packages"
WORKFLOW_FILE = "database-external-update.yml"


def api(token: str, url: str, *, method="GET", body=None):
    data = None if body is None else json.dumps(body).encode("utf-8")
    request = urllib.request.Request(url, data=data, method=method)
    request.add_header("Accept", "application/vnd.github+json")
    request.add_header("Authorization", f"Bearer {token}")
    request.add_header("X-GitHub-Api-Version", "2022-11-28")
    if data is not None:
        request.add_header("Content-Type", "application/json")
    try:
        with urllib.request.urlopen(request) as response:
            payload = response.read()
            return json.loads(payload) if payload else None
    except urllib.error.HTTPError as exc:
        details = exc.read().decode("utf-8", errors="replace")
        raise RuntimeError(f"GitHub API failed ({exc.code}): {details}") from exc


def wait_for_run(token: str, request_id: str, timeout_minutes: int) -> None:
    list_url = (
        f"https://api.github.com/repos/{TARGET_REPO}/actions/workflows/"
        f"{WORKFLOW_FILE}/runs?event=repository_dispatch&per_page=50"
    )
    title = f"Database update: {request_id}"
    deadline = time.monotonic() + timeout_minutes * 60
    run = None
    while time.monotonic() < deadline:
        response = api(token, list_url)
        run = next(
            (item for item in response.get("workflow_runs", []) if item.get("display_title") == title),
            None,
        )
        if run:
            break
        print("Waiting for general_packages workflow...")
        time.sleep(10)
    if not run:
        raise TimeoutError(f"Could not find {title}")

    print(f"Database workflow: {run['html_url']}")
    while time.monotonic() < deadline:
        run = api(token, run["url"])
        print(f"status={run.get('status')}, conclusion={run.get('conclusion')}")
        if run.get("status") == "completed":
            if run.get("conclusion") != "success":
                raise RuntimeError(
                    f"Database update failed with {run.get('conclusion')}: {run['html_url']}"
                )
            return
        time.sleep(15)
    raise TimeoutError(f"Timed out waiting for {run['html_url']}")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--token", default=os.environ.get("GENERAL_PACKAGES_TOKEN"))
    parser.add_argument("--channel", required=True)
    parser.add_argument("--sdk-version", required=True)
    parser.add_argument("--source-ref", default=os.environ.get("GITHUB_SHA", ""))
    parser.add_argument("--wait", action="store_true")
    parser.add_argument("--timeout-minutes", type=int, default=240)
    args = parser.parse_args()
    if not args.token:
        parser.error("--token or GENERAL_PACKAGES_TOKEN is required")

    request_id = uuid.uuid4().hex
    payload = {
        "request_id": request_id,
        "source_repo": os.environ.get("GITHUB_REPOSITORY", "MikroElektronika/mikrosdk_v2"),
        "source_ref": args.source_ref,
        "channel": normalize_channel(args.channel),
        "operation": "sdk",
        "core_release": "latest",
        "core_version": "latest",
        "sdk_version": args.sdk_version,
        "mcus_only": False,
        "skip_mchp_packs": False,
    }
    api(
        args.token,
        f"https://api.github.com/repos/{TARGET_REPO}/dispatches",
        method="POST",
        body={"event_type": "database-update", "client_payload": payload},
    )
    print(f"Dispatched database update {request_id}")
    if args.wait:
        wait_for_run(args.token, request_id, args.timeout_minutes)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
