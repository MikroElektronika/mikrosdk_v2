import os, re, py7zr, \
       requests, argparse, \
       json, hashlib, shutil, \
       sqlite3

import support as support

def functionRegex(value, pattern):
    reg = re.compile(r"\b" + str(value) + r"\b")
    return reg.search(str(pattern)) is not None

def read_data_from_db(db, sql_query):
    ## Open the database / connect to it
    con = sqlite3.connect(db)
    cur = con.cursor()

    ## Create the REGEXP function to be used in DB
    con.create_function("REGEXP", 2, functionRegex)
    # sqlite3.enable_callback_tracebacks(True) ## TODO - uncomment for debug purposes

    ## Execute the desired query
    results = cur.execute(sql_query).fetchall()
    # results = cur.fetchall()

    ## Close the connection
    cur.close()
    con.close()

    ## Return query results
    return len(results), results

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
            if re.search(r'(\.git)|(\.vscode)|(scripts)|(templates)|(changelog)|(resources)|(bsp/board/include/(boards|shields|mcu_cards))', os.path.relpath(root, source_folder)):
                if not 'board_generic' in os.path.relpath(root, source_folder):
                    continue
            for file in files:
                if re.search(r'\.git', file):
                    continue
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

def get_all_release_assets(repo, release_id, token):
    all_assets = []
    headers = {
        'Authorization': f'token {token}',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
    }
    page = 1
    while True:
        url = f'https://api.github.com/repos/{repo}/releases/{release_id}/assets?page={page}&per_page=30'
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        assets = response.json()

        # If no more assets, break out of loop
        if not assets:
            break

        all_assets += (asset for asset in assets)

        page += 1

    return all_assets

def upload_asset_to_release(repo, release_id, asset_path, token, assets, delete_existing=True):
    """Upload an asset to a specific GitHub release. If the asset exists, delete it first."""
    asset_name = os.path.basename(asset_path)
    url = f'https://api.github.com/repos/{repo}/releases/{release_id}/assets'
    headers = {
        'Authorization': f'token {token}',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
    }

    # Check if the asset already exists
    for asset in assets:
        if asset['name'] == asset_name:
            # If the asset exists, delete it
            delete_url = asset['url']
            if delete_existing:
                print(f'Deleting existing asset: {asset_name}')
                delete_response = requests.delete(delete_url, headers=headers)
                delete_response.raise_for_status()
                print(f'\033[91mAsset deleted: {asset_name}\033[0m')
            break

    # Upload the new asset
    url = f'https://uploads.github.com/repos/{repo}/releases/{release_id}/assets?name={os.path.basename(asset_path)}'
    headers = {
        'Authorization': f'token {token}',
        'Content-Type': 'application/x-7z-compressed',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
    }
    if delete_existing:
        with open(asset_path, 'rb') as file:
            print(f'Uploading new asset: {asset_name}')
            response = requests.post(url, headers=headers, data=file)
            response.raise_for_status()
            print(f'\033[92mUploaded asset: {os.path.basename(asset_path)} to release ID: {release_id}\033[0m')
            return response.json()
    else:
        asset_exists = False
        for asset in assets:
            if asset['name'] == asset_name:
                asset_exists = True
                break
        if not asset_exists:
            with open(asset_path, 'rb') as file:
                print(f'Uploading new asset: {asset_name}')
                response = requests.post(url, headers=headers, data=file)
                response.raise_for_status()
                print(f'\033[92mUploaded asset: {os.path.basename(asset_path)} to release ID: {release_id}\033[0m')
                return response.json()

def get_release_id(repo, tag_name, token):
    """Get the release ID for a given tag name."""
    url = f'https://api.github.com/repos/{repo}/releases/tags/{tag_name}'
    headers = {
        'Authorization': f'token {token}',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'
    }
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
    os.chdir(repo_dir)

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

def extract_board_info(each_path, file_content):
    # Regex to match the board name
    board_name_match = re.search(r'if\(\${_MSDK_BOARD_NAME_} STREQUAL "(.*?)"\)', file_content)
    # Regex to match the SHIELD value
    shield_value_match = re.search(r'set\(SHIELD\s*(TRUE|FALSE)\)', file_content)

    if board_name_match:
        board_name = board_name_match.group(1)
        if shield_value_match:
            shield_value = shield_value_match.group(1)
        else:
            shield_value = False
        return board_name, (True if 'TRUE' == shield_value else False)
    else:
        print("Some values not extracted for %s." % each_path)

    return None, None

