import os
import shutil
import subprocess
import urllib.request

# Runs a shell command and prints the output.
def run_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    for line in process.stdout:
        print(line.strip())
    process.wait()
    return process.returncode

def main():
    original_working_dir = os.getcwd()
    print(f"Original working directory: {original_working_dir}")

    os.chdir('/home/runner/')
    print(f"Script executed from: {os.getcwd()}")
    print("Current folder contents")
    for file in os.listdir(os.getcwd()):
        print(file)

    url = os.getenv('NECTO_DOWNLOAD_URL')
    if 'live' in url:
        print("Step 1: Downloading Live NECTOStudio version")
    else:
        print("Step 1: Downloading Development NECTOStudio version")
    urllib.request.urlretrieve(url, "NECTOInstaller.zip")

    print("Step 2: Extract installer")
    run_command("7za x NECTOInstaller.zip")

    print("Step 3: Install NECTO")
    run_command("./NECTOInstaller installer --install-packages necto_installer necto_application database /home/runner/MikroElektronika /home/runner/.MIKROE/NECTOStudio7")

    print("Step 4: Move installer to MIKROE if it's generated in root")
    if os.path.isfile("/home/runner/MikroElektronika/installer_tmp"):
        shutil.move("/home/runner/MikroElektronika/installer_tmp", "/home/runner/MikroElektronika/installer")

    print("Step 5: Move instance_uuid.txt to MIKROE if it's generated in root")
    if os.path.isfile("/home/runner/instance_uuid.txt"):
        shutil.move("/home/runner/instance_uuid.txt", "/home/runner/MikroElektronika/instance_uuid.txt")

    print("Step 6: Read hash from instance_uuid.txt")
    with open("/home/runner/MikroElektronika/instance_uuid.txt", "r") as f:
        line = f.readline().strip()

    print("Step 7: Copy NECTOStudio.conf to current directory")
    shutil.copy("/home/runner/.config/MikroElektronika/NECTOStudio.conf", "/home/runner/NECTOStudio.conf")

    print("Step 8: Add the read hash to it")
    with open("/home/runner/NECTOStudio.conf", "r+") as f:
        content = f.read()
        f.seek(0, 0)
        f.write(f"[{line}]\n" + content)

    print("Step 9: Copy it back to .config/MikroElektronika")
    shutil.copy("/home/runner/NECTOStudio.conf", "/home/runner/.config/MikroElektronika/NECTOStudio.conf")

    print("Step 10: Move installed_packages.json to MIKROE if it's generated in root")
    if os.path.isfile("/home/runner/installed_packages.json"):
        shutil.move("/home/runner/installed_packages.json", "/home/runner/MikroElektronika/installed_packages.json")

    print("Step 11: Remove NECTOInstaller.zip")
    os.remove("/home/runner/NECTOInstaller.zip")

    print("Step 12: Remove NECTOInstaller")
    os.remove("/home/runner/NECTOInstaller")

    print("Step 13: Remove NECTOStudio.conf")
    os.remove("/home/runner/NECTOStudio.conf")

    print("Current folder contents")
    for file in os.listdir(os.getcwd()):
        print(file)

    os.chdir(original_working_dir)
    print(f"Returned to original working directory: {os.getcwd()}")

if __name__ == "__main__":
    main()
