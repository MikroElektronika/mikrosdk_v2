import os, re
from packaging import version
from datetime import datetime

import support as utility

# Function to extract date from filename
def extract_date(filename):
    # Extract the date part (assuming format 'YYYY-MM-DD')
    date_str = filename.split('.')[0]
    # Convert to a datetime object for proper sorting
    return datetime.strptime(date_str, '%Y-%m-%d')

changelog_root = os.path.join(os.getcwd(), 'changelog')
all_changelog_dirs = os.listdir(changelog_root)

## Get all currently present changelog versions
all_versions = sorted(
    [x for x in all_changelog_dirs],
    key=lambda x: version.parse(x), reverse=True
)

## Get file content first
with open(os.path.join(os.getcwd(),'changelog.md'), 'r') as main_changelog_file:
    main_changelog = main_changelog_file.readlines()
main_changelog_file.close()

## Remove lines that contain version links
main_changelog = [line for line in main_changelog if not re.match(r'\+\s\*\*\[v\d+\.\d+\.\d+\]', line)]

array_of_links = ['**VERSIONS:**\n']
for each_version in all_versions:
    ## Create new links
    array_of_links.append(f'+ **[{each_version}](./changelog/{each_version}/changelog.md)**')

## Then write the new main changelog.md content
with open(os.path.join(os.getcwd(),'changelog.md'), 'w') as main_changelog_file:
    main_changelog_file.writelines(''.join(main_changelog).replace('**VERSIONS:**', '\n'.join(array_of_links)))
main_changelog_file.close()

## And remove any occurrences of more than 1 sequential empty row
utility.filter_multiple_empty_rows(os.path.join(os.getcwd(),'changelog.md'))

## Update CHANGELOG files with specific date releases
array_of_links = ['Support added for following hardware:\n']
for each_version in all_versions:
    ## Get file content first
    with open(os.path.join(changelog_root, each_version, 'changelog.md'), 'r') as sub_changelog_file:
        sub_changelog = sub_changelog_file.readlines()
    sub_changelog_file.close()

    ## Remove lines that contain links
    sub_changelog = [line for line in sub_changelog if not re.match(r'^\+ \*\*\[\d{4}-\d{2}-\d{2}\]\(\./new_hw/\d{4}-\d{2}-\d{2}\.md\)\*\*$', line)]

    ## Get file list
    current_files = os.listdir(os.path.join(changelog_root, each_version))
    if len(current_files) > 1:
        print('Updated changelog file at: %s' % os.path.join(changelog_root, each_version))
        if 'new_hw' in current_files:
            ## Sort the files based on date (newest go to top of the file)
            all_sub_files = sorted(os.listdir(os.path.join(changelog_root, each_version, 'new_hw')), key=extract_date)
            for each_sub_file in all_sub_files:
                ## Create new links
                array_of_links.append(f'+ **[{each_sub_file.split('.')[0]}](./new_hw/{each_sub_file})**')

        ## Then write the new sub changelog.md content
        with open(os.path.join(changelog_root, each_version, 'changelog.md'), 'w') as sub_changelog_file:
            sub_changelog_file.writelines(''.join(sub_changelog).replace('Support added for following hardware:', '\n'.join(array_of_links)))
        sub_changelog_file.close()

        ## And remove any occurrences of more than 1 sequential empty row
        utility.filter_multiple_empty_rows(os.path.join(changelog_root, each_version, 'changelog.md'))
