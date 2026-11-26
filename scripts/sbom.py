#!/usr/bin/env python3
"""Software bill of materials (SBOM) of mikroSDK, in CycloneDX 1.5 JSON.

    python3 scripts/sbom.py --version 2.21.0 [--output sbom.cdx.json]
    python3 scripts/sbom.py --check          (CI: the component list is complete and consistent)

Input: thirdparty/components.json (the third-party components, kept in step with
THIRD_PARTY_NOTICES.md) and, for lwIP, thirdparty/ethernet/lwip/UPSTREAM.json.

Each component gets the SHA-256 of its files as they are in this tree (run it on the
release tree, after scripts/keyword_replace.py, so the hashes match what is shipped):
sha256 over the sorted lines "<path relative to the repository>\\0<sha256 of the file>\\n".
The release workflow puts the SBOM into mikrosdk.7z and uploads it as a release asset.

Standard library only.
"""
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
import uuid
from datetime import datetime, timezone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
COMPONENTS = os.path.join(ROOT, 'thirdparty', 'components.json')
NOTICES = os.path.join(ROOT, 'THIRD_PARTY_NOTICES.md')
SUPPLIER = {'name': 'MikroElektronika d.o.o.', 'url': ['https://www.mikroe.com']}
REPO_URL = 'https://github.com/MikroElektronika/mikrosdk_v2'
SPDX_TOKEN = re.compile(r'^(LicenseRef-[A-Za-z0-9.-]+|[A-Za-z0-9.+-]+)$')


def files_of(rel):
    """Files under a path (a file or a folder), sorted, relative to ROOT."""
    full = os.path.join(ROOT, rel)
    if os.path.isfile(full):
        return [rel]
    out = []
    for root, dirs, names in os.walk(full):
        dirs.sort()
        for name in sorted(names):
            out.append(os.path.relpath(os.path.join(root, name), ROOT).replace(os.sep, '/'))
    return out


def file_sha256(rel):
    h = hashlib.sha256()
    with open(os.path.join(ROOT, rel), 'rb') as f:
        for chunk in iter(lambda: f.read(1 << 16), b''):
            h.update(chunk)
    return h.hexdigest()


def tree_hash(paths):
    lines = sorted(f'{rel}\0{file_sha256(rel)}\n' for p in paths for rel in files_of(p))
    return hashlib.sha256(''.join(lines).encode()).hexdigest(), len(lines)


def license_entry(expr):
    """CycloneDX licence: a single SPDX id / LicenseRef, or an expression."""
    if SPDX_TOKEN.match(expr):
        key = 'name' if expr.startswith('LicenseRef-') else 'id'
        return [{'license': {key: expr}}]
    return [{'expression': expr}]


def bom_ref(name):
    return re.sub(r'[^a-z0-9]+', '-', name.lower()).strip('-')


def component(c, parent_ref=''):
    ref = (parent_ref + '/' if parent_ref else '') + bom_ref(c['name'])
    digest, count = tree_hash(c['paths'])
    out = {
        'type': 'library',
        'bom-ref': ref,
        'name': c['name'],
        'version': c['version'],
        'copyright': c['copyright'],
        'licenses': license_entry(c['licenses']),
        'hashes': [{'alg': 'SHA-256', 'content': digest}],
        'properties': [{'name': 'mikroe:path', 'value': p} for p in c['paths']] +
                      [{'name': 'mikroe:file-count', 'value': str(count)},
                       {'name': 'mikroe:hash-method', 'value': 'sha256 of sorted "path\\0sha256(file)\\n" lines'}],
    }
    if c.get('purl'):
        out['purl'] = c['purl']
    if c.get('url'):
        out['externalReferences'] = [{'type': 'vcs' if 'github.com' in c['url'] else 'website', 'url': c['url']}]
    if c.get('note'):
        out['description'] = c['note']
    pedigree = {}
    if c.get('modified'):
        pedigree['notes'] = 'Modified by MikroElektronika: ' + c['modified']
    if c.get('upstream'):
        with open(os.path.join(ROOT, c['upstream'])) as f:
            up = json.load(f)
        changed = [x['path'] for x in up.get('files', []) if x.get('modified')]
        if up.get('commit') and up['commit'] != 'unknown':
            pedigree['commits'] = [{'uid': up['commit'], 'url': up.get('upstream', c.get('url', ''))}]
        out['properties'].append({'name': 'mikroe:upstream-tag', 'value': up.get('tag', '')})
        out['properties'] += [{'name': 'mikroe:modified-file', 'value': p} for p in changed]
    if pedigree:
        out['pedigree'] = pedigree
    if c.get('bundled'):
        out['components'] = [component(b, ref) for b in c['bundled']]
    return out


def all_components(data):
    for c in data['components']:
        yield c
        for b in c.get('bundled', []):
            yield b


