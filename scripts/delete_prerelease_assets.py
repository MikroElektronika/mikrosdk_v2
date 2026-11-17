import sys, time, \
       requests, argparse

## Removes ALL assets from a GitHub PRE-RELEASE.
## Published (non pre-release) and draft releases are never touched -
## the script aborts if the release is not marked as pre-release.

API_URL = 'https://api.github.com'

def get_headers(token):
    return {
        'Authorization': f'token {token}',
        'Accept': 'application/vnd.github+json',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
    }

def get_release_by_tag(session, repo, tag_name):
    """Get the release object for a given tag name."""
    response = session.get(f'{API_URL}/repos/{repo}/releases/tags/{tag_name}')
    response.raise_for_status()
    return response.json()

def get_release_by_id(session, repo, release_id):
    """Get the release object for a given release ID."""
    response = session.get(f'{API_URL}/repos/{repo}/releases/{release_id}')
    response.raise_for_status()
    return response.json()

def assert_prerelease(release):
    """Abort if the release is not an (undrafted) pre-release."""
    if release.get('draft') or not release.get('prerelease'):
        print(
            f'\033[91mABORTING: release "{release.get("name") or release.get("tag_name")}" '
            f'(ID: {release["id"]}) is NOT a pre-release '
            f'(prerelease={release.get("prerelease")}, draft={release.get("draft")}). '
            f'Assets will not be deleted.\033[0m'
        )
        sys.exit(1)

def get_all_release_assets(session, repo, release_id):
    """Fetch all assets of a release, paginating through results."""
    all_assets = []
    page = 1
    while True:
        response = session.get(
            f'{API_URL}/repos/{repo}/releases/{release_id}/assets',
            params={'page': page, 'per_page': 100}
        )
        response.raise_for_status()
        assets = response.json()

        # If no more assets, break out of loop
        if not assets:
            break

        all_assets += assets
        page += 1

    return all_assets

def delete_asset(session, asset, max_retries=5):
    """Delete a single asset, retrying on rate limits / transient errors."""
    for attempt in range(1, max_retries + 1):
        response = session.delete(asset['url'])

        if response.status_code in (204, 404):
            # 404 - asset already gone, treat as deleted
            return True

        if response.status_code in (403, 429) or response.status_code >= 500:
            retry_after = response.headers.get('Retry-After')
            reset_at = response.headers.get('X-RateLimit-Reset')
            if retry_after:
                wait = int(retry_after)
            elif response.headers.get('X-RateLimit-Remaining') == '0' and reset_at:
                wait = max(int(reset_at) - int(time.time()), 1)
            else:
                wait = 2 ** attempt
            print(f'\033[93mGot {response.status_code} for {asset["name"]}, retrying in {wait}s ({attempt}/{max_retries})\033[0m')
            time.sleep(wait)
            continue

        response.raise_for_status()

    print(f'\033[91mFailed to delete asset: {asset["name"]}\033[0m')
    return False

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Delete ALL assets from a GitHub PRE-RELEASE (never from published releases).")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("tag_name", help="Tag name, e.g., 'mikroSDK-2.11.1'")
    parser.add_argument("--dry-run", action="store_true", help="Only list assets that would be deleted")
    parser.add_argument("-y", "--yes", action="store_true", help="Skip the confirmation prompt")
    parser.add_argument("--recheck-every", type=int, default=50, help="Re-verify release is still a pre-release every N deletions")
    args = parser.parse_args()

    session = requests.Session()
    session.headers.update(get_headers(args.token))

    # Fetch the release and make sure it is a pre-release
    release = get_release_by_tag(session, args.repo, args.tag_name)
    assert_prerelease(release)
    release_id = release['id']

    assets = get_all_release_assets(session, args.repo, release_id)
    print(f'Pre-release "{release.get("name") or args.tag_name}" (ID: {release_id}) has {len(assets)} assets.')

    if not assets:
        sys.exit(0)

    if args.dry_run:
        for asset in assets:
            print(f'  [dry-run] would delete: {asset["name"]}')
        sys.exit(0)

    if not args.yes:
        answer = input(f'Delete ALL {len(assets)} assets from pre-release "{args.tag_name}"? Type the tag name to confirm: ')
        if answer.strip() != args.tag_name:
            print('Confirmation did not match. Aborting.')
            sys.exit(1)

    deleted = 0
    failed = []
    for index, asset in enumerate(assets, start=1):
        # Periodically re-verify, in case the release got published meanwhile
        if index % args.recheck_every == 0:
            assert_prerelease(get_release_by_id(session, args.repo, release_id))

        if delete_asset(session, asset):
            deleted += 1
            print(f'\033[91m[{index}/{len(assets)}] Asset deleted: {asset["name"]}\033[0m')
        else:
            failed.append(asset['name'])

    print(f'\033[92mDone. Deleted {deleted}/{len(assets)} assets from pre-release "{args.tag_name}".\033[0m')
    if failed:
        print(f'\033[91mFailed to delete {len(failed)} assets:\033[0m')
        for name in failed:
            print(f'  {name}')
        sys.exit(1)
