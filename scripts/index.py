import os, time, argparse, requests
from elasticsearch import Elasticsearch

import support as support

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
def fetch_release_details(repo, token):
    api_headers = get_headers(True, token)
    url = f'https://api.github.com/repos/{repo}/releases'
    response = requests.get(url, headers=api_headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return support.get_latest_release(response.json())

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

# Function to find an item by name
def find_item_by_name(items, name):
    for item in items:
        if item['name'] == name:
            return item
    return None

# Function to index release details into Elasticsearch
def index_release_to_elasticsearch(es : Elasticsearch, index_name, release_details, token):
    version = None
    for asset in release_details.get('assets', []):
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
    for asset in release_details.get('assets', []):
        doc = None
        name_without_extension = os.path.splitext(os.path.basename(asset['name']))[0]
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
                'category': 'Software Development Kit',
                'download_link': asset['url'],  # Adjust as needed for actual URL
                'package_changed': True
            }
        elif 'templates' == name_without_extension:
            doc = {
                "name": name_without_extension,
                "version" : version,
                "display_name" : "NECTO project templates",
                "hidden" : True,
                "vendor" : "MIKROE",
                "type" : "application",
                "download_link" : asset['url'],
                "install_location" : "%APPLICATION_DATA_DIR%",
                "package_changed": True
            }

        # Index the document
        if doc:
            resp = es.index(index=index_name, doc_type='necto_package', id=name_without_extension, body=doc)
            print(f"{resp["result"]} {resp['_id']}")

if __name__ == '__main__':
    # Get arguments
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("token", help="GitHub Token")
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
        es, os.environ['ES_INDEX'],
        fetch_release_details(args.repo, args.token),
        args.token
    )
