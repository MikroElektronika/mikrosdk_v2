import requests, py7zr, zipfile, io, os, re, json, shutil
import chardet  # For detecting file encoding
from datetime import datetime

def get_previous_release(releases, prerelases=None):
    ''' Fetch the previously released version '''
    for counter, release in enumerate(releases):
        if not release['draft']:
            if prerelases:
                if release['prerelease']:
                    continue
            if counter + 1 < len(releases):
                return releases[counter + 1]
            else:
                return None
    return None

def get_latest_release(releases):
    ''' Fetch the latest released version '''
    return next((release for release in releases if not release['prerelease'] and not release['draft']), None)

def get_specified_release(releases, release_version):
    ''' Fetch the latest released version '''
    return next((release for release in releases if release_version == release['tag_name']), None)

def determine_archive_type(byte_stream):
    '''
    Implement logic to determine the archive type, e.g., by file extension or magic number
    For simplicity, let's assume byte_stream has a 'name' attribute (e.g., a file-like object)
    '''
    byte_stream.seek(0)
    signature = byte_stream.read(4)
    byte_stream.seek(0)
    if signature == b'PK\x03\x04':  # ZIP magic number, it is what it is
        return 'zip'
    else:
        return '7z'

def extract_archive_from_url(url, destination, token=None, log_download_link=False):
    """
    Extract the contents of an archive (7z or zip) from a URL directly
    in memory, without downloading the file.
    """
    if log_download_link:
        print(f"Download link: {url}")
    headers = {
        'Authorization': f'token {token}',
        'Accept': 'application/octet-stream'
    }
    if 'github' in url:
        response = requests.get(url, headers=headers, stream=True)
    else:
        response = requests.get(url, stream=True)

    response.raise_for_status()

    if response.status_code == 200: ## Response OK?
        with io.BytesIO() as byte_stream:

            for chunk in response.iter_content(chunk_size=8192):
                byte_stream.write(chunk)

            byte_stream.seek(0)

            archive_type = determine_archive_type(byte_stream)

            if archive_type == '7z':
                with py7zr.SevenZipFile(byte_stream, mode='r') as archive:
                    archive.extractall(path=destination)
            elif archive_type == 'zip':
                with zipfile.ZipFile(byte_stream, mode='r') as archive:
                    for info in archive.infolist():
                        archive.extract(info, path=destination)
            else:
                raise ValueError("Unsupported archive type")
    else:
        raise Exception(f"Failed to download file: status code {response.status_code}")

def fetch_version_from_asset(asset_path):
    """
    Function to retrieve current version from manifest
    """
    for root, subdirs, files in os.walk(asset_path):
        for file_name in files:
            if 'manifest.json' == file_name:
                return json.load(open(os.path.join(root, file_name)))['sdk-version']
            else:
                continue
    return None

def replace_copyright_year(file_path):
    """
    Function to replace '${COPYRIGHT_YEAR}' with current year
    for the provided literal path to file_path
    """
    # Detect file encoding
    with open(file_path, 'rb') as f:
        raw_data = f.read()
        encoding_result = chardet.detect(raw_data)
        file_encoding = encoding_result['encoding']
    f.close()
    # Read the file with detected encoding
    with open(file_path, 'r', encoding=file_encoding) as file:
        file_content = file.read()
    file.close()
    # Get current year
    current_year = datetime.now().year
    # Perform the replacement using regular expression
    file_content = re.sub(r'\${COPYRIGHT_YEAR}', str(current_year), file_content)
    # Write back to the file with the same encoding
    with open(file_path, 'w', encoding=file_encoding) as file:
        file.write(file_content)
    file.close()

def update_copyright_year(directory):
    """
    Function to scan directory and update
    copyright year recursivelly
    """
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.endswith('.h') or filename.endswith('.c') or 'LICENSE' == filename:
                file_path = os.path.join(root, filename)
                if 'thirdparty' in file_path:
                    if re.search('callbacks_default|usb_isr_routines', file_path):
                        print('Updating file "%s"' % file_path)
                        replace_copyright_year(file_path)
                else:
                    print('Updating file "%s"' % file_path)
                    replace_copyright_year(file_path)