def check_database_for_shield(db, board):
    db_check = read_data_from_db(
        db, 'SELECT sdk_config FROM Boards WHERE sdk_config REGEXP ' + f'"{board}"'
    )

    if db_check[0]:
        json_object = json.loads(db_check[1][0][0])
        if '_MSDK_SHIELD_' in json_object:
            return json_object['_MSDK_SHIELD_']
        else:
            db_check = read_data_from_db(
                db, f'SELECT display FROM Boards WHERE sdk_config REGEXP ' + f'"{board}"'
            )
            db_check = read_data_from_db(
                db, f'SELECT sdk_config FROM Displays WHERE uid == "{db_check[1][0][0]}"'
            )
            json_object = json.loads(db_check[1][0][0])
            if '_MSDK_SHIELD_' in json_object:
                return json_object['_MSDK_SHIELD_']

    return None

def package_board_files(repo_root, files_root_dir, path_list, sdk_version):
    asset_type = files_root_dir.split(os.sep)[-1]
    os.makedirs(os.path.join(repo_root, f'tmp/assets/{asset_type}'), exist_ok=True)

    support.extract_archive_from_url(
        'https://github.com/MikroElektronika/core_packages/releases/latest/download/database.7z',
        os.path.join(repo_root, 'tmp/db')
    )

    archive_list = {}
    for each_path in path_list:
        # Do not generate for generic boards
        if 'generic' in each_path:
            continue

        all_files_on_path = os.listdir(os.path.join(files_root_dir, each_path))
        shutil.copytree(
            os.path.join(files_root_dir, each_path),
            os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp/board/include/boards/{each_path}'),
            dirs_exist_ok=True
        )

        with open(os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp/board/include/boards/{each_path}/board.cmake'), 'r') as file:
            board_name, has_shield = extract_board_info(each_path, file.read())
        file.close()

        if has_shield:
            # Check the database for the shield first
            shield_path = check_database_for_shield(
                os.path.join(repo_root, 'tmp/db/necto_db.db'),
                board_name
            )
            # If not found in database, search resource files next
            if not shield_path:
                board_query = json.loads(json.load(open(os.path.join(repo_root, f'resources/queries/boards/{each_path}/Boards.json'), 'r'))['sdk_config'])
                if '_MSDK_SHIELD_' in board_query:
                    shield_path = board_query['_MSDK_SHIELD_']
            # Finally, if shield found, copy it to package as well
            if shield_path:
                shutil.copytree(
                    os.path.join(repo_root, f'bsp/board/include/shields/{shield_path}'),
                    os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp/board/include/shields/{shield_path}'),
                    dirs_exist_ok=True
                )

        display_name = None
        display_names = read_data_from_db(
           os.path.join(repo_root, 'tmp/db/necto_db.db'),
           'SELECT name FROM Boards WHERE sdk_config REGEXP ' + f'"{board_name}"'
        )

        if not display_names[0]:
            display_name = json.load(open(os.path.join(repo_root, f'resources/queries/boards/{each_path}/Boards.json'), 'r'))['name']

        icon = None
        icon_root = f'https://raw.githubusercontent.com/MikroElektronika/mikrosdk_v2/mikroSDK-{sdk_version}/resources/'
        icon = read_data_from_db(
           os.path.join(repo_root, 'tmp/db/necto_db.db'),
           'SELECT icon FROM Boards WHERE sdk_config REGEXP ' + f'"{board_name}"'
        )

        if not icon[0]:
            icon = icon_root + json.load(open(os.path.join(repo_root, f'resources/queries/boards/{each_path}/Boards.json'), 'r'))['icon']
        else:
            leaf = icon[1][0][0].split('/')[-1]
            if not leaf.startswith('board'):
                icon = icon_root + icon[1][0][0].replace(leaf, f'board-{leaf}')
            else:
                icon = icon_root + icon[1][0][0]

        create_custom_archive(
            os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp'),
            os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_path}.7z')
        )
        os.chdir(repo_root)

        if display_name:
            query_file = '\'{"package":"' + each_path + '"}\''
            archive_list.update(
                    {
                        display_name:
                        {
                            "name": board_name,
                            "display_name": display_name,
                            "type": "board",
                            "icon": icon,
                            "package_name": each_path,
                            "hash": hash_directory_contents(os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp')),
                            "category": "Board Package",
                            "package_rel_path": f'tmp/assets/{asset_type}/{each_path}.7z',
                            "install_location": f"%APPLICATION_DATA_DIR%/packages/sdk/mikroSDK_v2/src/bsp",
                            "db_query": f'UPDATE Boards SET installer_package = {query_file} WHERE name = \"{display_name}\"'
                        }
                    }
                )
        else:
            for each_display_name in display_names[1]:
                query_file = '\'{"package":"' + each_path + '"}\''
                archive_list.update(
                    {
                        each_display_name[0]:
                        {
                            "name": board_name,
                            "display_name": each_display_name[0],
                            "type": "board",
                            "icon": icon,
                            "package_name": each_path,
                            "hash": hash_directory_contents(os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp')),
                            "category": "Board Package",
                            "package_rel_path": f'tmp/assets/{asset_type}/{each_path}.7z',
                            "install_location": f"%APPLICATION_DATA_DIR%/packages/sdk/mikroSDK_v2/src/bsp",
                            "db_query": f'UPDATE Boards SET installer_package = {query_file} WHERE name = \"{each_display_name[0]}\"'
                        }
                    }
                )

        shutil.rmtree(os.path.join(repo_root, f'tmp/assets/{asset_type}/bsp'))

    return archive_list

def package_card_files(repo_root, files_root_dir, path_list, sdk_version):
    asset_type = files_root_dir.split(os.sep)[-1]
    os.makedirs(os.path.join(repo_root, f'tmp/assets/{asset_type}'), exist_ok=True)

    support.extract_archive_from_url(
        'https://github.com/MikroElektronika/core_packages/releases/latest/download/database.7z',
        os.path.join(repo_root, 'tmp/db')
    )

    archive_list = {}
    existing_cards = []
    for each_path in path_list:
        # Do not generate for generic boards
        if 'generic' in each_path:
            continue

        os.makedirs(os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_path}'), exist_ok=True)
        shutil.copyfile(
            os.path.join(files_root_dir, each_path, 'mcu_card.h'),
            os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_path}/mcu_card.h')
        )

        mcu_card_name = each_path
        display_names = read_data_from_db(
            os.path.join(repo_root, 'tmp/db/necto_db.db'),
            'SELECT name FROM Devices WHERE sdk_config REGEXP ' + f'"{mcu_card_name.upper()}"'
        )

        icon = None
        icon_root = 'https://raw.githubusercontent.com/MikroElektronika/mikrosdk_v2/master/resources/'
        icon = read_data_from_db(
            os.path.join(repo_root, 'tmp/db/necto_db.db'),
            'SELECT icon FROM Devices WHERE sdk_config REGEXP ' + f'"{mcu_card_name.upper()}"'
        )

        if icon[0]:
            icon = icon_root + icon[1][0][0]

        for each_display_name in display_names[1]:
            mcu_name = read_data_from_db(
                os.path.join(repo_root, 'tmp/db/necto_db.db'),
                f'SELECT def_file FROM Devices WHERE name=="{each_display_name[0]}"'
            )[1][0][0].split('.')[0]
            mcu_name = mcu_name.replace('DSPIC', 'dsPIC')
            package_name = '_'.join(each_display_name[0].split()).lower().replace('-','')
            create_custom_archive(
                os.path.join(repo_root, f'tmp/assets/{asset_type}/{mcu_card_name}'),
                os.path.join(repo_root, f'tmp/assets/{asset_type}/{package_name}.7z')
            )
            os.chdir(repo_root)
            query_file = '\'{"package":"' + package_name + '"}\''
            archive_list.update(
                {
                    each_display_name[0]:
                    {
                        "name": mcu_card_name,
                        "display_name": each_display_name[0],
                        "type": "card",
                        "icon": icon,
                        "package_name": package_name,
                        "hash": hash_directory_contents(os.path.join(repo_root, f'tmp/assets/{asset_type}/{mcu_card_name}')),
                        "category": "Card Package",
                        "package_rel_path": f'tmp/assets/{asset_type}/{package_name}.7z',
                        "install_location": f"%APPLICATION_DATA_DIR%/packages/sdk/mikroSDK_v2/src/bsp/board/include/mcu_cards/{each_path}/{mcu_name}",
                        "db_query": f'UPDATE Devices SET installer_package = {query_file} WHERE name = \"{each_display_name[0]}\"'
                    }
                }
            )

            existing_cards.append(package_name)

        shutil.rmtree(os.path.join(repo_root, f'tmp/assets/{asset_type}/{mcu_card_name}'))

    if os.path.exists(os.path.join(os.getcwd(), 'resources/queries/cards')):
        for each_query_path in os.listdir(os.path.join(os.getcwd(), 'resources/queries/cards')):
            if each_query_path not in existing_cards:
                print('Adding new card: %s' % each_query_path)
                json_device = json.load(open(os.path.join(os.getcwd(), 'resources/queries/cards', each_query_path, 'Devices.json')))
                if 'pim' not in each_query_path:
                    card_path = json_device['uid'].rsplit('_', 1)[0].lower()
                else:
                    card_path = json_device['uid'].lower()
                os.makedirs(os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_query_path}'), exist_ok=True)
                shutil.copyfile(
                    os.path.join(files_root_dir, card_path, 'mcu_card.h'),
                    os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_query_path}/mcu_card.h')
                )
                package_name = json_device['uid'].lower()
                create_custom_archive(
                    os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_query_path}'),
                    os.path.join(repo_root, f'tmp/assets/{asset_type}/{package_name}.7z')
                )
                query_file = '\'{"package":"' + package_name + '"}\''
                archive_list.update(
                    {
                        json_device['name']:
                        {
                            "name": json_device['uid'].rsplit('_', 1)[0].lower(),
                            "display_name": json_device['name'],
                            "type": "card",
                            "icon": f'https://raw.githubusercontent.com/MikroElektronika/mikrosdk_v2/master/resources/{json_device['icon']}',
                            "package_name": package_name,
                            "hash": hash_directory_contents(os.path.join(repo_root, f'tmp/assets/{asset_type}/{each_query_path}')),
                            "category": "Card Package",
                            "package_rel_path": f'tmp/assets/{asset_type}/{package_name}.7z',
                            "install_location": f"%APPLICATION_DATA_DIR%/packages/sdk/mikroSDK_v2/src/bsp/board/include/mcu_cards/{card_path}/{json_device['def_file'].split('.')[0]}",
                            "db_query": f'UPDATE Devices SET installer_package = {query_file} WHERE name = \"{json_device['name']}\"'
                        }
                    }
                )

    return archive_list

