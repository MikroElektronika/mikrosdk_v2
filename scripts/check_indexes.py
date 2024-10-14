import sys, argparse, requests

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
    parser.add_argument("--log_only", help="Regex to use to fetch indexed items", type=bool, default=False)
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

    strict_fetch = ['images']
    fetch_fix = ['images_sdk']

    err = False
    for indexed_item in es_instance.indexed_items:
        asset_status = requests.get(indexed_item['source']['download_link'], headers=headers)
        if es_instance.Status.ERROR.value == asset_status.status_code: ## code 404 - error, reindex with correct download link
            err = True
            print("%sERROR: Asset \"%s\" download link is incorrect. - %s" % (es_instance.Colors.FAIL, indexed_item['source']['name'], indexed_item['source']['download_link']))
            if not args.log_only:
                loose = True
                if indexed_item['source']['name'] in strict_fetch:
                    loose = False
                check_package = indexed_item['source']['name']
                if indexed_item['source']['name'] in fetch_fix:
                    check_package = indexed_item['source']['name'][:-4]
                url = gh_instance.asset_fetch_url_api(check_package, loose=loose)
                indexed_item['source']['download_link'] = url
                es_instance.update(indexed_item['doc']['type'], indexed_item['doc']['id'], indexed_item['source'])
        else: ## code 200 - success, no need to reindex
            print("%sOK: Asset \"%s\" download link is correct. - %s" % (es_instance.Colors.OKBLUE, indexed_item['source']['name'], indexed_item['source']['download_link']))

    if err and args.log_only:
        sys.exit(-1)
