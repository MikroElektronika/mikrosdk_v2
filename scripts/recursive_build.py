import subprocess
import requests
import re
import os
import sqlite3
import json
from pathlib import Path

# Define the repository owner and name
repo_owner = "MikroElektronika"
repo_name = "mikrosdk_v2"

# Path to the necto_db.db file.
dbPath = '/home/runner/.MIKROE/NECTOStudio7/databases/necto_db.db'

# Path to the released SDK folder.
sdkPath = '/home/runner/.MIKROE/NECTOStudio7/packages/sdk'

# Path for storing artifacts.
testPath = '/home/runner/test_results'

# Path to sdk_build_automation tool.
toolPath = '/home/runner/MikroElektronika/NECTOStudio/bin'

# Global variable to trace failed tests.
build_failed = False

# Supported compilers list for each architecture.
compiler_list = {
    'ARM': ['gcc_arm_none_eabi', 'clang-llvm', 'mikrocarm'],
    'RISCV': ['xpack-riscv-none-embed-gcc', 'clang-llvm-riscv'],
    'PIC': ['mikrocpic', 'mchp_xc8'],
    'DSPIC': ['mikrocdspic', 'mchp_xc16'],
    'PIC32': ['mikrocpic32', 'mchp_xc32'],
    'AVR': ['mikrocavr']
}

# Extracts the SDK version from the manifest.json file.
def get_sdk_version(manifest_path):
    with open(manifest_path, 'r') as f:
        manifest = json.load(f)

        return manifest.get("sdk-version", "")

# Runs the bash command.
def run_cmd(cmd):
    global build_failed
    # Blue color for build tool command command.
    print(f"\033[94m{cmd}\033[0m")
    
    try:
        # Store all the output lines to print only important ones.
        output = subprocess.check_output(cmd, shell=True, text=True)
        for line in output.splitlines():
            if line.startswith("Building:"):

                # White color for the current setup build.
                print(line)
            elif "Build success!" in line:

                # Green color for success.
                print("\033[92m{}\033[0m".format(line))
            elif "Build failed" in line:

                # Red color for failure.
                print("\033[91m{}\033[0m".format(line))
                build_failed = True

    # Error handling for failed builds not to fail the job.
    except subprocess.CalledProcessError as e:
        for line in e.output.splitlines():
            if line.startswith("Building:"):

                # White color for the current setup build.
                print(line)
            elif "Build success!" in line:

                # Green color for success.
                print(f"\033[92m{line}\033[0m")  # Green color for success
            elif "Build failed" in line:

                # Red color for failure.
                print(f"\033[91m{line}\033[0m")  # Red color for failure
                build_failed = True

# Runs the build commands for each member of mcu_list, board_list, and mcu_card_list.
def run_builds(changes_dict):
    # Get the SDK version from manifest.json file.
    sdk_version = get_sdk_version('manifest.json').replace(".", "")

    # Run build for all MCUs from mcu_list.
    print(f"\033[93mRunning build for {len(changes_dict['mcu_list'])} MCUs\033[0m")
    for mcu in changes_dict['mcu_list']:
        # Get the necessary compiler for the current MCU build.
        compilers, architecture = get_compilers(mcu, is_mcu=True)
        for compiler in compilers:
            cmd = f'xvfb-run --auto-servernum --server-num=1 {toolPath}/sdk_build_automation --isBareMetal "0" --compiler "{compiler}" --sdk "mikrosdk_v{sdk_version}" --board "GENERIC_{architecture}_BOARD" --mcu "{mcu}" --installPrefix "{testPath}/mcu_build/{compiler}"'
            run_cmd(cmd)

    # Run build for all boards from board_list.
    print(f"\033[93mRunning build for {len(changes_dict['board_list'])} boards\033[0m")
    for board in changes_dict['board_list']:
        compilers = get_compilers(board, is_mcu=False)
        for compiler in compilers:
            cmd = f'xvfb-run --auto-servernum --server-num=1 {toolPath}/sdk_build_automation --isBareMetal "0" --compiler "{compiler}" --sdk "{sdk_version}" --board "{board}" --installPrefix "{testPath}/board_build/{compiler}"'
            run_cmd(cmd)

    # Run build for all MCU cards from mcu_card_list.
    print(f"\033[93mRunning build for {len(changes_dict['mcu_card_list'])} MCU cards\033[0m")
    for mcu_card in changes_dict['mcu_card_list']:
        compilers = get_compilers(mcu_card, is_mcu=True)
        for compiler in compilers:
            cmd = f'xvfb-run --auto-servernum --server-num=1 {toolPath}/sdk_build_automation --isBareMetal "0" --compiler "{compiler}" --sdk "{sdk_version}" --mcu "{mcu_card}" --installPrefix "{testPath}/mcu_card_build/{compiler}"'
            run_cmd(cmd)

