from datetime import datetime
from bs4 import BeautifulSoup
import os
import markdown
import argparse

# Set up argument parsing to accept the markdown file path
parser = argparse.ArgumentParser(description="Process a markdown file to generate formatted release notes.")
parser.add_argument('version', type=str, help='Version of the release notes')
args = parser.parse_args()

# Fixing single quote issue
markdown_file_path = os.path.join(os.getcwd(), 'changelog', f"v{args.version.replace('mikroSDK-', '')}", 'changelog.md')

# Read the markdown content from the file path provided as a command-line argument
with open(markdown_file_path, 'r', encoding='utf-8') as file:
    markdown_content = file.read()

# Convert markdown to HTML and parse it with BeautifulSoup
html_content = markdown.markdown(markdown_content)
soup = BeautifulSoup(html_content, 'html.parser')

# Function to extract sections dynamically based on headers, excluding unwanted sections
def extract_sections(soup):
    sections = {}
    current_main_section = None
    current_sub_section = None

    for tag in soup.find_all(['h3', 'h4', 'p', 'ul']):
        if tag.name == 'h3':  # Main sections (e.g., Fixes, Improvements)
            current_main_section = tag.get_text(strip=True)
            if current_main_section.lower() != 'new hardware':  # Exclude "NEW HARDWARE"
                sections[current_main_section] = {}
        elif tag.name == 'h4' and current_main_section:  # Sub-sections (e.g., mikroSDK, CORE)
            current_sub_section = tag.get_text(strip=True)
            sections[current_main_section][current_sub_section] = []
        elif current_sub_section and tag.name == 'p':  # Paragraphs
            if current_main_section in sections:
                sections[current_main_section][current_sub_section].append(tag.get_text(strip=True))
        elif current_sub_section and tag.name == 'ul':  # List items within sub-sections
            for li in tag.find_all('li'):
                sections[current_main_section][current_sub_section].append(f"  + {li.get_text(strip=True)}")

    return sections

# Extract sections from the parsed markdown, excluding specified sections
sections = extract_sections(soup)

# Define the order of the sections for proper sorting
section_order = ['Fixes', 'Improvements']
sub_section_order = ['mikroSDK', 'CORE']

# Format the extracted sections
formatted_sections = []
for main_section in section_order:
    if main_section in sections:
        formatted_sections.append(f"+ {main_section}")
        for sub_section in sub_section_order:
            if sub_section in sections[main_section]:
                formatted_sections.append(f"  + {sub_section}")
                for line in sections[main_section][sub_section]:
                    formatted_sections.append(f"    {line}")

# Combine all formatted sections
formatted_message_content = "\n".join(formatted_sections)

# Get the current date and time
release_date = datetime.now().strftime("%a %b %d %H:%M:%S CEST %Y")

# Create the final formatted message
formatted_message = f"""
NECTO SDK/CORE Update for {release_date}:

Update notes:

{formatted_message_content}

> For more information on today's release, visit the following [README](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v{args.version.replace('mikroSDK-', '')}/changelog.md)
"""

# Print the formatted message
print(formatted_message)
