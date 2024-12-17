import support, sqlite3, os, requests, json

db_path = os.path.join(os.path.dirname(__file__), 'necto_db.db')

# Function to download the database
def download_database(db_url, download_path):
    response = requests.get(db_url)
    if response.status_code == 200:
        with open(download_path, 'wb') as db_file:
            db_file.write(response.content)
    else:
        raise Exception("Failed to download database!")

def get_board_info_from_db(db_path, board_name):
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Get the board uid based on the display name
        cursor.execute("""
            SELECT uid
            FROM Boards
            WHERE name = ?;
        """, (board_name,))
        result = cursor.fetchone()

        if result:
            board_uid = result[0]
        else:
            return None, None, None, None

        # Query to get necessary information from Boards
        cursor.execute("""
            SELECT soldered_device, mikrobus_count, display_socket, display
            FROM Boards
            WHERE uid = ?;
        """, (board_uid,))
        # Fetch the result
        result = cursor.fetchone()

        soldered_device, mikrobus_count, display_socket, display = result

        # Query to get socket_uid
        cursor.execute("""
            SELECT socket_uid
            FROM BoardToSocket
            WHERE board_uid = ?;
        """, (board_uid,))
        result = cursor.fetchall()
        socket_list = [socket_uid[0].replace('_SOCKET', '').replace('MCU_CARD_V7', 'MCU Card V7') for socket_uid in result]

        # Get Display names
        if display_socket == 'BUILT_IN_DISPLAY':
            cursor.execute("""
                SELECT name
                FROM Displays
                WHERE uid = ?;
            """, (display,))
            result = cursor.fetchone()
            displays = [result[0]]
        elif display_socket == 'NO_DISPLAY':
            displays = []
        else:
            cursor.execute("""
                SELECT name
                FROM Displays
                WHERE display_socket = ?;
            """, (display_socket,))
            result = cursor.fetchall()
            displays = [display_name[0] for display_name in result if 'TSC2003' not in display_name[0]]

    except sqlite3.Error as e:
        # Handle the database error
        return None
    finally:
        conn.close()

    return soldered_device, mikrobus_count, displays, socket_list

def get_card_info_from_db(db_path, device_name):
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Query to get device_uid based on display name
        cursor.execute("""
            SELECT uid
            FROM Devices
            WHERE name = ?;
        """, (device_name,))
        result = cursor.fetchone()

        if result:
            device_uid = result[0]
        else:
            # If nothing was found return None
            return None, None, None, None, None, None

        # Query to get necessary information from Devices
        cursor.execute("""
            SELECT flash, max_speed, ram, sdk_config
            FROM Devices
            WHERE uid = ?;
        """, (device_uid,))
        result = cursor.fetchone()

        if result:
            flash, max_speed, ram, sdk_config = result

            sdk_config_json = json.loads(sdk_config)
            core_name = sdk_config_json.get('CORE_NAME', '')
        else:
            print(f"No device found with uid: {device_uid}")

        # Process RAM value to display it in KB
        ram_int = int(ram) / 1024
        ram = str(ram_int)

        # Query to get package_uid
        cursor.execute("""
            SELECT DISTINCT package_uid
            FROM DeviceToPackage
            WHERE device_uid = ?;
        """, (device_uid,))
        package_uid_result = cursor.fetchone()

        package_uid = package_uid_result[0]

        # Query to get socket_uid
        cursor.execute("""
            SELECT DISTINCT socket_uid
            FROM DeviceToSocket
            WHERE device_uid = ?;
        """, (device_uid,))
        socket_uid_result = cursor.fetchone()

        socket_uid = socket_uid_result[0].replace('_SOCKET', '').replace('MCU_CARD_V7', 'MCU Card V7')
    except sqlite3.Error as e:
        return None
    finally:
        conn.close()

    return flash, max_speed.replace('.000', ''), ram.replace('.0', ''), core_name.replace('M4EF', 'M4').replace('M4DSP', 'M4'), package_uid, socket_uid

