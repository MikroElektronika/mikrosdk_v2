import os, re
from packaging import version

import support as utility

## Get all currently present changelog versions
all_versions = sorted(
    [x for x in os.listdir(os.path.join(os.getcwd(), 'changelog'))],
    key=lambda x: version.parse(x), reverse=True
)

## Get file content first
with open(os.path.join(os.getcwd(),'CHANGELOG.md'), 'r') as main_changelog_file:
    main_changelog = main_changelog_file.readlines()
main_changelog_file.close()

## Remove lines that contain version links
main_changelog = [line for line in main_changelog if not re.match(r'\+\s\*\*\[v\d+\.\d+\.\d+\]', line)]

array_of_links = ['**VERSIONS:**\n']
for each_version in all_versions:
    ## Create new links
    array_of_links.append(f'+ **[{each_version}](./changelog/{each_version}/changelog.md)**')

## Then write the new main CHANGELOG.md content
with open(os.path.join(os.getcwd(),'CHANGELOG.md'), 'w') as main_changelog_file:
    main_changelog_file.writelines(''.join(main_changelog).replace('**VERSIONS:**', '\n'.join(array_of_links)))
main_changelog_file.close()

## And remove any occurrences of more than 1 sequential empty row
utility.filter_multiple_empty_rows(os.path.join(os.getcwd(),'CHANGELOG.md'))
