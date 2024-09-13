import os
from datetime import datetime

def find_file(root_folder, filename):
    for dirpath, dirnames, filenames in os.walk(root_folder):
        if filename in filenames:
            rel_path = dirpath.replace(os.getcwd(), '').replace(os.path.sep, '/')
            return f'https://github.com/MikroElektronika/mikrosdk_v2/blob/master{rel_path}/{filename}'
    ## By default, return main markdown file link
    return 'https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog.md'

def create_message():
    # Get the current date and time
    current_time = datetime.now().strftime('%a %b %d %H:%M:%S %Z %Y')

    # Retrieve full file link
    readme_path = find_file(
        os.path.join(os.getcwd(), "changelog"),
        f'{datetime.now().strftime("%Y-%m-%d")}.md'
    )

    # Construct the message
    message = f"Release for {current_time}:\n\n"
    message += f"+ For more information on todays release, visit following [README]({readme_path})\n"

    return message

if __name__ == "__main__":
    print(create_message())
