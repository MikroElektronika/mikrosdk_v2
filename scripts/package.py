import os, re, py7zr, \
       requests, argparse, \
       json, hashlib

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
            if re.search(r'(\.git)|(scripts)|(templates)|(changelog)|(resources)', os.path.relpath(root, source_folder)):
                continue
            for file in files:
                file_path = os.path.join(root, file)
                # Exclude the archive itself
                if file_path == archive_path:
                    continue
                archive.write(file_path, os.path.join(version, 'src', os.path.relpath(file_path, source_folder)))

def create_custom_archive(source_folder, archive_path):
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

def zip_bsp_related_files(archive_path, repo_dir):
    support.copy_files_with_structure(
        os.path.join(repo_dir, 'bsp'),
        os.path.join(repo_dir, 'output/bsps'),
        [
            'board.h',
            'mcu_card.h'
        ]
    )
    support.copy_files_with_structure(
        repo_dir,
        os.path.join(repo_dir, 'output/bsps'),
        [
            'mcu_definitions.h',
            'can_definitions.h',
            'dma_definitions.h'
        ]
    )
    create_custom_archive('output', archive_path)

def hash_file(filename):
    """Generate MD5 hash of a file."""
    hash_md5 = hashlib.md5()
    with open(filename, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def hash_directory_contents(directory):
    """Generate a hash for the contents of a directory."""
    all_hashes = []
    for root, dirs, files in os.walk(directory):
        dirs.sort()  # Ensure directory traversal is in a consistent order
        files.sort()  # Ensure file traversal is in a consistent order
        for filename in files:
            file_path = os.path.join(root, filename)
            file_hash = hash_file(file_path)
            all_hashes.append(file_hash)

    # Combine all file hashes into one hash
    combined_hash = hashlib.md5("".join(all_hashes).encode()).hexdigest()
    return combined_hash

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("tag_name", help="Tag name, e.g., 'mikroSDK-2.11.1'")
    args = parser.parse_args()

    repo_dir = os.getcwd()

    # Set appropriate SDK version
    support.update_sdk_version(repo_dir, args.tag_name.replace('mikroSDK-', ''))

    # Assuming the repository is checked out at the root directory
    manifest_folder = find_manifest_folder(repo_dir)
    version = json.load(open(os.path.join(manifest_folder ,'manifest.json')))['sdk-version']

    # Set copyright year for all files to current year
    support.update_copyright_year(repo_dir)

    # Get the release ID used to upload assets
    release_id = get_release_id(args.repo, f'mikroSDK-{version}', args.token)

    metadata_content = {}
    if manifest_folder:
        archive_path = os.path.join(repo_dir, 'mikrosdk.7z')
        print('Creating archive: %s' % archive_path)
        create_7z_archive(version, repo_dir, archive_path)
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('mikrosdk', release_id))

    if os.path.exists(os.path.join(repo_dir, 'resources/images')):
        archive_path = os.path.join(repo_dir, 'images.7z')
        print('Creating archive: %s' % archive_path)
        create_custom_archive('resources/images', archive_path)
        os.chdir(repo_dir)
        metadata_content['images'] = {'hash': hash_directory_contents(os.path.join(repo_dir, 'resources/images'))}
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('images', release_id))

    if os.path.exists(os.path.join(repo_dir, 'templates/necto')):
        archive_path = os.path.join(repo_dir, 'templates.7z')
        print('Creating archive: %s' % archive_path)
        create_custom_archive('templates/necto', archive_path)
        os.chdir(repo_dir)
        metadata_content['templates'] = {'hash': hash_directory_contents(os.path.join(repo_dir, 'templates/necto'))}
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('templates', release_id))

    if os.path.exists(os.path.join(repo_dir, 'resources/queries')):
        archive_path = os.path.join(repo_dir, 'queries.7z')
        print('Creating archive: %s' % archive_path)
        create_custom_archive('resources/queries', archive_path)
        os.chdir(repo_dir)
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('queries', release_id))

    # BSP asset
    archive_path = os.path.join(repo_dir, 'bsps.7z')
    print('Creating archive: %s' % archive_path)
    zip_bsp_related_files(archive_path, repo_dir)
    upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token)
    print('Asset "%s" uploaded successfully to release ID: %s' % ('bsps', release_id))

    os.makedirs(os.path.join(repo_dir, 'tmp'), exist_ok=True)
    with open(os.path.join(repo_dir, 'tmp/metadata.json'), 'w') as metadata:
        json.dump(metadata_content, metadata, indent=4)
    metadata.close()
    upload_result = upload_asset_to_release(args.repo, release_id, os.path.join(repo_dir, 'tmp/metadata.json'), args.token)