# Returns the list of compilers based on the given name and type.
def get_compilers(name, is_mcu=True):
    if is_mcu:
        if any(substring in name for substring in ["ATSAM", "STM", "TM4C", "MK"]):
            return compiler_list["ARM"], "ARM"
        elif "GD32" in name:
            return compiler_list["RISCV"], "RISCV"
        elif "PIC32" in name:
            return compiler_list["PIC32"], "PIC32"
        elif any(substring in name for substring in ["DSPIC", "PIC24", "dsPIC"]):
            return compiler_list["DSPIC"], "DSPIC"
        elif any(substring in name for substring in ["PIC18", "PIC16", "PIC12", "PIC10"]):
            return compiler_list["PIC"], "PIC"
        elif "AT" in name and "ATSAM" not in name:
            return compiler_list["AVR"], "AVR"
    else:
        conn = sqlite3.connect(dbPath)
        cursor = conn.cursor()

        # Get all device_uids associated with the board name.
        cursor.execute(f"""
            SELECT device_uid
            FROM BoardToDevice
            WHERE board_uid = '{name}';
        """)
        device_uids = cursor.fetchall()
        
        # Initialize an empty set to store unique compiler keys.
        unique_compilers = set()
        result_compilers = []

        # Get necessary compilers for all supported MCU cards for this board.
        for device_uid in device_uids:
            device_uid = device_uid[0]
            if any(substring in device_uid for substring in ["ATSAM", "STM", "TM4C", "MK"]):
                if "ARM" not in unique_compilers:
                    unique_compilers.add("ARM")
                    result_compilers.extend(compiler_list["ARM"])
            elif "GD32" in device_uid:
                if "RISCV" not in unique_compilers:
                    unique_compilers.add("RISCV")
                    result_compilers.extend(compiler_list["RISCV"])
            elif "PIC32" in device_uid:
                if "PIC32" not in unique_compilers:
                    unique_compilers.add("PIC32")
                    result_compilers.extend(compiler_list["PIC32"])
            elif any(substring in device_uid for substring in ["dsPIC", "PIC24"]):
                if "DSPIC" not in unique_compilers:
                    unique_compilers.add("DSPIC")
                    result_compilers.extend(compiler_list["DSPIC"])
            elif any(substring in device_uid for substring in ["PIC18", "PIC16", "PIC12", "PIC10"]):
                if "PIC" not in unique_compilers:
                    unique_compilers.add("PIC")
                    result_compilers.extend(compiler_list["PIC"])
            elif "AT" in device_uid and "ATSAM" not in device_uid:
                if "AVR" not in unique_compilers:
                    unique_compilers.add("AVR")
                    result_compilers.extend(compiler_list["AVR"])

        conn.close()
        return result_compilers

# Fetches the two latest releases from the GitHub repository.
def get_latest_releases():
    try:
        # GitHub API URL to fetch tags
        tags_url = f"https://api.github.com/repos/{repo_owner}/{repo_name}/tags"

        # Send request to GitHub API
        response = requests.get(tags_url)
        response.raise_for_status()
        tags = response.json()

        # Return the two most recent tags
        return [tag['name'] for tag in tags[:2]]
    except requests.RequestException as e:
        print(f"Error fetching tags: {e}")
        return None, None

