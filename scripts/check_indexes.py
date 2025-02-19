import os, sys, json, argparse, requests

import classes.class_gh as gh
import classes.class_es as es
import add_extra_index_info as extra_info

# Legacy packages for NECTO version 7.0.4 and lower
legacy_packages = ["clocks", "schemas", "database", "images", "images_sdk"]

def assign_urls(indexed_item, gh_instance, es_instance, fix_url_api=False):
    # All indexed github packages are 7z archives
    if 'gh_package_name' in indexed_item['source']:
        if '.7z' not in indexed_item['source']['gh_package_name']:
            indexed_item['source']['gh_package_name'] += '.7z'
        # Check if download link for all github assets is direct github download url
        url = gh_instance.asset_fetch_url_browser(indexed_item['source']['gh_package_name'], loose=False)
        url_api = gh_instance.asset_fetch_url_api(indexed_item['source']['gh_package_name'], loose=False)
        # For non-github packages url is None, so we should skip it
        if (indexed_item['source']['download_link'] != url and url != None) or (fix_url_api and url != None):
            indexed_item['source']['download_link'] = url
            indexed_item['source']['download_link_api'] = url_api
            es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
            print("%sINFO: Updated \"download_link\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))

if __name__ == "__main__":
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
    parser.add_argument("gh_repo", help="Github repository name, e.g., 'username/repo'", type=str)
    parser.add_argument("gh_token", help="GitHub Token", type=str)
    parser.add_argument("es_host", help="ES instance host value", type=str)
    parser.add_argument("es_user", help="ES instance user value", type=str)
    parser.add_argument("es_password", help="ES instance password value", type=str)
    parser.add_argument("es_index", help="ES instance index value", type=str)
    parser.add_argument("--es_regex", help="Regex to use to fetch indexed items", type=str, default=".+")
    parser.add_argument("--log_only", help="If True, will not fix broken links, just log them to std out", type=str2bool, default=False)
    parser.add_argument("--index_package_names", help="If True, will add \"gh_package_name\" to indexed item", type=str2bool, default=True)
    args = parser.parse_args()

    es_instance = es.index(
        es_host=args.es_host, es_user=args.es_user, es_password=args.es_password,
        index=args.es_index, token=args.gh_token
    )

    if 'ES_HOST_LEGACY' in os.environ and 'ES_USER_LEGACY' in os.environ and 'ES_PASSWORD_LEGACY':
        es_instance_legacy = es.index(
            es_host=os.environ['ES_HOST_LEGACY'], es_user=os.environ['ES_USER_LEGACY'], es_password=os.environ['ES_PASSWORD_LEGACY'],
            index=args.es_index, token=args.gh_token
        )

    gh_instance = gh.repo(args.gh_repo, args.gh_token)

    es_instance.fetch(regex=args.es_regex)

    headers = {
        'Authorization': f'token {args.gh_token}'
    }

    err = False
    doc_extra_info = {}
    try:
        for indexed_item in es_instance.indexed_items:
            if 'download_link_api' in indexed_item['source']:
                asset_status = requests.get(indexed_item['source']['download_link_api'], headers=headers)
            else:
                asset_status = requests.get(indexed_item['source']['download_link'], headers=headers)
            if es_instance.Status.ERROR.value == asset_status.status_code: ## code 404 - error, reindex with correct download link
                err = True
                print("%sERROR: Asset \"%s\" download link is incorrect. - %s" % (es_instance.Colors.FAIL, indexed_item['source']['name'], indexed_item['source']['download_link']))
                if not args.log_only:
                    if 'gh_package_name' in indexed_item['source']:
                        # Assign correct URLs
                        assign_urls(indexed_item, gh_instance, es_instance, fix_url_api=True)
                        if 'extra_information' not in indexed_item['source']: # Add extra information for Card or Board
                            extra_info.add(indexed_item['source'], args.gh_token, args.es_index)
                    else:
                        print("%sWARNING: Asset \"%s\" has no \"gh_package_name\" in the index." % (es_instance.Colors.WARNING, indexed_item['source']['name']))
                    if 'MIKROE' != indexed_item['source']['author']:
                        indexed_item['source']['author'] = 'MIKROE'
                        es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                        print("%sINFO: Updated \"author\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
            else: ## code 200 - success, no need to reindex
                if args.index_package_names:
                    package_name = f'{indexed_item['source']['name']}.7z'
                    if 'gh_package_name' not in indexed_item['source']:
                        indexed_item['source'].update({"gh_package_name": package_name})
                        if 'extra_information' not in indexed_item['source']: # Add extra information for Card or Board
                            extra_info.add(indexed_item['source'], args.gh_token, args.es_index)
                        es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                        print("%sINFO: Added \"gh_package_name\" to %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
                    else:
                        if package_name != indexed_item['source']['gh_package_name']:
                            indexed_item['source']['gh_package_name'] = package_name
                            if 'extra_information' not in indexed_item['source']: # Add extra information for Card or Board
                                extra_info.add(indexed_item['source'], args.gh_token, args.es_index)
                            es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                            print("%sINFO: Updated \"gh_package_name\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
                        else:
                            if 'extra_information' not in indexed_item['source']: # Add extra information for Card or Board
                                extra_info.add(indexed_item['source'], args.gh_token, args.es_index)
                                es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                        if 'author' not in indexed_item['source']:
                            indexed_item['source']['author'] = 'MIKROE'
                            es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                            print("%sINFO: Updated \"author\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))
                        if 'MIKROE' != indexed_item['source']['author']:
                            indexed_item['source']['author'] = 'MIKROE'
                            es_instance.update(None, indexed_item['doc']['id'], indexed_item['source'])
                            print("%sINFO: Updated \"author\" for %s" % (es_instance.Colors.UNDERLINE, indexed_item['source']['name']))

                    # Assign correct URLs
                    assign_urls(indexed_item, gh_instance, es_instance)
                print("%sOK: Asset \"%s\" download link is correct. - %s" % (es_instance.Colors.OKBLUE, indexed_item['source']['name'], indexed_item['source']['download_link']))
    except Exception as e:
        print(f'{es_instance.Colors.FAIL}Error for {indexed_item['source']['name']}: {e}')

        if 'ES_HOST_LEGACY' in os.environ and 'ES_USER_LEGACY' in os.environ and 'ES_PASSWORD_LEGACY':
            if indexed_item['source']['name'] in legacy_packages:
                es_instance_legacy.update('necto_package', indexed_item['doc']['id'], indexed_item['source'])
                print("%sOK: \"%s\" indexed for legacy NECTO." % (es_instance_legacy.Colors.OKGREEN, indexed_item['source']['name']))

    if err and args.log_only:
        sys.exit(-1)
