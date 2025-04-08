import os, re, pytz
from datetime import datetime

import support as support

def find_file(root_folder, filename):
    for dirpath, dirnames, filenames in os.walk(root_folder):
        if filename in filenames:
            rel_path = dirpath.replace(os.getcwd(), '').replace(os.path.sep, '/')
            return f'https://github.com/MikroElektronika/mikrosdk_v2/blob/master/{rel_path[1:]}/{filename}', os.path.join(os.getcwd(), f'{rel_path[1:]}/{filename}')
    ## By default, return main markdown file link
    return 'https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog.md', os.path.join(os.getcwd(), 'changelog.md')

def extract_new_hardware_from_md(md_file_path_or_url):
    md_file_path = md_file_path_or_url
    if md_file_path_or_url.startswith('http'):
        # Extract the filename from the URL
        filename = os.path.basename(md_file_path_or_url)
        # Download the file to the current working directory
        downloaded_file = support.download_file(md_file_path_or_url, filename)
        if not downloaded_file:
            print("Error: Could not download the markdown file.")
            return
        # Set the markdown file path to the downloaded file
        md_file_path = downloaded_file

    # Read the markdown file content
    try:
        with open(md_file_path, 'r') as file:
            content = file.read()
    except FileNotFoundError:
        print(f"File not found: {md_file_path}")
        return

    # Regular expression to capture the "NEW HARDWARE" section
    pattern = re.compile(r'### NEW HARDWARE\s+Support added for following hardware:(.*?)---', re.DOTALL)
    match = pattern.search(content)
    string_out = ''
    if not match:
        string_out = 'Preconfigured Clock settings addeded for following hardware:\n'
        pattern = re.compile(r'### Improvements\s+Preconfigured Clock settings added for following hardware:(.*?)---', re.DOTALL)
        match = pattern.search(content)


    if match:
        # Extracted section (it's a block of text, including newlines)
        new_hardware_section = match.group(1).strip()

        # Extract the individual hardware links
        hardware_links = re.findall(r'\+ \[(.*?)\]\((.*?)\)', new_hardware_section)

        # Display the extracted hardware information
        if hardware_links:
            for hardware_name, hardware_link in hardware_links:
                string_out += f"+ [{hardware_name}]({hardware_link})\n"

    # Clean up the downloaded file if applicable
    if md_file_path_or_url.startswith('http'):
        os.remove(md_file_path)  # Remove the temporary downloaded file

    return string_out

def create_message():
    # Set the desired timezone, for example, "Europe/Belgrade"
    timezone = pytz.timezone('Europe/Belgrade')

    # Get the current date and time
    current_time = datetime.now(timezone).strftime('%a %b %d %H:%M:%S %Z %Y')

    # Retrieve full file link
    readme_link, readme_path = find_file(
        os.path.join(os.getcwd(), "changelog"),
        f'{datetime.now().strftime("%Y-%m-%d")}.md'
    )

    # Construct the message
    message = f"Release for {current_time}:\n\n"
    message += extract_new_hardware_from_md(readme_path)
    message += f"\n> For more information on today's release, visit following [README]({readme_link})"

    return message

if __name__ == "__main__":
    print(create_message())
