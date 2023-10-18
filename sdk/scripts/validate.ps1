[CmdletBinding()]
param (
    [Parameter(Mandatory = $true)]
    [String]$sdkVersion
)

Write-Host "Current Dir = $pwd"

$rootDirValidate = Get-ChildItem -Path ./ -Exclude .git, .gitignore, .gitlab-ci.yml
$Global:rootListErr = @()
$Global:versionListErr = @()

function validateDirsRoot() {
    $localList = @()
    $rootList = @(
        'api',
        'bsp',
        'cmake',
        'components',
        'drv',
        'hal',
        'middleware',
        'platform',
        'scripts',
        'targets',
        'tests',
        'AUTHORS.md',
        'CHANGELOG.md',
        'CMakeLists.txt',
        'CODE_OF_CONDUCT.md',
        'CONTRIBUTING.md',
        'LICENSE',
        'manifest.json',
        'README.md',
        'REQUIREMENTS.md',
        'SUPPORTED_CHIP_LIST.md'
    )

    foreach ($element in $rootDirValidate) {
        $localList += $element.PSChildName
    }

    foreach ($element in $rootList) {
        if ($localList -notcontains $element) {
            $Global:rootListErr += "$element is missing from root."
        }
    }
}

function checkVersion() {
    if ($(Get-Content manifest.json | ConvertFrom-Json).'sdk-version' -ne $sdkVersion) {
        $Global:versionListErr += "Version not changed in manifest.json file."
    }
    if ($(Get-Content manifest.json | ConvertFrom-Json).'sdk-version' -ne $sdkVersion) {
        $Global:versionListErr += "Version not changed in manifest.json file."
    }
}

function checkVersionMacro() {
    $versions = $sdkVersion.Split('.')
    $versionMajor = '#define mikroSDK_MAJOR_VERSION ' + $versions[0]
    $versionMinor = '#define mikroSDK_MINOR_VERSION ' + $versions[1]
    $versionPatch = '#define mikroSDK_PATCH_VERSION ' + $versions[2]
    $versions = @()
    $versions += $versionMajor
    $versions += $versionMinor
    $versions += $versionPatch

    foreach ( $checkString in $versions ) {
        if ( !(Select-String -Path ./platform/mikrosdk_version/include/mikrosdk_version.h -Pattern $checkString) ) {
            $Global:versionListErr += "$checkString not found in mikrosdk_version.h file."
        }
    }

    if ( !(Select-String -Path ./CMakeLists.txt -Pattern "    project\(MikroSDK VERSION $sdkVersion LANGUAGES MikroC\)") ) {
        $Global:versionListErr += "Project version not updated. Check main CMakeLists.txt file."
    }

    if ( !(Select-String -Path ./CMakeLists.txt -Pattern "    project\(MikroSDK VERSION $sdkVersion LANGUAGES C ASM\)") ) {
        $Global:versionListErr += "Project version not updated. Check main CMakeLists.txt file."
    }

    $versions = $sdkVersion.Split('.')
    $testVersion = $versions[0] + $versions[1] + $versions[2]
    if ( !(Select-String -Path ./CHANGELOG.md -Pattern "\+ \*\*\[v$sdkVersion\]\(#v$testVersion\)\*\*") ) {
        $Global:versionListErr += "SDK version not added to CHANGELOG file."
    }

    if ( !(Select-String -Path ./REQUIREMENTS.md -Pattern "\* \*\*v$sdkVersion\*\*") ) {
        $Global:versionListErr += "SDK version not added to REQUIREMENTS file."
    }
}

function checkForErrors() {
    $errCheckValue = 0

    if ($Global:rootListErr.Count) {
        if ( !(Test-Path -Path ./scripts/logOut ) ) {
            New-Item -Path ./scripts/logOut -ItemType Directory -Force
        }
        Set-Content -Path scripts/logOut/rootListErrors.log -Value $Global:rootListErr -Force
        $errCheckValue++
    }

    if ($Global:versionListErr.Count) {
        if ( !(Test-Path -Path ./scripts/logOut ) ) {
            New-Item -Path ./scripts/logOut -ItemType Directory -Force
        }
        Set-Content -Path scripts/logOut/versionListErrors.log -Value $Global:versionListErr -Force
        $errCheckValue++
    }

    return $errCheckValue
}

validateDirsRoot
checkVersion
checkVersionMacro

if (checkForErrors -ne 0) {
    Write-Host "Validation Failed!" -ForegroundColor Red
    Exit 1
}
else {
    Write-Host "Validation Passed!" -ForegroundColor Green
    Exit 0
}