# Fetches the changed files between two releases using the GitHub API.
def get_changed_files():
    latest, previous = get_latest_releases()
    if not latest or not previous:
        return []

    try:
        # GitHub API URL to compare commits between two tags
        compare_url = f"https://api.github.com/repos/{repo_owner}/{repo_name}/compare/{previous}...{latest}"

        # Send request to GitHub API
        response = requests.get(compare_url)
        response.raise_for_status()
        compare_data = response.json()

        # Extract the list of changed files
        changed_files = [file['filename'] for file in compare_data['files']]
        
        # Write all detected changed files to changed_files.txt
        with open('changed_files.txt', 'w') as f:
            for line in changed_files:
                f.write(line + '\n')

        return changed_files
    except requests.RequestException as e:
        print(f"Error running git diff: {e}")
        return []

# Classifies changes into 4 different Cases.
def classify_changes(changes_dict):
    # Case 1 - MCU card files were changed. 
    case_1_paths = ["bsp/board/include/mcu_cards"]
    # Case 2 - Board files were changed.
    case_2_paths = ["bsp/board/include/boards"]
    # Case 3 - Target files were changed.
    case_3_paths = ["targets"]
    # Case 4 - Any other file was changed.
    
    # List for storing CMakeList files affected by the changes.
    cmake_files = []
    # List for storing source and header files affected by the changes.
    other_files = []

    sdk_version = get_sdk_version('manifest.json')

    for file in changes_dict['changed_files']:
        # Ensure we handle paths correctly.
        file = file.replace('\\', '/')
        # Case 4 - return empty data lists which means that we need to run build for everything.
        if any(file.startswith(prefix) for prefix in ["api", "cmake", "components", "drv", "hal", "middleware", "platform", "thirdparty"]):
            changes_dict['mcu_list'] = []
            changes_dict['board_list'] = []
            changes_dict['mcu_card_list'] = []
            return
        
        # Case 1 - find MCU card name that was affected by the changes.
        if any(file.startswith(path) for path in case_1_paths):
            # MCU card name is always present as a folder name.
            folder_name = Path(file).parts[4]
            # Add it to the list for building if it is not present there already.
            if folder_name not in changes_dict['mcu_card_list']:
                changes_dict['mcu_card_list'].append(folder_name)
        
        # Case 2 - obtain the _MSDK_BOARD_NAME_ variable from board.cmake file.
        if any(file.startswith(path) for path in case_2_paths):
            # Board name can differ from folder name but always has the same path.
            folder_name = Path(file).parts[4]
            board_cmake_file = Path(sdkPath) / f'{sdk_version}/src/bsp/board/include/boards' / folder_name / 'board.cmake'
            # If board.cmake file was found add it to the list for building in sdk_config format.
            if board_cmake_file.exists():
                extract_board_name(board_cmake_file, changes_dict)
        
        # Case 3 - store all the changed files from targets folder.
        if any(file.startswith(path) for path in case_3_paths):
            # Check if it is CMake file or source/header file and store accordingly.
            if file.endswith('CMakeLists.txt') or file.endswith('CMakeLists.cmake'):
                cmake_files.append(file)
            else:
                other_files.append(file)
    
    # If Case 3 - find all the regexes for MCUs that were affected by the changes.
    if cmake_files or other_files:
        # If it is CMake file simply extract the regex from it. 
        for cmake_file in cmake_files:
            extract_regex(Path(cmake_file), changes_dict)

        # If it is source or header file find the CMake that handles this file.
        for other_file in other_files:
            if other_file.endswith('.h'):
                # If it is header file do additional checkings.
                handle_header_file(Path(other_file), changes_dict)
            else:
                # If it is a source file find appropriat CMake file in current or 2 parent folders.
                folder_path = Path(other_file).parent
                check_and_extract_regex(folder_path, changes_dict)

# Checks and extracts regex from CMakeLists.txt or CMakeLists.cmake files in the given folder or its parents.
def check_and_extract_regex(folder_path, changes_dict):
    # Check for CMake in the same folder with the source file and in 2 parent folders.
    for iterations in range(3):
        cmake_file = folder_path / 'CMakeLists.txt'
        if cmake_file.exists():
            # Extract regex for MCUs from found CMake file.
            extract_regex(cmake_file, changes_dict)
            return
        cmake_file = folder_path / 'CMakeLists.cmake'
        if cmake_file.exists():
            # Extract regex for MCUs from found CMake file.
            extract_regex(cmake_file, changes_dict)
            return
        folder_path = folder_path.parent

