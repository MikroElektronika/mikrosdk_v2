import os, re, time, argparse, requests, hashlib, shutil
from elasticsearch import Elasticsearch
from datetime import datetime, timezone

import support as support

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

# Function to fetch release details from GitHub
def fetch_release_details(repo, token, version):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    if "latest" == version:
        return support.get_latest_release(response.json()), support.get_previous_release(response.json(), True)
    else:
        release_check = None
        release_check = support.get_specified_release(response.json(), version)
        if release_check:
            return release_check, support.get_latest_release(response.json())
        else:
            ## Always fallback to latest release
            print("WARNING: Falling back to LATEST release.")
            return support.get_latest_release(response.json()), support.get_previous_release(response.json(), True)

# Function to fetch content as JSON from the link
def fetch_json_data(download_link, token):
    """
    Fetches JSON data from the specified URL using an authorization token and returns it as a dictionary.

    Args:
        download_link (str): URL from which to fetch the JSON data.

    Returns:
        tuple: The first element is a dictionary containing the JSON data (or None in case of failure),
                the second element is an error message or None if no errors occurred.
    """
    headers = get_headers(False, token)

    try:
        response = requests.get(download_link, headers=headers)
        response.raise_for_status()
        return response.json(), None
    except requests.RequestException as e:
        print(f"Error fetching JSON data: {e}")
        return None, str(e)

def check_from_index(es: Elasticsearch, index_name, asset):
    # Search query to use
    query_search = {
        "size": 5000,
        "query": {
            "match_all": {}
        }
    }

    # Search the base with provided query
    num_of_retries = 1
    while num_of_retries <= 10:
        try:
            response = es.search(index=index_name, body=query_search)
            if not response['timed_out']:
                break
        except:
            print("Executing search query - retry number %i" % num_of_retries)
        num_of_retries += 1

    version = '1.0.0'
    for eachHit in response['hits']['hits']:
        if not 'name' in eachHit['_source']:
            continue ## TODO - Check newly created bare metal package (is it created correctly)
        name = eachHit['_source']['name']
        if name == asset:
            version = eachHit['_source']['version']

    return version

def increment_version(version):
    major, minor, patch = map(int, version.split('.'))
    return f"{major}.{minor}.{patch + 1}"

def fetch_current_indexed_version(es : Elasticsearch, index_name, package_name):
    # Search query to use
    query_search = {
        "size": 5000,
        "query": {
            "match_all": {}
        }
    }
    # All package types to check for
    typeCheck = [
        'mcu',
        'preinit',
        'database',
        'mcu_clocks',
        'mcu_schemas',
        'unit_test_lib',
        'mikroe_utils_common'
    ]

    # Search the base with provided query
    num_of_retries = 1
    while num_of_retries <= 10:
        try:
            response = es.search(index=index_name, body=query_search)
            if not response['timed_out']:
                break
        except:
            print("Executing search query - retry number %i" % num_of_retries)
        num_of_retries += 1

    for eachHit in response['hits']['hits']:
        if not 'name' in eachHit['_source']:
            continue ## TODO - Check newly created bare metal package (is it created correctly)
        name = eachHit['_source']['name']
        if name == package_name:
            return eachHit['_source']['published_at']

    return None

