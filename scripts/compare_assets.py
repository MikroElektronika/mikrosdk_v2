import argparse, requests

import support as support

def get_headers(api, token):
    if api:
        return {
            'Authorization': f'token {token}'
        }
    else:
        return {
            'Authorization': f'Bearer {token}',
            'Accept': 'application/octet-stream'
        }

def fetch_specified_release_version(repo, token, tag):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return support.get_specified_release(response.json(), tag)

def fetch_previous_release_version(repo, token):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return support.get_previous_release(response.json())

def fetch_latest_release_version(repo, token):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return support.get_latest_release(response.json())

def fetch_existing_asset_names(release):
    return [asset['name'] for asset in release['assets']]

def main(token, repo, current_tag, previous_tag):
    found_dif = 0

    if current_tag != "latest":
        current_release = fetch_specified_release_version(repo, token, current_tag)
    else:
        current_release = fetch_latest_release_version(repo, token)

    if previous_tag != "latest":
        previous_release = fetch_specified_release_version(repo, token, previous_tag)
    else:
        previous_release = fetch_previous_release_version(repo, token)

    current_assets = [package.replace('.7z', '') for package in fetch_existing_asset_names(current_release)]
    previous_assets = [package.replace('.7z', '') for package in fetch_existing_asset_names(previous_release)]

    for current_asset in current_assets:
        if current_asset not in previous_assets:
            print(f"\033[93m{current_release['tag_name']} release has {current_asset} which is not present in {previous_release['tag_name']}!")
            # Write the line to a file
            with open("result_compare.txt", "a") as file:
                file.write(f'{current_release['tag_name']} release has {current_asset} which is not present in {previous_release['tag_name']}!\n')
            found_dif = 1

    for previous_asset in previous_assets:
        if previous_asset not in current_assets:
            print(f"\033[93m{previous_release['tag_name']} release has {previous_asset} which is not present in {current_release['tag_name']}!")
            # Write the line to a file
            with open("result_compare.txt", "a") as file:
                file.write(f'{previous_release['tag_name']} release has {previous_asset} which is not present in {current_release['tag_name']}!\n')
            found_dif = 1

    if found_dif == 0:
        print(f"\033[92mThere is no difference in asset names between {current_release['tag_name']} and {previous_release['tag_name']} releases!")

    return


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Compare release assets for 2 releases.")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("--current_tag", help="Tag name for the current release", default="latest")
    parser.add_argument("--previous_tag", help="Tag name for the previous release", default="latest")
    args = parser.parse_args()
    print("Starting the comparation process...")
    main(args.token, args.repo, args.current_tag, args.previous_tag)
    print("Comparation process completed.")