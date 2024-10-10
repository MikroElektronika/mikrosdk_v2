import os, requests, argparse
import support as support

from datetime import datetime
from packaging.version import Version

# Gets latest release headers from repository
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

def write_output_to_file(file, content):
    with open(file, 'w') as file_write:
        file_write.write(content)
    file_write.close()

def find_file(root_folder, filename):
    for dirpath, dirnames, filenames in os.walk(root_folder):
        if filename in filenames:
            return os.path.join(dirpath, filename), dirpath
    return None, None

def fetch_latest_release_version(repo, token):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return support.get_latest_release(response.json())

def edit_changelog(version):
    found_file, file_dir = find_file(os.path.join(os.getcwd(), "changelog"), "new_hw.md")

    if found_file:
        current_date = datetime.now().strftime("%Y-%m-%d")
        os.rename(found_file, os.path.join(file_dir, f'{current_date}.md'))
        with open(os.path.join(file_dir, f'{current_date}.md'), 'r') as hw_changelog_file:
            board_changelog = hw_changelog_file.read()
        hw_changelog_file.close()
        board_changelog = board_changelog.replace('`DATE`', current_date).replace('#date', f'#{current_date}')
        with open(os.path.join(file_dir, f'{current_date}.md'), 'w') as hw_changelog_file:
            hw_changelog_file.write(board_changelog)
        hw_changelog_file.close()

        os.makedirs(os.path.join(file_dir, f'v{version}', 'new_hw'), exist_ok=True)
        os.rename(os.path.join(file_dir, f'{current_date}.md'), os.path.join(file_dir, f'v{version}', f'new_hw/{current_date}.md'))

        if os.path.isfile(os.path.join(file_dir, 'new_hw.md')):
            os.remove(os.path.join(file_dir, 'new_hw.md'))

        write_output_to_file(os.path.join(os.getcwd(), 'sdk_tag.txt'), version)
    else:
        # Extract and sort versions, removing the 'v' prefix
        # Take the ighest version present in the repo itself, not github
        latest_version = max(os.listdir(os.path.join(os.getcwd(), 'changelog')), key=lambda v: Version(v.lstrip('v'))).lstrip('v')
        write_output_to_file(os.path.join(os.getcwd(), 'sdk_tag.txt'), latest_version)

if __name__ == '__main__':
    # Get arguments
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("token", type=str, help="GitHub Token")
    parser.add_argument("repo", type=str, help="Repository name, e.g., 'username/repo'")
    args = parser.parse_args()

    release = fetch_latest_release_version(args.repo, args.token)
    edit_changelog(release['tag_name'].replace('mikroSDK-', ''))