def form_extra_information(asset_type, package_name, asset_url, token):
    # Process MCU Card
    if asset_type == 'card':
        # Get REV version from mcu_card.h file
        rev_version = ''
        asset_path = os.path.join(os.path.dirname(__file__), asset_type, f'{package_name}')
        support.extract_archive_from_url(asset_url, asset_path, token)
        with open(os.path.join(asset_path, 'mcu_card.h'), 'r') as header_file:
            for line in header_file:
                if 'MCU_CARD_REV_MAJOR' in line:
                    rev_version = line.strip().split(' ')[-1].replace('(', '').replace(')', '')
                if 'MCU_CARD_REV_MINOR' in line:
                    rev_version += '.' + line.strip().split(' ')[-1].replace('(', '').replace(')', '')

        # Get necessary Card info from the database
        flash_size, max_speed, ram_size, core_name, package_uid, socket = get_card_info_from_db(db_path, package_name)
        # If nothing was found - return an empty dictionary
        if flash_size == None:
            return {}

        # Form extra information
        pin_num = package_uid.split('/')[0]
        doc_extra_info = {
            'extra_information' :
                {
                    'RAM Size' : f'{ram_size} KB',
                    'Flash Size' : f'{flash_size} KB',
                    'Maximum Speed' : f'{max_speed} MHz',
                    'Core Name' : core_name,
                    'Pin Count': pin_num,
                    'MCU Card Socket': socket
                }
        }
        if rev_version:
            doc_extra_info['extra_information'].update(
                {
                    'Latest Rev Version': rev_version
                }
            )

    # Process Board
    if asset_type == 'board':
        # Get necessary Board info from the database
        soldered_mcu, mikrobus_num, displays, sockets = get_board_info_from_db(db_path, package_name)
        # If nothing was found - return an empty dictionary
        if mikrobus_num == None:
            return {}

        # Form extra information
        doc_extra_info = {
            'extra_information' :
                {
                    'MikroBUS Count' : str(mikrobus_num)
                }
        }
        if len(displays):
            if len(displays) == 1:
                if '3' in displays[0]:
                    display_size = '3.5 inches'
                elif '4' in displays[0]:
                    display_size = '4.3 inches'
                elif '5' in displays[0]:
                    display_size = '5 inches'
                elif '7' in displays[0]:
                    display_size = '7 inches'
                elif 'Plus' in displays[0]:
                    display_size = '4.3 inches'
                else:
                    display_size = '2.8 inches'
                if 'Mikromedia' in displays[0]:
                    doc_extra_info['extra_information'].update(
                        {
                            'Supported Displays' : 'Built-In Display'
                        }
                    )
                else:
                    doc_extra_info['extra_information'].update(
                        {
                            'Supported Displays' : displays
                        }
                    )
                doc_extra_info['extra_information'].update(
                    {
                        'Display Size' : display_size
                    }
                )
            else:
                doc_extra_info['extra_information'].update(
                    {
                        'Supported Displays' : 'TFT BOARD 3 / 4 / 5 / 7'
                    }
                )
        if len(sockets) and sockets[0] != 'NONE':
            doc_extra_info['extra_information'].update(
                {
                    'Supported Sockets' : sockets
                }
            )
        else:
            doc_extra_info['extra_information'].update(
                {
                    'Soldered MCU' : soldered_mcu
                }
            )

    return doc_extra_info

def add(indexed_item_source, gh_token, es_index):
    # Download corresponding database from github
    if 'test' in es_index:
        download_database('https://github.com/MikroElektronika/core_packages/blob/main/necto_db_dev.db?raw=true', db_path)
    else:
        download_database('https://github.com/MikroElektronika/core_packages/blob/main/necto_db.db?raw=true', db_path)

    doc_extra_info = {}
    if 'category' in indexed_item_source:
        # Get extra info for boards
        if indexed_item_source['category'] == 'Board Package':
            doc_extra_info = form_extra_information('board', indexed_item_source['display_name'], indexed_item_source['download_link'], gh_token)
        # Get extra info for cards
        elif indexed_item_source['category'] == 'Card Package':
            doc_extra_info = form_extra_information('card', indexed_item_source['display_name'], indexed_item_source['download_link'], gh_token)
        if doc_extra_info != {}:
            indexed_item_source.update(doc_extra_info)
            print(f"INFO: Added \"extra_information\" to {indexed_item_source['name']}")
