## Impor section
import os, re, argparse
from os.path import dirname, abspath

## Root path
root_path = dirname(dirname(abspath(__file__)))

def is_commented_line(line):
    ''' Check if line is a comment '''
    stripped_line = line.lstrip()
    return stripped_line.startswith('//')

def replace_patterns_in_file(file_path, pattern_replacements):
    ''' Replace all strings that match the regexes '''
    with open(file_path, 'r', encoding='cp1252') as file:
        lines = file.readlines()

    ## Set new line to LF(linux system default)
    # with open(file_path, 'w', encoding='cp1252', newline='\n') as file:
    with open(file_path, 'wb') as file:
        for line in lines:
            if not is_commented_line(line):
                for pattern, replacement in pattern_replacements:
                    line = re.sub(pattern, replacement, line)
            file.write(bytes(line, "UTF-8"))

def replace_patterns_in_directory(directory, pattern_replacements, extensions=('.c', '.h')):
    ''' Iterate through all source and header files '''
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(extensions):
                file_path = os.path.join(root, file)
                replace_patterns_in_file(file_path, pattern_replacements)

def generate_pattern_replacements(target_word, replacement_word):
    ''' List of patterns and replacements '''
    return [
        (r' ' + re.escape(target_word) + r';', r' ' + replacement_word + r';'),
        (r'\[(?!_)' + re.escape(target_word) + '\]', r'[' + replacement_word + r']'),
        (r'\((?!_)' + re.escape(target_word) + '\)', r'(' + replacement_word + r')'),
        (r'\b' + re.escape(target_word) + '\)', replacement_word + r')'),
        ('\(' + re.escape(target_word) + r'\b', r'(' + replacement_word),
        (r'->' + re.escape(target_word), r'->' + replacement_word),
        (r'\.' + re.escape(target_word), r'.' + replacement_word),
        (r'\b' + re.escape(target_word) + r'\s*=', replacement_word + r' ='),
        (r'=\s*' + re.escape(target_word), r'= ' + replacement_word),
        (r',\s*(?!_)' + re.escape(target_word), r', ' + replacement_word),
        (r'\bint8_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int8_t ' + replacement_word),
        (r'\bint16_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int16_t ' + replacement_word),
        (r'\bint32_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int32_t ' + replacement_word),
        (r'\buint8_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint8_t ' + replacement_word),
        (r'\buint16_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint16_t ' + replacement_word),
        (r'\buint32_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint32_t ' + replacement_word),
        (r'__' + re.escape(target_word), replacement_word)
    ]

if __name__ == "__main__":
    ''' Main runner '''
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("keyword", help="Keyword to replace")
    parser.add_argument("keyword_new", help="Replace the keyword with this one")
    parser.add_argument("directory", help="Directory to replace in recursively")
    args = parser.parse_args()

    ## Replace args.keyword with args.keyword_new in all
    ## source and header files in args.directory list of directories
    replace_patterns_in_directory(
        os.path.join(root_path, args.directory),
        generate_pattern_replacements(args.keyword, args.keyword_new)
    )
