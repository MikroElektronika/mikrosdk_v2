## Impor section
from __future__ import annotations

import os, re, argparse
from os.path import dirname, abspath

from pathlib import Path
from typing import Iterable, Tuple

## Root path

root_path = dirname(dirname(abspath(__file__)))

## ETHERNET

def is_commented_line(line):
    ''' Check if line is a comment '''
    stripped_line = line.lstrip()
    return stripped_line.startswith('//')

def replace_patterns_in_file(file_path, pattern_replacements, set_encoding):
    ''' Replace all strings that match the regexes '''
    with open(file_path, 'r', encoding=set_encoding) as file:
        lines = file.readlines()

    ## Set new line to LF(linux system default)
    with open(file_path, 'wb') as file:
        for line in lines:
            if not is_commented_line(line):
                for pattern, replacement in pattern_replacements:
                    line = re.sub(pattern, replacement, line)
            file.write(bytes(line, set_encoding))

def replace_patterns_in_directory(directory, pattern_replacements, set_encoding, extensions=('.c', '.h')):
    ''' Iterate through all source and header files '''
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(extensions):
                file_path = os.path.join(root, file)
                replace_patterns_in_file(file_path, pattern_replacements, set_encoding)

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
        (r'&&\s*' + re.escape(target_word), r'&& ' + replacement_word),
        (r'\|\|\s*' + re.escape(target_word), r'\|\| ' + replacement_word),
        (r',\s*(?!_)' + re.escape(target_word), r', ' + replacement_word),
        (r'\bint8_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int8_t ' + replacement_word),
        (r'\bint16_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int16_t ' + replacement_word),
        (r'\bint32_t\s+(?!_)' + re.escape(target_word) + r'\b', r'int32_t ' + replacement_word),
        (r'\buint8_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint8_t ' + replacement_word),
        (r'\buint16_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint16_t ' + replacement_word),
        (r'\buint32_t\s+(?!_)' + re.escape(target_word) + r'\b', r'uint32_t ' + replacement_word),
        (r'__' + re.escape(target_word), replacement_word)
    ]

## LVGL

def _is_ident_start(ch: str) -> bool:
    return ch.isalpha() or ch == "_"

def _is_ident_part(ch: str) -> bool:
    return ch.isalnum() or ch == "_"

def replace_c_identifier_outside_comments_and_strings(
    text: str,
    *,
    target: str = "code",
    replacement: str,
    exclude_prefixes: Tuple[str, ...] = ("@", "\\"),
) -> Tuple[str, int]:
    """
    Replace `target` identifier token with `replacement` ONLY outside comments and string/char literals.
    Also skips replacement when the identifier is immediately preceded by any char in `exclude_prefixes`
    (e.g. '@code' or '\\code').
    Returns (updated_text, replacements_count).
    """

    NORMAL, LINE_COMMENT, BLOCK_COMMENT, STRING, CHAR = range(5)

    n = len(text)
    i = 0
    state = NORMAL
    out: List[str] = []
    count = 0

    while i < n:
        ch = text[i]

        if state == NORMAL:
            # Enter comments
            if ch == "/" and i + 1 < n and text[i + 1] == "/":
                out.append("//")
                i += 2
                state = LINE_COMMENT
                continue
            if ch == "/" and i + 1 < n and text[i + 1] == "*":
                out.append("/*")
                i += 2
                state = BLOCK_COMMENT
                continue

            # Enter string/char literals
            if ch == '"':
                out.append(ch)
                i += 1
                state = STRING
                continue
            if ch == "'":
                out.append(ch)
                i += 1
                state = CHAR
                continue

            # Identifier token
            if _is_ident_start(ch):
                j = i + 1
                while j < n and _is_ident_part(text[j]):
                    j += 1

                token = text[i:j]

                # Token boundary is guaranteed by scanning.
                # Check doxygen-ish prefixes like '@code' or '\code'
                prev_ch = text[i - 1] if i > 0 else ""
                if token == target and prev_ch not in exclude_prefixes:
                    out.append(replacement)
                    count += 1
                else:
                    out.append(token)

                i = j
                continue

            # Default: copy character
            out.append(ch)
            i += 1
            continue

        elif state == LINE_COMMENT:
            out.append(ch)
            i += 1
            if ch == "\n":
                state = NORMAL
            continue

        elif state == BLOCK_COMMENT:
            if ch == "*" and i + 1 < n and text[i + 1] == "/":
                out.append("*/")
                i += 2
                state = NORMAL
            else:
                out.append(ch)
                i += 1
            continue

        elif state == STRING:
            out.append(ch)
            i += 1
            if ch == "\\" and i < n:
                # escape next character inside string
                out.append(text[i])
                i += 1
                continue
            if ch == '"':
                state = NORMAL
            continue

        elif state == CHAR:
            out.append(ch)
            i += 1
            if ch == "\\" and i < n:
                # escape next character inside char literal
                out.append(text[i])
                i += 1
                continue
            if ch == "'":
                state = NORMAL
            continue

    return "".join(out), count

def replace_code_identifier_in_project(
    root: str | Path,
    *,
    replacement: str,
    target: str = "code",
    dry_run: bool = True,
) -> List[Path]:
    """
    Recursively replaces identifier `target` -> `replacement` in .c/.h files under `root`,
    but ONLY outside comments and string/char literals.

    Uses UTF-8 with surrogateescape so we can round-trip odd bytes without corrupting files.

    Returns list of modified files (or would-be modified if dry_run).
    """
    root_path = Path(root)
    modified: List[Path] = []

    for path in root_path.rglob("*"):
        if not path.is_file():
            continue
        if path.suffix.lower() not in (".c", ".h"):
            continue

        original = path.read_text(encoding="utf-8", errors="surrogateescape")
        updated, n = replace_c_identifier_outside_comments_and_strings(
            original,
            target=target,
            replacement=replacement,
            exclude_prefixes=("@", "\\"),
        )

        if n == 0:
            continue

        modified.append(path)
        if not dry_run:
            path.write_text(updated, encoding="utf-8", errors="surrogateescape")

    return modified

if __name__ == "__main__":
    ''' Main runner '''
    parser = argparse.ArgumentParser(description="Upload directories as release assets.")
    parser.add_argument("keyword", help="Keyword to replace")
    parser.add_argument("keyword_new", help="Replace the keyword with this one")
    parser.add_argument("directory", help="Directory to replace in recursively")
    parser.add_argument("encoding", help="Directory to replace in recursively")
    args = parser.parse_args()

    ## Replace args.keyword with args.keyword_new in all
    ## source and header files in args.directory list of directories
    ## TODO - Check if Ethernet can work with new 'replace_code_identifier_in_project'
    ## If so, create a PR with this change and remove previous 'replace_patterns_in_directory'
    ## and supporting functions
    if 'ethernet' in args.directory:
        replace_patterns_in_directory(
            os.path.join(root_path, args.directory),
            generate_pattern_replacements(args.keyword, args.keyword_new),
            args.encoding
        )
    elif 'lvgl' in args.directory:
        changed = replace_code_identifier_in_project(
            root=os.path.join(root_path, args.directory),
            replacement="_code",
            dry_run=False,
        )
