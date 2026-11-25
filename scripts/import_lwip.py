#!/usr/bin/env python3
"""Import lwIP into thirdparty/ethernet/lwip.

    python3 scripts/import_lwip.py <lwip checkout> [--dest thirdparty/ethernet/lwip]

<lwip checkout> is a clean checkout of a release tag of https://github.com/lwip-tcpip/lwip
(e.g. git clone --depth 1 --branch STABLE-2_2_1_RELEASE ...). The script

  - copies only what mikroSDK builds: the core (IPv4, IPv6), the Ethernet netif and the
    headers, plus COPYING,
  - renames the identifier `code` to `_code` outside comments and strings, because every
    mikroSDK library is compiled with `code=` (an empty macro, `code` is a reserved word in
    the mikroC compilers) - lwIP uses `code` as a field name (ICMP headers),
  - puts a notice at the top of every file it changes,
  - writes UPSTREAM.json: tag, commit, every imported file with the SHA-256 of the upstream
    file and whether it was changed (for updates, reviews and the SBOM).

Files under <dest>/src are replaced; the MIKROE files next to it (port/, CMakeLists.txt,
README.md, lwip_sources.cmake) are left alone.
"""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys

# What mikroSDK builds. Paths are relative to the lwIP checkout.
IMPORT_DIRS = {
    'src/core': ('.c',),             # not recursive, see below
    'src/core/ipv4': ('.c',),
    'src/core/ipv6': ('.c',),
    'src/include': ('.h',),          # recursive
}
IMPORT_FILES = ['src/netif/ethernet.c', 'COPYING']
RECURSIVE = {'src/include'}

TARGET, REPLACEMENT = 'code', '_code'
NOTICE = ('/* Modified by MikroElektronika d.o.o. (MIKROE) on import: identifier `code` renamed to\n'
          ' * `_code` (reserved word in the mikroC compilers) by scripts/import_lwip.py. */\n')


def rename_identifier(text):
    """Replace the identifier TARGET outside comments, strings and char literals."""
    out, i, n, count = [], 0, len(text), 0
    state = 'code'  # code | line | block | str | chr
    while i < n:
        ch = text[i]
        nxt = text[i + 1] if i + 1 < n else ''
        if state == 'code':
            if ch == '/' and nxt == '/':
                state = 'line'; out.append('//'); i += 2; continue
            if ch == '/' and nxt == '*':
                state = 'block'; out.append('/*'); i += 2; continue
            if ch == '"':
                state = 'str'; out.append(ch); i += 1; continue
            if ch == "'":
                state = 'chr'; out.append(ch); i += 1; continue
            if ch.isalpha() or ch == '_':
                j = i + 1
                while j < n and (text[j].isalnum() or text[j] == '_'):
                    j += 1
                token = text[i:j]
                if token == TARGET:
                    out.append(REPLACEMENT); count += 1
                else:
                    out.append(token)
                i = j
                continue
            out.append(ch); i += 1; continue
        if state == 'line':
            out.append(ch); i += 1
            if ch == '\n':
                state = 'code'
            continue
        if state == 'block':
            if ch == '*' and nxt == '/':
                out.append('*/'); i += 2; state = 'code'
            else:
                out.append(ch); i += 1
            continue
        # string or char literal
        out.append(ch); i += 1
        if ch == '\\' and i < n:
            out.append(text[i]); i += 1
            continue
        if (state == 'str' and ch == '"') or (state == 'chr' and ch == "'"):
            state = 'code'
    return ''.join(out), count


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def collect(src_root):
    files = []
    for d, exts in IMPORT_DIRS.items():
        base = os.path.join(src_root, d)
        if d in RECURSIVE:
            for root, dirs, names in os.walk(base):
                dirs.sort()
                for name in sorted(names):
                    if name.endswith(exts):
                        files.append(os.path.relpath(os.path.join(root, name), src_root))
        else:
            for name in sorted(os.listdir(base)):
                if name.endswith(exts) and os.path.isfile(os.path.join(base, name)):
                    files.append(os.path.join(d, name))
    files += IMPORT_FILES
    return sorted(files)


def git(src_root, *args):
    try:
        return subprocess.run(['git', '-C', src_root, *args], capture_output=True, text=True,
                              check=True).stdout.strip()
    except (OSError, subprocess.CalledProcessError):
        return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('lwip', help='checkout of an lwIP release tag')
    ap.add_argument('--dest', default=os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                                                   'thirdparty', 'ethernet', 'lwip'))
    args = ap.parse_args()

    if not os.path.isfile(os.path.join(args.lwip, 'src', 'include', 'lwip', 'init.h')):
        sys.exit(f'{args.lwip} does not look like an lwIP checkout')

    tag = git(args.lwip, 'describe', '--tags', '--exact-match') or 'unknown'
    commit = git(args.lwip, 'rev-parse', 'HEAD') or 'unknown'

    src_dest = os.path.join(args.dest, 'src')
    if os.path.isdir(src_dest):
        shutil.rmtree(src_dest)

    manifest = {'upstream': 'https://github.com/lwip-tcpip/lwip', 'tag': tag, 'commit': commit,
                'license': 'BSD-3-Clause', 'files': []}
    changed_total = 0
    for rel in collect(args.lwip):
        with open(os.path.join(args.lwip, rel), 'rb') as f:
            raw = f.read()
        dest_rel = rel if rel.startswith('src/') else rel  # COPYING stays at the top
        out_path = os.path.join(args.dest, dest_rel)
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
        modified = False
        data = raw
        if rel.endswith(('.c', '.h')):
            text = raw.decode('utf-8', errors='surrogateescape')
            new, count = rename_identifier(text)
            if count:
                modified = True
                changed_total += 1
                data = (NOTICE + new).encode('utf-8', errors='surrogateescape')
        with open(out_path, 'wb') as f:
            f.write(data)
        manifest['files'].append({'path': dest_rel, 'upstream_sha256': sha256(raw), 'modified': modified})

    with open(os.path.join(args.dest, 'UPSTREAM.json'), 'w', encoding='utf-8') as f:
        json.dump(manifest, f, indent=2)
        f.write('\n')
    print(f'lwIP {tag} ({commit[:12]}): {len(manifest["files"])} files imported into {args.dest}, '
          f'{changed_total} changed (`{TARGET}` -> `{REPLACEMENT}`)')


if __name__ == '__main__':
    main()
