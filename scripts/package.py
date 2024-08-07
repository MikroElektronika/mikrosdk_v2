import os, re, py7zr, requests, argparse, json

import support as support

def find_manifest_folder(base_dir):
    """Find the folder containing 'manifest.json'."""
    for root, dirs, files in os.walk(base_dir):
        if 'manifest.json' in files:
            return root
    return None

def create_7z_archive(version, source_folder, archive_path):
    """Create a .7z archive from a source folder with a specific folder structure, excluding the .github folder."""
    with py7zr.SevenZipFile(archive_path, 'w') as archive:
        for root, dirs, files in os.walk(source_folder):
            if re.search(r'(\.git)|(scripts)|(templates)', os.path.relpath(root, source_folder)):
                continue
            for file in files:
                file_path = os.path.join(root, file)
                # Exclude the archive itself
                if file_path == archive_path:
                    continue
                archive.write(file_path, os.path.join(version, 'src', os.path.relpath(file_path, source_folder)))

def create_template_archive(source_folder, archive_path):
    """Create a .7z archive from a source folder with a specific folder structure."""
    with py7zr.SevenZipFile(archive_path, 'w') as archive:
        os.chdir(source_folder)
        archive.writeall('./')
        os.chdir('..')

def upload_asset_to_release(repo, release_id, asset_path, token):
    """Upload an asset to a specific GitHub release."""
    url = f'https://uploads.github.com/repos/{repo}/releases/{release_id}/assets?name={os.path.basename(asset_path)}'
    headers = {
        'Authorization': f'token {token}',
        'Content-Type': 'application/x-7z-compressed'
    }
    with open(asset_path, 'rb') as file:
        response = requests.post(url, headers=headers, data=file)
        response.raise_for_status()
        print(f'Uploaded asset: {os.path.basename(asset_path)} to release ID: {release_id}')
        return response.json()

def get_release_id(repo, tag_name, token):
    """Get the release ID for a given tag name."""
    url = f'https://api.github.com/repos/{repo}/releases/tags/{tag_name}'
    headers = {'Authorization': f'token {token}'}
    response = requests.get(url, headers=headers)
    response.raise_for_status()
    return response.json()['id']

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    args = parser.parse_args()

    # Assuming the repository is checked out at the root directory
    repo_dir = os.getcwd()
    manifest_folder = find_manifest_folder(repo_dir)
    version = json.load(open(os.path.join(manifest_folder ,'manifest.json')))['sdk-version']

    # Set copyright year for all files to current year
    support.update_copyright_year(repo_dir)

    if manifest_folder:
        archive_path = os.path.join(repo_dir, 'mikrosdk.7z')
        print('Creating archive: %s' % archive_path)
        create_7z_archive(version, repo_dir, archive_path)
        print('Archive created successfully: %s' % archive_path)

        # Get the release ID and upload the asset
        release_id = get_release_id(args.repo, f'mikroSDK-{version}', args.token)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)

        print('Asset "%s" uploaded successfully to release ID: %s' % ('mikrosdk', release_id))

    if os.path.exists(os.path.join(repo_dir, 'templates')):
        archive_path = os.path.join(repo_dir, 'templates.7z')
        print('Creating archive: %s' % archive_path)
        create_template_archive('templates', archive_path)
        print('Archive created successfully: %s' % archive_path)

        # Get the release ID and upload the asset
        release_id = get_release_id(args.repo, f'mikroSDK-{version}', args.token)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)

        print('Asset "%s" uploaded successfully to release ID: %s' % ('templates', release_id))
