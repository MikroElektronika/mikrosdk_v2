import argparse, requests

import classes.class_gh as gh
import classes.class_es as es

if __name__ == "__main__":
    # Get arguments
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("gh_repo", help="Github repository name, e.g., 'username/repo'")
    parser.add_argument("gh_token", help="GitHub Token")
    parser.add_argument("es_host", help="ES instance host value")
    parser.add_argument("es_user", help="ES instance user value")
    parser.add_argument("es_password", help="ES instance password value")
    parser.add_argument("es_index", help="ES instance index value")
    args = parser.parse_args()

    es_instance = es.index(
        es_host=args.es_host, es_user=args.es_user, es_password=args.es_password,
        index=args.es_index, token=args.gh_token
    )

    gh_instance = gh.repo(args.gh_repo, args.gh_token)

    check_regex = r'\b(?:board|mcu_card|clicker|easymx_pro_v7|mikromedia|pim|sibrain|sparkfun_micromod|bsps|metadata|queries|templates)(?:_[a-z0-9]+)*\b'
    es_instance.fetch(regex=check_regex)

    headers = {
        'Authorization': f'token {args.gh_token}'
    }

    for indexed_item in es_instance.indexed_items:
        asset_status = requests.get(indexed_item['source']['download_link'], headers=headers)
        if es_instance.Status.ERROR.value == asset_status.status_code: ## code 404 - error
            print("%sERROR: Asset \"%s\" download link is incorrect. - %s" % (es_instance.Colors.FAIL, indexed_item['source']['name'], indexed_item['source']['download_link']))
            url = gh_instance.asset_fetch_url_api(indexed_item['source']['name'], loose=True)
            indexed_item['source']['download_link'] = url
            es_instance.update(indexed_item['doc']['type'], indexed_item['doc']['id'], indexed_item['source'])
        else: ## code 200 - success
            print("%sOK: Asset \"%s\" download link is correct. - %s" % (es_instance.Colors.OKBLUE, indexed_item['source']['name'], indexed_item['source']['download_link']))
