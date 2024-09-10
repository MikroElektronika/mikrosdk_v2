import os
from datetime import datetime

def find_file(root_folder, filename):
    for dirpath, dirnames, filenames in os.walk(root_folder):
        if filename in filenames:
            return os.path.join(dirpath, filename), dirpath
    return None, None

found_file, file_dir = find_file(os.path.join(os.getcwd(), "changelog"), "new_boards.md")

if found_file:
    current_date = datetime.now().strftime("%Y-%m-%d")
    os.rename(found_file, os.path.join(file_dir, f'{current_date}.md'))
    with open(os.path.join(file_dir, f'{current_date}.md'), 'r') as board_changelog_file:
        board_changelog = board_changelog_file.read()
    board_changelog_file.close()
    board_changelog = board_changelog.replace('`DATE`', current_date).replace('#date', f'#{current_date}')
    with open(os.path.join(file_dir, f'{current_date}.md'), 'w') as board_changelog_file:
        board_changelog_file.write(board_changelog)
    board_changelog_file.close()