def git_commit():
    try:
        return subprocess.run(['git', '-C', ROOT, 'rev-parse', 'HEAD'], capture_output=True, text=True,
                              check=True).stdout.strip()
    except (OSError, subprocess.CalledProcessError):
        return None


def build(version, data):
    top = {
        'type': 'framework',
        'bom-ref': 'mikrosdk',
        'name': 'mikroSDK',
        'version': version,
        'supplier': SUPPLIER,
        'licenses': [{'expression': 'LGPL-3.0-only OR LicenseRef-MIKROE-Commercial'}],
        'externalReferences': [{'type': 'vcs', 'url': REPO_URL},
                               {'type': 'license', 'url': 'https://www.mikroe.com/legal/software-license-agreement'}],
    }
    commit = git_commit()
    if commit:
        top['properties'] = [{'name': 'mikroe:git-commit', 'value': commit}]
    comps = [component(c) for c in data['components']]
    return {
        '$schema': 'http://cyclonedx.org/schema/bom-1.5.schema.json',
        'bomFormat': 'CycloneDX',
        'specVersion': '1.5',
        # Same release, same serial number: uuid5 of the product and version.
        'serialNumber': 'urn:uuid:' + str(uuid.uuid5(uuid.NAMESPACE_URL, f'{REPO_URL}#{version}')),
        'version': 1,
        'metadata': {
            'timestamp': datetime.now(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ'),
            'tools': {'components': [{'type': 'application', 'name': 'scripts/sbom.py', 'supplier': SUPPLIER}]},
            'component': top,
            'supplier': SUPPLIER,
        },
        'components': comps,
        'dependencies': [{'ref': 'mikrosdk', 'dependsOn': [c['bom-ref'] for c in comps]}] +
                        [{'ref': c['bom-ref'], 'dependsOn': [b['bom-ref'] for b in c.get('components', [])]}
                         for c in comps if c.get('components')],
    }


def check(data):
    """Problems with the component list; empty when it is complete and consistent."""
    problems = []
    with open(NOTICES, encoding='utf-8') as f:
        notices = f.read()
    covered = set()
    for c in all_components(data):
        for key in ('name', 'version', 'licenses', 'copyright', 'paths'):
            if not c.get(key):
                problems.append(f'{c.get("name", "?")}: no {key}')
        for p in c.get('paths', []):
            if not os.path.exists(os.path.join(ROOT, p)):
                problems.append(f'{c["name"]}: path {p} does not exist')
            covered.update(files_of(p))
        if c.get('name') and c['name'] not in notices:
            problems.append(f'{c["name"]}: not in THIRD_PARTY_NOTICES.md')
        for token in re.split(r'\s+(?:AND|OR|WITH)\s+|[()]', c.get('licenses', '')):
            if token.strip() and not SPDX_TOKEN.match(token.strip()):
                problems.append(f'{c["name"]}: "{token}" is not an SPDX licence id')
        if c.get('upstream') and not os.path.isfile(os.path.join(ROOT, c['upstream'])):
            problems.append(f'{c["name"]}: {c["upstream"]} does not exist')
    for p in data.get('mikroe_folders', []):
        if not os.path.exists(os.path.join(ROOT, p)):
            problems.append(f'mikroe_folders: {p} does not exist')
        covered.update(files_of(p))
    # Every file under thirdparty/ belongs to a component or to MIKROE (build files are MIKROE's).
    for rel in files_of('thirdparty'):
        if rel not in covered and os.path.basename(rel) != 'CMakeLists.txt':
            problems.append(f'{rel}: not covered by thirdparty/components.json')
    return problems


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--version', help='mikroSDK version, e.g. 2.21.0 (a "mikroSDK-" prefix is dropped)')
    ap.add_argument('--output', default=os.path.join(ROOT, 'sbom.cdx.json'))
    ap.add_argument('--check', action='store_true', help='only check thirdparty/components.json')
    args = ap.parse_args()

    with open(COMPONENTS, encoding='utf-8') as f:
        data = json.load(f)
    problems = check(data)
    if problems:
        print('thirdparty/components.json:', file=sys.stderr)
        for p in problems[:50]:
            print('  ' + p, file=sys.stderr)
        if len(problems) > 50:
            print(f'  ... and {len(problems) - 50} more', file=sys.stderr)
        sys.exit(1)
    if args.check:
        n = sum(1 for _ in all_components(data))
        print(f'thirdparty/components.json: {n} components, every file under thirdparty/ covered')
        return
    if not args.version:
        ap.error('--version is required (or --check)')
    version = args.version.replace('mikroSDK-', '')
    bom = build(version, data)
    with open(args.output, 'w', encoding='utf-8') as f:
        json.dump(bom, f, indent=2)
        f.write('\n')
    print(f'{os.path.relpath(args.output, ROOT)}: CycloneDX 1.5, mikroSDK {version}, '
          f'{sum(1 for _ in all_components(data))} components')


if __name__ == '__main__':
    main()