# Function to index release details into Elasticsearch
def index_release_to_elasticsearch(es : Elasticsearch, index_name, release_details, token):
    # Iterate over each asset in the release and previous release
    metadata_content = []
    for each_release_details in release_details:
        if each_release_details:  ## TODO - hotfix for test index - check this
            metadata_asset = next((a for a in each_release_details['assets'] if a['name'] == "metadata.json"), None)
            if metadata_asset:
                metadata_download_url = metadata_asset['url']
                metadata_content.append(fetch_json_data(metadata_download_url, token)[0])

    ## 0 is new one being indexed, 1 in previously indexed release
    if 'mikrosdk' in metadata_content[0]:
        version = metadata_content[0]['mikrosdk']['version']
    else:
        for asset in release_details[0].get('assets', []):
            if 'mikrosdk.7z' == asset['name']:
                # Download the current mikroSDK asset in order to read the version
                support.extract_archive_from_url(
                    asset['url'],
                    os.path.join(os.path.dirname(__file__), 'tmp'),
                    token
                )

                # Then fetch version from manifest file
                version = support.fetch_version_from_asset(os.path.join(os.path.dirname(__file__), 'tmp'))
                break

    import urllib.request
    urllib.request.urlretrieve(f"{os.environ['MIKROE_NECTO_AWS']}/public/boards.txt", os.path.join(os.path.dirname(__file__), "boards.txt"))
    with open(os.path.join(os.path.dirname(__file__), "boards.txt"), 'r') as file:
        boards = [x.replace('\n', '') for x in file.readlines()]
    file.close()

    # Get the current time in UTC
    current_time = datetime.now(timezone.utc).replace(microsecond=0)
    # If you specifically want the 'Z' at the end instead of the offset
    published_at = current_time.isoformat().replace('+00:00', 'Z')

    for asset in release_details[0].get('assets', []):
        doc = None
        package_name = None
        name_without_extension = os.path.splitext(os.path.basename(asset['name']))[0]
        package_id = name_without_extension
        if 'mikrosdk' == name_without_extension:
            doc = {
                'name': name_without_extension,
                'display_name': "mikroSDK",
                'author': 'MIKROE',
                'hidden': False,
                'type': 'sdk',
                'version': version,
                'created_at' : asset['created_at'],
                'updated_at' : asset['updated_at'],
                'published_at': published_at,
                'category': 'Software Development Kit',
                'download_link': asset['url'],  # Adjust as needed for actual URL
                "install_location" : "%APPLICATION_DATA_DIR%/packages/sdk",
                'package_changed': version != version
            }
        elif 'templates' == name_without_extension:
            package_changed = True
            if len(metadata_content) > 1:
                package_changed = metadata_content[0]['templates']['hash'] != metadata_content[1]['templates']['hash']
            templates_version = check_from_index(es, index_name, 'templates')
            if package_changed:
                templates_version = increment_version(templates_version)
            doc = {
                "name": name_without_extension,
                "version" : templates_version,
                "display_name" : "NECTO project templates",
                "hidden" : True,
                "vendor" : "MIKROE",
                "type" : "application",
                "download_link" : asset['url'],
                "install_location" : "%APPLICATION_DATA_DIR%/templates",
                "package_changed": package_changed
            }
        elif 'images' == name_without_extension:
            package_changed = True
            package_id = name_without_extension + '_sdk'
            images_version_previous = check_from_index(es, index_name, 'images_sdk')
            if len(metadata_content) > 1:
                package_changed = metadata_content[0]['images']['hash'] != metadata_content[1]['images']['hash']
            doc = {
                "name": 'images_sdk',
                "version" : increment_version(images_version_previous),
                "display_name" : "mikroSDK Setup images",
                "hidden" : True,
                "vendor" : "MIKROE",
                "type" : "images",
                "download_link" : asset['url'],
                "install_location" : "%APPLICATION_DATA_DIR%/resources/images",
                "package_changed": True
            }
        elif asset['name'].startswith('board') or \
             asset['name'].startswith('mikromedia') or \
             asset['name'].startswith('clicker') or \
             asset['name'].startswith('board') or \
             asset['name'].startswith('kit') or \
             asset['name'].startswith('flip'):
            board_version_new = '1.0.0'
            board_version_previous = '0.0.0'
            if 'packages' in metadata_content[1]:
                if name_without_extension in metadata_content[1]['packages']:
                    if 'hash' in metadata_content[1]['packages'][name_without_extension]:
                        board_version_previous = check_from_index(es, index_name, asset['name'])
                        board_version_new = board_version_previous
                        if metadata_content[0]['packages'][name_without_extension]['hash'] != metadata_content[1]['packages'][name_without_extension]['hash']:
                            board_version_new = increment_version(board_version_previous)
            for each_package in metadata_content[0]['packages']:
                if metadata_content[0]['packages'][each_package]['package_name'] == name_without_extension:
                    package_name = metadata_content[0]['packages'][each_package]['display_name']
                    break
            show_package = False if metadata_content[0]['packages'][package_name]['package_name'] in boards else True
            if board_version_previous != '0.0.0':
                if board_version_previous != board_version_new:
                    show_package = True
            else:
                if show_package:
                    for each_package in metadata_content[0]['packages']:
                        if name_without_extension == metadata_content[0]['packages'][each_package]['package_name']:
                            previous_package_hash = metadata_content[0]['packages'][each_package]['hash']
                            support.extract_archive_from_url(
                                asset['url'],
                                os.path.join(os.path.dirname(__file__), 'test_package'),
                                token=token
                            )
                            current_package_hash = hash_directory_contents(os.path.join(os.path.dirname(__file__), 'test_package'))
                            if previous_package_hash == current_package_hash:
                                board_version_previous = board_version_new
                            shutil.rmtree(os.path.join(os.path.dirname(__file__), 'test_package'))
                            break
            doc = {
                'name': metadata_content[0]['packages'][package_name]['package_name'],
                'display_name': metadata_content[0]['packages'][package_name]['display_name'],
                'author': 'MIKROE',
                'hidden': False,
                "icon": re.sub(r'(mikrosdk_v2/)(.*?)(/resources)', r'\1master\3', metadata_content[0]['packages'][package_name]['icon']),
                'type': metadata_content[0]['packages'][package_name]['type'],
                'version': board_version_new,
                'created_at' : asset['created_at'],
                'updated_at' : asset['updated_at'],
                'published_at': published_at,
                'category': metadata_content[0]['packages'][package_name]['category'],
                'download_link': asset['url'],  # Adjust as needed for actual URL
                "install_location" : metadata_content[0]['packages'][package_name]['install_location'],
                'package_changed': board_version_previous != board_version_new,
                'show_package_info': show_package
            }

            check_types = ['board']
            if not doc['package_changed'] and doc['type'] in check_types:
                current_package_date = fetch_current_indexed_version(es, index_name, name_without_extension)
                if current_package_date:
                    doc['published_at'] = current_package_date
                doc['package_changed'] = True
                print("Date left to initial for: %s" % name_without_extension)

        # Index the document
        if doc:
            resp = es.index(index=index_name, doc_type='necto_package', id=package_id, body=doc)
            ## Special case for images, update live index elasticsearch base as well
            ## Called only from board release workflow
            if ('ES_INDEX_TEST' in os.environ) and ('ES_INDEX_LIVE' in os.environ):
                if ('images' == name_without_extension) and (index_name == os.environ['ES_INDEX_TEST']):
                    resp = es.index(index=os.environ['ES_INDEX_LIVE'], doc_type='necto_package', id=package_id, body=doc)
            if doc['package_changed']:
                print(f"{resp["result"]} {resp['_id']}")
                print(f"Download link is {doc['download_link']}")
                print(f"Version is {doc['version']}")
                print(f"Package changed set to {str(doc['package_changed'])}")

