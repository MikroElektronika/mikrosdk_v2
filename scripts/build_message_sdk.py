from datetime import datetime
from bs4 import BeautifulSoup
import os
import markdown
import argparse

# Set up argument parsing to accept the markdown file path
parser = argparse.ArgumentParser(description="Process a markdown file to generate formatted release notes.")
parser.add_argument('version', type=str, help='Path to the markdown file')
args = parser.parse_args()

markdown_file_path = os.path.join(os.getcwd(), 'changelog', f'v{args.version.replace('mikroSDK-', '')}', 'changelog.md')

# Read the markdown content from the file path provided as a command-line argument
with open(markdown_file_path, 'r', encoding='utf-8') as file:
    markdown_content = file.read()

# Convert markdown to HTML and parse it with BeautifulSoup
html_content = markdown.markdown(markdown_content)
soup = BeautifulSoup(html_content, 'html.parser')

# Function to extract sections dynamically based on headers, excluding unwanted sections
def extract_sections(soup):
    sections = {}
    current_section = None
    for tag in soup.find_all(['h3', 'p', 'ul']):
        if tag.name == 'h3':
            current_section = tag.get_text(strip=True)
            # Exclude the "NEW HARDWARE" section
            if current_section.lower() == 'new hardware':
                current_section = None
            else:
                sections[current_section] = []
        elif current_section and tag.name in ['p', 'ul']:
            # Join text contents with spaces to avoid missing spaces between elements
            text_content = ' '.join(tag.stripped_strings)
            sections[current_section].append(text_content)
    return sections

# Extract sections from the parsed markdown, excluding specified sections
sections = extract_sections(soup)

# Format the extracted sections
formatted_sections = []
for section, content in sections.items():
    formatted_sections.append(f"+ {section}")
    for line in content:
        formatted_sections.append(f"  + {line}")

# Combine all formatted sections
formatted_message_content = "\n".join(formatted_sections)

# Get the current date and time
release_date = datetime.now().strftime("%a %b %d %H:%M:%S CEST %Y")

# Create the final formatted message
formatted_message = f"""
NECTO SDK Update for {release_date}:

Update notes:

{formatted_message_content}

> For more information on today's release, visit following [README](https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v{args.version.replace('mikroSDK-', '')}/changelog.md)
"""

# Print the formatted message
print(formatted_message)