def fetch_live_packages(url):
    response = requests.get(url)
    with open(os.path.join(os.path.dirname(__file__), os.path.basename(url)), 'wb') as file:
        file.write(response.content)
    file.close()
    with open(os.path.join(os.path.dirname(__file__), os.path.basename(url)), 'r') as file:
        metadata_json = json.load(file)
    file.close()
    os.remove(os.path.join(os.path.dirname(__file__), os.path.basename(url)))
    return metadata_json['packages'], metadata_json

def check_files_in_directory(directory_path):
    # Check if the directory exists and is a directory
    if os.path.exists(directory_path) and os.path.isdir(directory_path):
        files = []
        # Recursively walk through the directory
        for root, _, filenames in os.walk(directory_path):
            for filename in filenames:
                files.append(os.path.join(root, filename))
        return files
    else:
        print("The directory does not exist.")
        return []

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

    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("token", help="GitHub Token")
    parser.add_argument("repo", help="Repository name, e.g., 'username/repo'")
    parser.add_argument("tag_name", help="Tag name, e.g., 'mikroSDK-2.11.1'")
    parser.add_argument("package_boards_or_mcus", help="Boards release, e.g. 'True'", type=str2bool, default=False)
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

    assets = get_all_release_assets(args.repo, release_id, args.token)

    metadata_content = {}
    if not args.package_boards_or_mcus:
        if manifest_folder:
            archive_path = os.path.join(repo_dir, 'mikrosdk.7z')
            print('Creating archive: %s' % archive_path)
            # Left previous approach with version
            # create_7z_archive(version, repo_dir, archive_path)
            # New approach with fixed path
            create_7z_archive('mikroSDK_v2', repo_dir, archive_path)
            print('Archive created successfully: %s' % archive_path)
            metadata_content['mikrosdk'] = {'version': version}
            upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token, assets)
            print('Asset "%s" uploaded successfully to release ID: %s' % ('mikrosdk', release_id))

    if os.path.exists(os.path.join(repo_dir, 'resources/images')):
        archive_path = os.path.join(repo_dir, 'images.7z')
        print('Creating archive: %s' % archive_path)
        create_custom_archive('resources/images', archive_path)
        os.chdir(repo_dir)
        metadata_content['images'] = {'hash': hash_directory_contents(os.path.join(repo_dir, 'resources/images'))}
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token, assets)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('images', release_id))

    if not args.package_boards_or_mcus:
        if os.path.exists(os.path.join(repo_dir, 'templates/necto')):
            archive_path = os.path.join(repo_dir, 'templates.7z')
            print('Creating archive: %s' % archive_path)
            create_custom_archive('templates/necto', archive_path)
            os.chdir(repo_dir)
            metadata_content['templates'] = {'hash': hash_directory_contents(os.path.join(repo_dir, 'templates/necto'))}
            print('Archive created successfully: %s' % archive_path)
            upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token, assets)
            print('Asset "%s" uploaded successfully to release ID: %s' % ('templates', release_id))

    if os.path.exists(os.path.join(repo_dir, 'resources/queries')):
        archive_path = os.path.join(repo_dir, 'queries.7z')
        print('Creating archive: %s' % archive_path)
        create_custom_archive('resources/queries', archive_path)
        os.chdir(repo_dir)
        print('Archive created successfully: %s' % archive_path)
        upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token, assets)
        print('Asset "%s" uploaded successfully to release ID: %s' % ('queries', release_id))

    # Package all boards as separate packages
    packages = {}
    if check_files_in_directory(os.path.join(os.getcwd(), 'resources/queries/boards')) or not args.package_boards_or_mcus:
        packages = package_board_files(
            repo_dir,
            os.path.join(os.getcwd(), 'bsp/board/include/boards'),
            os.listdir(os.path.join(os.getcwd(), 'bsp/board/include/boards')),
            args.tag_name.replace('mikroSDK-', '')
        )

        with open(os.path.join(repo_dir, 'tmp/packages_boards.json'), 'w') as metadata:
            json.dump(packages, metadata, indent=4)

    # Package all cards as separate packages
    if check_files_in_directory(os.path.join(os.getcwd(), 'resources/queries/cards')) or not args.package_boards_or_mcus:
        packages_cards = package_card_files(
            repo_dir,
            os.path.join(os.getcwd(), 'bsp/board/include/mcu_cards'),
            os.listdir(os.path.join(os.getcwd(), 'bsp/board/include/mcu_cards')),
            args.tag_name.replace('mikroSDK-', '')
        )
        packages.update(packages_cards)

        with open(os.path.join(repo_dir, 'tmp/packages_cards.json'), 'w') as metadata:
            json.dump(packages_cards, metadata, indent=4)

    # Update the metadata with package details
    metadata_content.update(
        {
            "packages": packages
        }
    )

    # Upload all the board packages
    live_packages, metadata_full = fetch_live_packages('https://github.com/MikroElektronika/mikrosdk_v2/releases/latest/download/metadata.json')
    for each_package in packages:
        if args.package_boards_or_mcus:
            execute = True
            for each_metadata_package_key in live_packages.keys():
                if each_metadata_package_key == each_package:
                    # If package has been changed, update it either way
                    if packages[each_package]['hash'] == live_packages[each_metadata_package_key]['hash']:
                        execute = False
                    break
            if execute:
                upload_result = upload_asset_to_release(args.repo, release_id, os.path.join(repo_dir, f'{packages[each_package]['package_rel_path']}'), args.token, assets)
        else:
            upload_result = upload_asset_to_release(args.repo, release_id, os.path.join(repo_dir, f'{packages[each_package]['package_rel_path']}'), args.token, assets)

    # BSP asset for internal MIKROE tools
    os.chdir(repo_dir)
    archive_path = os.path.join(repo_dir, 'bsps.7z')
    print('Creating archive: %s' % archive_path)
    zip_bsp_related_files(archive_path, repo_dir)
    upload_result = upload_asset_to_release(args.repo, release_id, archive_path, args.token, assets)
    print('Asset "%s" uploaded successfully to release ID: %s' % ('bsps', release_id))

    os.makedirs(os.path.join(repo_dir, 'tmp'), exist_ok=True)
    if args.package_boards_or_mcus:
        for each_package in metadata_content['packages']:
            if each_package not in metadata_full['packages']:
                metadata_full['packages'].update(
                    {
                        each_package: metadata_content['packages'][each_package]
                    }
                )
            ## Always update the new package hash values
            metadata_full['packages'][each_package]['hash'] = packages[each_package]['hash']
        metadata_content = metadata_full
    with open(os.path.join(repo_dir, 'tmp/metadata.json'), 'w') as metadata:
        json.dump(metadata_content, metadata, indent=4)
    metadata.close()
    upload_result = upload_asset_to_release(args.repo, release_id, os.path.join(repo_dir, 'tmp/metadata.json'), args.token, assets)