def is_release_latest(repo, token, release_version):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    latest_release = support.get_latest_release(response.json())
    if 'latest' == release_version:
        return None, True
    else:
        return response.json(), release_version == latest_release['tag_name']

def promote_to_latest(releases, repo, token, release_version):
    # Headers for authentication
    headers = {
        "Authorization": f"token {token}",
        "Accept": "application/vnd.github+json"
    }

    # Step 1: Update the prerelease version and set it as not prerelease
    selected_release = support.get_specified_release(releases, release_version=release_version)
    if selected_release['prerelease']:
        data_selected_release = {
            "tag_name": selected_release['tag_name'],
            "name": selected_release['name'],
            "body": selected_release['body'],
            "draft": False,
            "prerelease": False
        }

        response_1 = requests.patch(
            f"https://api.github.com/repos/{repo}/releases/{selected_release['id']}",
            headers=headers,
            json=data_selected_release
        )

    if not response_1.ok:
        raise Exception(f"Failed to update release {selected_release['name']}: {response_1.status_code} - {response_1.text}")

    # Step 2: Set the current latest release to prerelease
    latest_release = support.get_latest_release(releases)
    data_latest_release = {
        "prerelease": True
    }

    response_2 = requests.patch(
        f"https://api.github.com/repos/{repo}/releases/{latest_release['id']}",
        headers=headers,
        json=data_latest_release
    )

    if not response_2.ok:
        raise Exception(f"Failed to demote release {selected_release['name']}: {response_2.status_code} - {response_2.text}")

    # Step 3: Change the state of the current latest release back to not prerelease
    data_latest_release['prerelease'] = False
    response_3 = requests.patch(
        f"https://api.github.com/repos/{repo}/releases/{latest_release['id']}",
        headers=headers,
        json=data_latest_release
    )

    if not response_3.ok:
        raise Exception(f"Failed to revert status for release {selected_release['name']}: {response_3.status_code} - {response_3.text}")

    return


if __name__ == '__main__':
    # First, check for arguments passed
    def str2bool(v):
        if isinstance(v, bool):
            return v
        if v.lower() in ('yes', 'true', 't', 'y', '1'):
            return True
        elif v.lower() in ('no', 'false', 'f', 'n', '0'):
            return False
        else:
            raise argparse.ArgumentTypeError('Boolean value expected.')

    # Get arguments
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("release_version", help="Selected release version to index", type=str)
    parser.add_argument("select_index", help="Provided index name")
    parser.add_argument("promote_release_to_latest", help="Sets current release as latest", type=str2bool, default=False)
    args = parser.parse_args()

    # Elasticsearch instance used for indexing
    num_of_retries = 1
    while True:
        print(f"Trying to connect to ES. Connection retry:  {num_of_retries}")
        es = Elasticsearch([os.environ['ES_HOST']], http_auth=(os.environ['ES_USER'], os.environ['ES_PASSWORD']))
        if es.ping():
            break
        # Wait for 30 seconds and try again if connection fails
        if 10 == num_of_retries:
            # Exit if it fails 10 times, something is wrong with the server
            raise ValueError("Connection to ES failed!")
        num_of_retries += 1

        time.sleep(30)

    # Now index the new release
    index_release_to_elasticsearch(
        es, args.select_index,
        fetch_release_details(args.repo, args.token, args.release_version),
        args.token
    )

    # And then promote to latest if requested
    if (args.promote_release_to_latest):
        # If current release isn't latest already
        releases, is_latest = is_release_latest(args.repo, args.token, args.release_version)
        if (not is_latest):
            promote_to_latest(releases, args.repo, args.token, args.release_version)