# Extracts and stores regex from the given cmake file.
def extract_regex(cmake_file, changes_dict):
    sdk_version = sdk_version = get_sdk_version('manifest.json')

    try:
        with open(str(sdkPath) + f'/{sdk_version}/src/' + str(cmake_file), 'r') as file:
            content = file.read()
            # Find all matches for MCU_* MATCHES or MCU_* STREQUAL.
            regexes = re.findall(r'\${[^}]*MCU[^}]*}\s+(?:MATCHES|STREQUAL)\s+"([^"]+)"', content)
            # Store all the found regexes.
            changes_dict['regex_list'].extend(regexes)
    except Exception as e:

        # Return error if couldn't read the CMake file.
        print(f"Error reading {cmake_file}: {e}")

# Extracts the _MSDK_BOARD_NAME_ from the board.cmake file.
def extract_board_name(board_cmake_file, changes_dict):
    try:
        with open(board_cmake_file, 'r') as file:
            content = file.read()
            # Find all matches for _MSDK_BOARD_NAME_ STREQUAL "BOARD_NAME".
            board_names = re.findall(r'\${_MSDK_BOARD_NAME_}\s+STREQUAL\s+"([^"]+)"', content)
            # Store all found _MSDK_BOARD_NAME_ values in sdk_config format.
            for board_name in board_names:
                changes_dict['board_list'].append(f'"_MSDK_BOARD_NAME_":"{board_name}"')
    except Exception as e:
        
        # Return error if couldn't read the board.cmake file.
        print(f"Error reading {board_cmake_file}: {e}")

# Handles header files to find MCU names or check corresponding CMake files.
def handle_header_file(header_file, changes_dict):
    # If changes were done to the common folder simply get the MCU name from folder name.
    if "common" in header_file.parts:
        obtain_mcu_name_from_path(header_file, changes_dict)

    # If changes were done to the include folder find a corresponding src folder with CMake file.
    elif "include" in header_file.parts:
        find_corresponding_src_folder(header_file, changes_dict)

# Obtains MCU name from the header file path.
def obtain_mcu_name_from_path(header_file, changes_dict):
    try:
        path_parts = header_file.parts
        # For ARM and RISCV MCUs we have different folder structure with extra folder after mcu_definitions and mcu_reg_addresses.
        if 'arm' in path_parts or 'riscv' in path_parts:
            if 'STM32' in path_parts:
                idx = path_parts.index('STM32')
                mcu_name = path_parts[idx + 1]
                # Additional check for STM32 and mcu_definitions as it has a package at the end of folder name.
                if 'mcu_definitions' in path_parts:
                    mcu_name = mcu_name[:11]
            elif 'NXP' in path_parts:
                idx = path_parts.index('NXP')
                mcu_name = path_parts[idx + 1]
            elif 'TIVA' in path_parts:
                idx = path_parts.index('TIVA')
                mcu_name = path_parts[idx + 1]
            else:
                idx = path_parts.index('GIGADEVICE')
                mcu_name = path_parts[idx + 1]
        # For all other architectures MCU name goes right after mcu_definitions or mcu_reg_addresses folder.
        else:
            if 'mcu_definitions' in path_parts:
                idx = path_parts.index('mcu_definitions')  
            else: 
                idx = path_parts.index('mcu_reg_addresses')
            mcu_name = path_parts[idx + 1]

        # Add the obtained MCU name to the list for building if it hasn't been added there already.
        if mcu_name not in changes_dict['mcu_list']:
            changes_dict['mcu_list'].append(mcu_name)
    except ValueError as e:

        # Print an error message if something went wrong.
        print(f"Error obtaining MCU name from path: {e}")

