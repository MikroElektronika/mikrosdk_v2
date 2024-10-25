import os, time, argparse
import json
from elasticsearch import Elasticsearch
from datetime import datetime
import classes.class_generate_events_json as calendar_events

import support as support

def fetch_current_indexed_sdk_files(es : Elasticsearch, index_name):
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
        if 'necto_package' == eachHit['_type']:
            if False == eachHit['_source']['hidden']:
                all_packages.append(eachHit['_source'])

    return all_packages

def fetch_current_indexed_click_boards(es : Elasticsearch, index_name):
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
        if index_name == eachHit['_type']:
            if 'mikroe.click' in eachHit['_source']['name']:
                all_packages.append(eachHit['_source'])

    return all_packages

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Create the release post message for Web.")
    parser.add_argument("title", help="Event title for calendar.")
    parser.add_argument("doc_link", help="Spreadsheet table with release details - link.")
    parser.add_argument("sdk_index", help="SDK packages index.")
    parser.add_argument("clicks_index", help="Click packages index.")

    ## Parse the arguments
    args = parser.parse_args()

    # Elasticsearch instance used for getting indexing info
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

    current_date = datetime.now().strftime("%Y-%m-%d")

    # Get all indexed click boards
    all_click_boards = fetch_current_indexed_click_boards(es, args.clicks_index)

    # Get all indexed sdk packages
    all_sdk_files = fetch_current_indexed_sdk_files(es, args.sdk_index)

    ## Update release calendar values
    release_calendar = calendar_events.events_json(args.doc_link, args.title)
    release_calendar.fetch_data()
    ## Then generate the input file for teamup API
    release_calendar.generate_file(os.path.join(os.path.dirname(__file__), 'releases.json'))

    with open(os.path.join(os.path.dirname(__file__), 'releases.json'), 'r') as file:
        data = json.load(file)

    release_spreadsheet_data = ''
    update_present = 0
    todays_release = '<h4>New:</h4>\n\n<ul>\n</ul>'
    todays_update = '\n\n<h4>Updated:</h4>\n\n<ul>\n</ul>'

    for event in data["NECTO DAILY UPDATE"]["events"]:
        if event['end_dt'].startswith(current_date):
            release_spreadsheet_data += event['notes']

    # Add newly added click packages to the release message
    for each_click in all_click_boards:
        # Find newly published clicks
        if 'published' in each_click:
            if each_click['published'].startswith(current_date):
                todays_release = todays_release.replace('</ul>', f'\t<li>{each_click['display_name']}</li>\n</ul>')
            if each_click['last_updated'].startswith(current_date):
                todays_update = todays_update.replace('</ul>', f'\t<li>{each_click['display_name']}</li>\n</ul>')
                update_present = 1


    # Add newly added SDK packages to the release message
    for sdk_file in all_sdk_files:
        # First check if this package was published during latest releases
        if 'published_at' in sdk_file:
            # Find newly published SDK packages
            if sdk_file['published_at'].startswith(current_date):
                # Check if it is a newly released package that is listed in release spreadsheet
                if sdk_file['display_name'] in release_spreadsheet_data:
                    todays_release = todays_release.replace('</ul>', f'\t<li>{sdk_file['display_name']}</li>\n</ul>')
                # If it is not newly released package - add it to UPDATED section
                else:
                    todays_update = todays_update.replace('</ul>', f'\t<li>{sdk_file['display_name']}</li>\n</ul>')
                    update_present = 1

    if update_present:
        todays_release += todays_update

    print(todays_release)
