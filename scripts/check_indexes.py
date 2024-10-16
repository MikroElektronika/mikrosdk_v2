import sys, json, argparse, requests

import classes.class_gh as gh
import classes.class_es as es

if __name__ == "__main__":
    # Get arguments
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("gh_repo", help="Github repository name, e.g., 'username/repo'", type=str)
    parser.add_argument("gh_token", help="GitHub Token", type=str)
    parser.add_argument("es_host", help="ES instance host value", type=str)
    parser.add_argument("es_user", help="ES instance user value", type=str)
    parser.add_argument("es_password", help="ES instance password value", type=str)
    parser.add_argument("es_index", help="ES instance index value", type=str)
    parser.add_argument("--es_regex", help="Regex to use to fetch indexed items", type=str, default=".+")
    parser.add_argument("--log_only", help="If True, will not fix broken links, just log them to std out", type=bool, default=False)
    parser.add_argument("--index_package_names", help="If True, will add \"gh_package_name\" to indexed item", type=bool, default=True)
    args = parser.parse_args()

    es_instance = es.index(
        es_host=args.es_host, es_user=args.es_user, es_password=args.es_password,
        index=args.es_index, token=args.gh_token
    )

    gh_instance = gh.repo(args.gh_repo, args.gh_token)

    es_instance.fetch(regex=args.es_regex)

    headers = {
        'Authorization': f'token {args.gh_token}'
    }

    err = False
    for indexed_item in es_instance.indexed_items:
        asset_status = requests.get(indexed_item['source']['download_link'], headers=headers)
        if es_instance.Status.ERROR.value == asset_status.status_code: ## code 404 - error, reindex with correct download link
            err = True
            print("%sERROR: Asset \"%s\" download link is incorrect. - %s" % (es_instance.Colors.FAIL, indexed_item['source']['name'], indexed_item['source']['download_link']))
            if not args.log_only:
                if 'gh_package_name' in indexed_item['source']:
                    url = gh_instance.asset_fetch_url_api(indexed_item['source']['gh_package_name'], loose=False)
                    indexed_item['source']['download_link'] = url
                    es_instance.update(indexed_item['doc']['type'], indexed_item['doc']['id'], indexed_item['source'])
                else:
                    print("%sWARNING: Asset \"%s\" has no \"gh_package_name\" in the index." % (es_instance.Colors.WARNING, indexed_item['source']['name']))
        else: ## code 200 - success, no need to reindex
            if args.index_package_names:
                package_name = (json.loads(asset_status.text))['name']
                if 'gh_package_name' not in indexed_item['source']:
                    indexed_item['source'].update({"gh_package_name": package_name})
                    es_instance.update(indexed_item['doc']['type'], indexed_item['doc']['id'], indexed_item['source'])
                    print("%sINFO: Added \"gh_package_name\" to %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
                else:
                    if package_name != indexed_item['source']['gh_package_name']:
                        indexed_item['source']['gh_package_name'] = package_name
                        es_instance.update(indexed_item['doc']['type'], indexed_item['doc']['id'], indexed_item['source'])
                        print("%sINFO: Updated \"gh_package_name\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
            print("%sOK: Asset \"%s\" download link is correct. - %s" % (es_instance.Colors.OKBLUE, indexed_item['source']['name'], indexed_item['source']['download_link']))

    if err and args.log_only:
        sys.exit(-1)
