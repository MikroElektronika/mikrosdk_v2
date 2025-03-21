import os
import sys
import subprocess

def get_repo_root():
    abs_directory = os.path.abspath('.')  # Ensure absolute path
    if not os.path.isdir(abs_directory):
        print(f"Error: {abs_directory} is not a valid directory.")
        return None

    try:
        result = subprocess.run(['git', 'rev-parse', '--show-toplevel'], cwd=abs_directory, capture_output=True, text=True, shell=True)
        if result.returncode == 0:
            return result.stdout.strip()
        else:
            print("Error: Not inside a Git repository.")
            return None
    except Exception as e:
        print(f"Error running Git command: {e}")
        return None

def find_and_replace(batch_size=1000):
    old_text = ("** THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
                "** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED\n"
                "** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n")

    new_text = ("** THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
                "** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES\n"
                "** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n")

    valid_extensions = {'.c', '.h', '.txt'}
    valid_keywords = {'cmake', 'CMake'}

    modified_files = []
    repo_root = get_repo_root()
    if repo_root is None:
        print("Exiting: Not a Git repository.")
        sys.exit(1)

    last_processed_file = get_last_processed_file(repo_root)
    start_processing = last_processed_file is None

    for root, _, files in os.walk(repo_root):
        for file in files:
            if not (file.endswith(tuple(valid_extensions)) or any(keyword in file for keyword in valid_keywords)):
                continue

            file_path = os.path.join(root, file)

            if not start_processing:
                if file_path == last_processed_file:
                    start_processing = True
                continue

            if process_file(file_path, old_text, new_text):
                modified_files.append(file_path)

            if len(modified_files) >= batch_size:
                commit_changes(repo_root, modified_files)
                save_last_processed_file(repo_root, file_path)
                modified_files = []

    if modified_files:
        commit_changes(repo_root, modified_files)
        save_last_processed_file(repo_root, "")

def process_file(file_path, old_text, new_text):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()

        if old_text in content:
            content = content.replace(old_text, new_text)
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(content)
            return True
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
    return False

def commit_changes(repo_root, modified_files):
    try:
        subprocess.run(['git', 'add', '*'], cwd=repo_root, check=True)
        subprocess.run(['git', 'commit', '-m', f'Updated {len(modified_files)} files with correct license text'], cwd=repo_root, check=True)
        subprocess.run(['git', 'push'], cwd=repo_root, check=True)
        print(f"Committed and pushed {len(modified_files)} files.")
    except subprocess.CalledProcessError as e:
        print(f"Git error: {e}")

def get_last_processed_file(repo_root):
    record_file = os.path.join(repo_root, '.last_processed_file')
    if os.path.exists(record_file):
        with open(record_file, 'r', encoding='utf-8') as f:
            return f.read().strip() or None
    return None

def save_last_processed_file(repo_root, file_path):
    record_file = os.path.join(repo_root, '.last_processed_file')
    with open(record_file, 'w', encoding='utf-8') as f:
        f.write(file_path)

if __name__ == "__main__":
    find_and_replace()