# Finds the corresponding src folder for a given header file in include folder.
def find_corresponding_src_folder(header_file, changes_dict):
    try:
        # Get the include folder index in the path.
        parts = list(header_file.parts)
        include_index = parts.index('include')

        # Add module name if it is present in include path.
        if include_index + 2 < len(parts):
            folder_name = parts[include_index + 1]
        else:
            folder_name = ''

        # Create new parts list ending with 'src/module_name if module_name folder exists'
        new_parts = parts[:include_index] + ['src']
        if folder_name:
            new_parts.append(folder_name)

        src_path = Path(*new_parts)
        
        # Get the parent folder path starting with include/
        include_path = Path(*parts[include_index:])
        
        if src_path.exists():
            # Recursively search for CMakeLists.txt or CMakeLists.cmake in src/module_name folder
            for root, dirs, files in os.walk(src_path):
                for file in files:
                    if file in ['CMakeLists.txt', 'CMakeLists.cmake']:
                        cmake_file_path = Path(root) / file
                        # If we found CMake with the changed header file extract regexes for MCUs.
                        if check_cmake_file_for_include_path(cmake_file_path, include_path):
                            extract_regex(cmake_file_path, changes_dict)
    except ValueError as e:

        # Return error if no src folder has been found.
        print(f"Error finding corresponding src folder: {e}")
    return None

# Checks if the CMake file contains the include path or parts of it.
def check_cmake_file_for_include_path(cmake_file_path, include_path):
    try:
        with open(cmake_file_path, 'r') as cmake_file:
            content = cmake_file.read()
            include_path_str = str(include_path)
            # Check for the full include path or parts of it
            if include_path_str in content or any(part in content for part in include_path_str.split('/')):
                return True
    except Exception as e:
        print(f"Error reading {cmake_file_path}: {e}")
    return False

# Define a REGEXP function for SQLite.
def regexp(expr, item):
    reg = re.compile(expr)
    return reg.search(item) is not None

