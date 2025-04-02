import os, re, time, argparse, requests, hashlib, shutil, logging
from elasticsearch import Elasticsearch
from datetime import datetime, timezone
from alive_progress import alive_bar

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
            'Authorization': f'token {token}',
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
        }
    else:
        return {
            'Authorization': f'Bearer {token}',
            'Accept': 'application/octet-stream',
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
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

def check_from_index_hash(asset, indexed_items):
    for item in indexed_items:
        if asset == item['name']:
            if 'hash' in item:
                return item['hash']

    return None

def check_from_index_version(asset, indexed_items):
    version = None
    for item in indexed_items:
        if asset == item['name']:
            version = item['version']
            break

    return version

def increment_version(version):
    major, minor, patch = map(int, version.split('.'))
    return f"{major}.{minor}.{patch + 1}"

def fetch_current_indexed_version(package_name, indexed_items):
    for item in indexed_items:
        if package_name == item['name']:
            if 'published_at' in item:
                return item['published_at']

    return None

def fetch_current_indexed_packages(es : Elasticsearch, index_name):
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

    all_packages = []
    for eachHit in response['hits']['hits']:
        if not 'name' in eachHit['_source']:
            continue
        if '_type' in eachHit:
            if '_doc' == eachHit['_type']:
                all_packages.append(eachHit['_source'])

    # Sort all_packages alphabetically by the 'name' field
    all_packages.sort(key=lambda x: x['name'])

    return all_packages

def resolve_publish_date(indexed_items, package_name):
    for indexed_item in indexed_items:
        if indexed_item['name'] == package_name:
            return indexed_item['published_at']
    # Notify user about failed package
    print("%sNo release date found for %s!" % (support.Colors.FAIL, package_name))
    return None

# Function to index release details into Elasticsearch
def index_release_to_elasticsearch(es : Elasticsearch, index_name, release_details, token, keep_previous_date=False):
    necto_versions = {
        'test': 'dev', ## Development NECTO version
        'live': 'live', ## Live NECTO version
        'experimental': 'experimental' ## Experimental NECTO version
    }

    # Get all currently indexed items
    indexed_items = fetch_current_indexed_packages(es, index_name)
    index_asset_names = []
    for index_asset_name in indexed_items:
        index_asset_names.append(index_asset_name['name'])

    # Iterate over each asset in the release and previous release
    metadata_content = []
    for each_release_details in release_details:
        if each_release_details:
            metadata_asset = next((a for a in each_release_details['assets'] if a['name'] == "metadata.json"), None)
            if metadata_asset:
                metadata_download_url = metadata_asset['url']
                metadata_content.append(fetch_json_data(metadata_download_url, token)[0])

    ## 0 is new one being indexed, 1 in previously indexed release
    if 'mikrosdk' in metadata_content[0]:
        version = metadata_content[0]['mikrosdk']['version']
        version_index = check_from_index_version('mikrosdk', indexed_items)
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
                version_index = check_from_index_version('mikrosdk', indexed_items)
                break

    # Get the current time in UTC
    current_time = datetime.now(timezone.utc).replace(microsecond=0)
    # If you specifically want the 'Z' at the end instead of the offset
    published_at = current_time.isoformat().replace('+00:00', 'Z')

    # Set logger to display only fatal errors
    logging.basicConfig(level=logging.FATAL)

    cnt = 0
    package_names = [{},{}]
    for metadata in metadata_content:
        for package in metadata['packages']:
            package_names[cnt].update(
                {metadata['packages'][package]['package_name']: metadata['packages'][package]['display_name']}
            )
        cnt += 1

    with alive_bar(len(release_details[0]['assets']), title='Indexing Packages', length=60, spinner='wait') as bar:
        for asset in release_details[0].get('assets', []):
            doc = None
            package_name = None
            name_without_extension = os.path.splitext(os.path.basename(asset['name']))[0]
            package_id = name_without_extension

            # Increase bar value
            bar.text(name_without_extension)
            bar()

            if 'mikrosdk' == name_without_extension:
                asset_version_previous = version_index
                publish_date = published_at
                doc = {
                    'name': name_without_extension,
                    'display_name': "mikroSDK",
                    'author': 'MIKROE',
                    'hidden': False,
                    'type': 'sdk',
                    'version': version,
                    'created_at' : asset['created_at'],
                    'updated_at' : asset['updated_at'],
                    'published_at': publish_date,
                    'category': 'Software Development Kit',
                    'download_link': asset['browser_download_url'],
                    'download_link_api': asset['url'],
                    'install_location' : "%APPLICATION_DATA_DIR%/packages/sdk",
                    'package_changed': version != version_index,
                    'gh_package_name': "mikrosdk.7z"
                }
            elif 'templates' in name_without_extension:
                if 'test' in index_name:
                    necto_version = necto_versions['test']
                elif 'live' in index_name:
                    necto_version = necto_versions['live']
                elif 'experimental' in index_name:
                    necto_version = necto_versions['experimental']
                if f'templates_{necto_version}' == name_without_extension:
                    package_id = 'templates'
                    hash_previous = check_from_index_hash(f'templates', indexed_items)
                    hash_new = metadata_content[0][f'templates_{necto_version}']['hash']
                    asset_version_previous = check_from_index_version(f'templates', indexed_items)
                    asset_version_new = asset_version_previous
                    if hash_previous:
                        if hash_previous != hash_new:
                            asset_version_new = increment_version(check_from_index_version(f'templates', indexed_items))
                    doc = {
                        "name": "templates",
                        "version" : asset_version_new,
                        "display_name" : f"NECTO project templates - {necto_version}", ## Added necto_version for more info
                        "hidden" : True,
                        "vendor" : "MIKROE",
                        "type" : "application",
                        "download_link" : asset['browser_download_url'],
                        "download_link_api" : asset['url'],
                        "install_location" : "%APPLICATION_DATA_DIR%/templates",
                        "package_changed": asset_version_previous != asset_version_new,
                        "hash": hash_new,
                        "gh_package_name": f"templates_{necto_version}.7z"
                    }
            elif 'images' == name_without_extension:
                package_id = name_without_extension + '_sdk'
                hash_previous = check_from_index_hash('images_sdk', indexed_items)
                hash_new = metadata_content[0]['images']['hash']
                asset_version_previous = check_from_index_version('images_sdk', indexed_items)
                asset_version_new = asset_version_previous
                if hash_previous != hash_new:
                    asset_version_new = increment_version(asset_version_previous)
                doc = {
                    "name": 'images_sdk',
                    "version" : asset_version_new,
                    "display_name" : "mikroSDK Setup images",
                    "hidden" : True,
                    "vendor" : "MIKROE",
                    "type" : "images",
                    "download_link" : asset['browser_download_url'],
                    "download_link_api" : asset['url'],
                    "install_location" : "%APPLICATION_DATA_DIR%/resources/images",
                    "package_changed": asset_version_previous != asset_version_new,
                    "hash": hash_new,
                    "gh_package_name": "images.7z"
                }
            elif asset['name'].startswith('board') or \
                asset['name'].startswith('mikromedia') or \
                asset['name'].startswith('clicker') or \
                asset['name'].startswith('kit') or \
                asset['name'].startswith('flip') or \
                asset['name'].startswith('mcu_card') or \
                asset['name'].startswith('pim') or \
                'mcucard' in asset['name'] or \
                'mcu_card' in asset['name'] or \
                'micromod' in asset['name'] or \
                asset['name'].startswith('sibrain'):

                # Set new version to be 1.0.0 by default
                asset_version_new = '1.0.0'
                # Get the indexed version
                asset_version_previous = check_from_index_version(name_without_extension, indexed_items)
                # Set hash to be None by default
                hash_new = None
                # If current item is already indexed
                if name_without_extension in index_asset_names:
                    # If there is an info about hash in metadata for current release (normally it should have it always)
                    if 'hash' in metadata_content[0]['packages'][package_names[0][name_without_extension]]:
                        # Set version to be as for index asset
                        asset_version_new = asset_version_previous
                        # Get hash info for current item from latest release metadata.json
                        metadata_hash = metadata_content[0]['packages'][package_names[0][name_without_extension]]['hash']
                        # Get indexed hash info for current item
                        hash_indexed = check_from_index_hash(name_without_extension, indexed_items)
                        # If hash from current metadata is not the same as indexed hash
                        if metadata_hash != hash_indexed:
                            # Increase the index version
                            asset_version_new = increment_version(asset_version_previous)
                            # Set the index hash to be as in metadata
                            hash_new = metadata_hash
                        # Else leave it to be the same
                        else:
                            hash_new = hash_indexed
                # If current item is not indexed
                else:
                    # If there is an info about hash in metadata for current release (normally it should have it always)
                    if 'hash' in metadata_content[0]['packages'][package_names[0][name_without_extension]]:
                        # Set hash to be as in metadata.json for current release
                        hash_new = metadata_content[0]['packages'][package_names[0][name_without_extension]]['hash']

                # Get valid package name from metadata,json
                for each_package in metadata_content[0]['packages']:
                    if metadata_content[0]['packages'][each_package]['package_name'] == name_without_extension:
                        package_name = metadata_content[0]['packages'][each_package]['display_name']
                        break

                publish_date = published_at

                doc = {
                    'name': metadata_content[0]['packages'][package_name]['package_name'],
                    'display_name': metadata_content[0]['packages'][package_name]['display_name'],
                    'author': 'MIKROE',
                    'hidden': False,
                    "icon": re.sub(r'(mikrosdk_v2/)(.*?)(/resources)', r'\1master\3', metadata_content[0]['packages'][package_name]['icon']),
                    'type': metadata_content[0]['packages'][package_name]['type'],
                    'version': asset_version_new,
                    'created_at' : asset['created_at'],
                    'updated_at' : asset['updated_at'],
                    'published_at': publish_date,
                    'category': metadata_content[0]['packages'][package_name]['category'],
                    'download_link': asset['browser_download_url'],
                    'download_link_api': asset['url'],
                    "install_location" : metadata_content[0]['packages'][package_name]['install_location'],
                    'package_changed': asset_version_previous != asset_version_new,
                    'show_package_info': True,
                    'hash': hash_new,
                    'gh_package_name': os.path.splitext(os.path.basename(asset['name']))[0]
                }

            # Index the document
            if doc:
                # If requested to keep previous date, only update the hash value
                if keep_previous_date and 'hash' in doc:
                    for item in indexed_items:
                        package_name = name_without_extension
                        # Exception for SDK images - index name is images_sdk
                        if 'images' == name_without_extension:
                            package_name = 'images_sdk'
                        if item['name'] == package_name:
                            hash_new = doc['hash']
                            doc = item
                            doc['hash'] = hash_new
                            break
                # Kibana v8 requires _type to be in body in order to have doc_type defined
                doc['_type'] = '_doc'
                if 'images' == name_without_extension or (asset_version_previous != doc['version'] and doc['package_changed']) or (keep_previous_date and 'mikrosdk' != name_without_extension):
                    resp = es.index(index=index_name, doc_type=None, id=package_id, body=doc)
                    print(f"{resp["result"]} {resp['_id']}")

                    if asset_version_previous != doc['version'] and doc['package_changed']:
                        print(f'\033[95mVersion for asset {doc['name']} has been updated from {asset_version_previous} to {doc['version']}\033[0m')
                    # SDK images and templates package don't have a publish date
                    elif keep_previous_date:
                        if 'images' != name_without_extension and 'templates' not in name_without_extension:
                            print(f'\033[95mKept the release date for asset {doc['name']} as {doc['published_at']} with the {doc['version']} version. New hash is {doc['hash']}\033[0m')
                        else:
                            print(f'\033[95mUpdated hash for {doc['name']} to be {doc['hash']}\033[0m')

                    ## Note: commented out as now we index the browser download link, not the api link
                    ## and it always stays the same, so no need to reindex to live on every release to TEST.
                    ## Leaving it as commented out section to see how images_sdk asset behaves without indexing it to live on test release.
                    # Always index images_sdk asset to live
                    # if 'images' == name_without_extension and 'test' in index_name:
                    #     asset_version_previous = check_from_index_version('images_sdk', fetch_current_indexed_packages(es, os.environ['ES_INDEX_LIVE']))
                    #     doc['version'] = increment_version(asset_version_previous)
                    #     resp = es.index(index=os.environ['ES_INDEX_LIVE'], doc_type=None, id=package_id, body=doc)
                    #     print("Indexed images_sdk to LIVE as well")
                    #     print(f'\033[95mVersion for asset {doc['name']} on LIVE has been updated from {asset_version_previous} to {doc['version']}\033[0m')

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
    parser.add_argument("--keep_previous_dates", help="Repacks and uploads all packages with new copyright year, but keeps previous release dates.", type=str2bool, default=False)
    args = parser.parse_args()

    # Elasticsearch instance used for indexing
    num_of_retries = 1
    print("Trying to connect to ES.")
    while True:
        es = Elasticsearch([os.environ['ES_HOST']], http_auth=(os.environ['ES_USER'], os.environ['ES_PASSWORD']))
        if es.ping():
            break
        # Wait 1 second and try again if connection fails
        if 10 == num_of_retries:
            # Exit if it fails 10 times, something is wrong with the server
            raise ValueError("Connection to ES failed!")
        print(f"Connection retry: {num_of_retries}")
        num_of_retries += 1

        time.sleep(1)

    # Now index the new release
    index_release_to_elasticsearch(
        es, args.select_index,
        fetch_release_details(args.repo, args.token, args.release_version),
        args.token,
        args.keep_previous_dates
    )

    # And then promote to latest if requested
    if (args.promote_release_to_latest):
        # If current release isn't latest already
        releases, is_latest = is_release_latest(args.repo, args.token, args.release_version)
        if (not is_latest):
            promote_to_latest(releases, args.repo, args.token, args.release_version)