def copy_files_with_structure(src_root, dst_root, filenames):
    """
    Copy files named in `filenames` from `src_root` to `dst_root` while preserving the folder structure.

    Args:
        src_root (str): Source root directory to search for files.
        dst_root (str): Destination root directory where files will be copied.
        filenames (list of str): List of filenames to copy.
    """
    # Ensure filenames is a list
    if not isinstance(filenames, list):
        raise TypeError("filenames should be a list of strings")

    # Iterate over each directory in the source root
    for dirpath, _, files in os.walk(src_root):
        if dst_root in dirpath:
            continue
        for filename in filenames:
            if filename in files:
                # Construct full file path
                src_file = os.path.join(dirpath, filename)
                # Construct destination path preserving the folder structure
                relative_path = os.path.relpath(dirpath, src_root)
                dst_dir = os.path.join(dst_root, relative_path)

                # Ensure the destination directory exists
                if not os.path.exists(dst_dir):
                    os.makedirs(dst_dir)

                # Construct destination file path
                dst_file = os.path.join(dst_dir, filename)
                # Copy the file
                shutil.copy2(src_file, dst_file)
                print(f"Copied {src_file} to {dst_file}")

def filter_multiple_empty_rows(file_path):
    # Read the content of the markdown file
    with open(file_path, 'r') as file:
        content = file.readlines()
    file.close()

    # Remove any occurrence of double empty rows
    filtered_content = []
    previous_line_empty = False

    for line in content:
        if line.strip() == "":
            if not previous_line_empty:
                filtered_content.append(line)
            previous_line_empty = True
        else:
            filtered_content.append(line)
            previous_line_empty = False

    # Write the filtered content back to the file (or a new file)
    with open(file_path, 'w') as file:
        file.writelines(filtered_content)
    file.close()

# Function to increment the version number
def increment_manifest_version(version):
    parts = version.split('.')
    parts[-1] = str(int(parts[-1]) + 1)  # Increment the last part of the version
    return '.'.join(parts)

def update_sdk_version(directory, version):
    """
    Function to scan directory and update
    copyright year recursivelly
    """
    current_files = [
        "README.md",
        "manifest.json",
        "CMakeLists.txt"
    ]
    for root, _, files in os.walk(directory):
        for filename in files:
            file_path = os.path.join(root, filename)
            if filename in current_files:
                with open(file_path, 'r') as file:
                    file_content = file.read()
                file.close()
                if '${MIKROSDK_CURRENT_VERSION}' in file_content:
                    print('Updating file "%s"' % file_path)
                    with open(file_path, 'w') as file:
                        file.write(file_content.replace('${MIKROSDK_CURRENT_VERSION}', version))
                    file.close()
                    if 'manifest.json' == filename:
                        with open(file_path, 'r') as file:
                            data = json.load(file)
                        file.close()
                        # Increment the manifest-version
                        data['manifest-version'] = increment_manifest_version(data['manifest-version'])
                        # Write the updated JSON back to the file
                        with open(file_path, 'w') as file:
                            json.dump(data, file, indent=4)
                        file.close()

    with open(os.path.join(directory, 'platform/mikrosdk_version/include/mikrosdk_version.h'), 'r') as file:
        file_content = file.read()
    file.close()

    # Replace the version macros with new values
    file_content = re.sub(r'#define\s+mikroSDK_MAJOR_VERSION\s+\d+', f'#define mikroSDK_MAJOR_VERSION {version.split('.')[0]}', file_content)
    file_content = re.sub(r'#define\s+mikroSDK_MINOR_VERSION\s+\d+', f'#define mikroSDK_MINOR_VERSION {version.split('.')[1]}', file_content)
    file_content = re.sub(r'#define\s+mikroSDK_PATCH_VERSION\s+\d+', f'#define mikroSDK_PATCH_VERSION {version.split('.')[2]}', file_content)

    with open(os.path.join(directory, 'platform/mikrosdk_version/include/mikrosdk_version.h'), 'w') as file:
        file.write(file_content)
    file.close()

def download_file(url, destination):
    """Downloads a file from a given URL and saves it to a destination path."""
    try:
        response = requests.get(url)
        response.raise_for_status()  # Check if the request was successful
        with open(destination, 'wb') as file:
            file.write(response.content)
        return destination
    except requests.exceptions.RequestException as e:
        print(f"Failed to download the file: {e}")
        return None