# Queries the database to update mcu_card_list, board_list, and mcu_list.
def query_database(changes_dict):
    # Get the SDK version from the manifest.json file.
    sdk_version = get_sdk_version('manifest.json').replace(".", "")

    # Connect to the database.
    conn = sqlite3.connect(dbPath)

    # Create REGEXP function for python script.
    conn.create_function("REGEXP", 2, regexp)
    cursor = conn.cursor()

    # Update mcu_card_list.
    # Find all MCU cards according to the stored MCU card names that has SDK support.
    new_mcu_card_list = []
    for mcu_card in changes_dict['mcu_card_list']:
        mcu_card_upper = mcu_card.upper()
        cursor.execute(f"""
            SELECT SDKToDevice.device_uid
            FROM SDKToDevice
            INNER JOIN Devices ON SDKToDevice.device_uid = Devices.uid
            WHERE SDKToDevice.sdk_uid = 'mikrosdk_v{sdk_version}'
            AND SDKToDevice.device_uid REGEXP ?
            AND Devices.sdk_support = '1';
        """, (mcu_card_upper,))
        rows = cursor.fetchall()
        if rows:
            new_mcu_card_list.extend([row[0] for row in rows])
        else:
            changes_dict['unused'].append(mcu_card)
    changes_dict['mcu_card_list'][:] = sorted(list(set(new_mcu_card_list)))

    # Update board_list.
    # Find all boards according to the stored _MSDK_BOARD_NAME_ values that has SDK support.
    new_board_list = []
    for board in changes_dict['board_list']:
        cursor.execute(f"""
            SELECT SDKToBoard.board_uid
            FROM SDKToBoard
            INNER JOIN Boards ON SDKToBoard.board_uid = Boards.uid
            WHERE SDKToBoard.sdk_uid = 'mikrosdk_v{sdk_version}'
            AND Boards.sdk_config REGEXP ?;
        """, (board,))
        rows = cursor.fetchall()
        if rows:
            new_board_list.extend([row[0] for row in rows])
        else:
            changes_dict['unused'].append(board)
    changes_dict['board_list'][:] = sorted(list(set(new_board_list)))

    # Update mcu_list based on regex_list.
    # Find all MCUs that are not on any cards and that have SDK support.
    new_mcu_list = []
    for regex in changes_dict['regex_list']:
        # Skip regexes with only one letter.
        if len(regex) > 1:
            cursor.execute(f"""
                SELECT SDKToDevice.device_uid
                FROM SDKToDevice
                INNER JOIN Devices ON SDKToDevice.device_uid = Devices.uid
                WHERE SDKToDevice.sdk_uid = 'mikrosdk_v{sdk_version}'
                AND SDKToDevice.device_uid REGEXP ?
                AND Devices.sdk_support = '1'
                AND SDKToDevice.device_uid NOT LIKE '%\\_%' ESCAPE '\\';
            """, (regex,))
            rows = cursor.fetchall()
            if rows:
                new_mcu_list.extend([row[0] for row in rows])
            else:
                changes_dict['unused'].append(regex)
    changes_dict['mcu_list'].extend([device for device in set(new_mcu_list) if device not in changes_dict['mcu_list']])
    changes_dict['mcu_list'][:] = sorted(changes_dict['mcu_list'])

    # If all lists for building are empty this means that either changes were made to Case 4 folders
    #   or we are running build for everything. 
    # In this case get all the SDK supported boards, MCU cards and MCUs from the database.
    if not changes_dict['mcu_list'] and not changes_dict['board_list'] and not changes_dict['mcu_card_list']:
        cursor.execute(f"""
            SELECT SDKToDevice.device_uid
            FROM SDKToDevice
            INNER JOIN Devices ON SDKToDevice.device_uid = Devices.uid
            WHERE SDKToDevice.sdk_uid = 'mikrosdk_v{sdk_version}'
            AND SDKToDevice.device_uid NOT LIKE '%\\_%' ESCAPE '\\';
        """)
        rows = cursor.fetchall()
        if rows:
            new_mcu_list.extend([row[0] for row in rows])
        else:
            changes_dict['unused'].append(regex)
        changes_dict['mcu_list'].extend([device for device in set(new_mcu_list) if device not in changes_dict['mcu_list']])
        changes_dict['mcu_list'][:] = sorted(changes_dict['mcu_list'])

        cursor.execute(f"""
            SELECT device_uid
            FROM SDKToDevice
            WHERE sdk_uid = 'mikrosdk_v{sdk_version}'
            AND device_uid REGEXP '_';
        """)
        rows = cursor.fetchall()
        if rows:
            new_mcu_card_list.extend([row[0] for row in rows])
        else:
            changes_dict['unused'].append(mcu_card)
        changes_dict['mcu_card_list'][:] = sorted(list(set(new_mcu_card_list)))

        cursor.execute(f"""
            SELECT board_uid
            FROM SDKToBoard
            WHERE sdk_uid = 'mikrosdk_v{sdk_version}';
        """)
        rows = cursor.fetchall()
        if rows:
            new_board_list.extend([row[0] for row in rows])
        else:
            changes_dict['unused'].append(board)
        changes_dict['board_list'][:] = sorted(list(set(new_board_list)))

    conn.close()

# Writes the result dictionary to a JSON file and ensures testPath exists.
def write_results_to_file(changes_dict):
    with open(f'{testPath}/built_changes.json', 'w+') as json_file:
        json.dump(changes_dict, json_file, indent=4)

    print(f"All the data for build has been written to {testPath}/built_changes.json")

    for item in changes_dict['unused']:
        print(f"Couldn't find {item} in the database")

def main():
    global build_failed

    # Initialize the changes dictionary.
    changes_dict = {
        'regex_list': [],
        'mcu_list': [],
        'board_list': [],
        'mcu_card_list': [],
        'unused': [],
        'changed_files': []
    }

    # Create a folder for job artifacts. 
    os.makedirs(testPath, exist_ok=True)

    # Check if it's a job for global build or not.
    if os.getenv('BUILD_ALL') == '0':
        # If it's not - get the changed files.
        changes_dict['changed_files'] = get_changed_files()

        # Classify the changed files.
        classify_changes(changes_dict)

    # Get the necessary data from the database.
    query_database(changes_dict)

    # Finally, run the SDK build tool.
    run_builds(changes_dict)

    # Write all the used info for building to artifact folder.
    write_results_to_file(changes_dict)

    if build_failed == True:
        # Red text for failure.
        print("\033[91mRecursive Build Failed!\033[0m")
        # Fail the job as well.
        exit(1)
    else:
        # Green text for success.
        print("\033[92mRecursive Build Success!\033[0m")

if __name__ == "__main__":
    main()
