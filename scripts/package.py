import os, sys, py7zr, requests

from elasticsearch import Elasticsearch

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
            relative_path = os.path.relpath(root, source_folder)
            if '.github' in relative_path.split(os.sep):
                continue
            if '.git' in relative_path.split(os.sep):
                continue
            if 'scripts' in relative_path.split(os.sep):
                continue
            for file in files:
                file_path = os.path.join(root, file)
                # Exclude the archive itself
                if file_path == archive_path:
                    continue
                archive.write(file_path, os.path.join(version, 'src', os.path.relpath(file_path, source_folder)))

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
    return None

def get_release_id(repo, tag_name, token):
    """Get the release ID for a given tag name."""
    url = f'https://api.github.com/repos/{repo}/releases/tags/{tag_name}'
    headers = {'Authorization': f'token {token}'}
    response = requests.get(url, headers=headers)
    response.raise_for_status()
    return response.json()['id']

if __name__ == '__main__':
    token = sys.argv[1]
    repo = sys.argv[2]
    tag_name = sys.argv[3]

    # Elasticsearch details
    es = Elasticsearch(["https://search-mikroe-eotds45vmgevl75dl75hjanrzm.us-west-2.es.amazonaws.com"])
    index_name = 'github_test_index'

    # Assuming the repository is checked out at the root directory
    repo_dir = os.getcwd()
    version = tag_name.split('-')[1]

    manifest_folder = find_manifest_folder(repo_dir)
    if manifest_folder:
        archive_path = os.path.join(repo_dir, 'mikrosdk.7z')
        print('Creating archive: %s' % archive_path)
        create_7z_archive(version, repo_dir, archive_path)
        print('Archive created successfully: %s' % archive_path)

        # Get the release ID and upload the asset
        release_id = get_release_id(repo, tag_name, token)
        upload_result = upload_asset_to_release(repo, release_id, archive_path, token)
        doc = {
            'name': upload_result['name'],
            'display_name': "mikroSDK",
            'author': 'MIKROE',
            'hidden': False,
            'type': 'mcu',
            'version': tag_name.replace('mikroSDK-', ''),
            'created_at' : upload_result['created_at'],
            'updated_at' : upload_result['updated_at'],
            'category': 'MCU support',
            'download_link': upload_result['browser_download_url'],  # Adjust as needed for actual URL
            'package_changed': True
        }

        print('Asset details: \n%s' % doc)
        print('Asset uploaded successfully to release ID: %s' % release_id)
