# BEGIN
[CmdletBinding()]
param (
    [Parameter(Mandatory=$false)]
    [Switch]$silent,
    [Parameter(Mandatory=$false)]
    [String]$coreSelect = $false,
    [Parameter(Mandatory=$false)]
    [String]$chipRegex = $false,
    [Switch]$customParams = $false,
    [Switch]$examples = $false,
    [Switch]$remove = $false
)

. '.\utility.ps1'

if ( $customParams ) {
    $customParamsContent = Get-Content customParams.json | ConvertFrom-Json
    $silent = $customParamsContent.silent
    $Env:CORE = $customParamsContent.coreSelect
    $chipRegex = $customParamsContent.chipRegex
    $examples = $customParamsContent.examples
    $remove = $customParamsContent.remove
}

## --------------------------------------
## Uncomment desired core for local run
# $Env:CORE = "STM32_M0"
# $Env:CORE = "STM32_M3"
# $Env:CORE = "STM32_M4"
# $Env:CORE = "STM32_M7"
# $Env:CORE = "PIC18"
# $Env:CORE = "PIC32_MIPS32"
# $Env:CORE = "PIC32_MICROAPTIV_FP"
# $Env:CORE = "PIC32_MICROAPTIV"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "NXP_M4DSP"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "NXP_M4EF"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "NXP_M7"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "TIVA_M4EF"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $ENV:CORE = "DSPIC"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "AVR_GT64K"  ## No chips with this core are supported in mikroSDK2.0 at this time
# $Env:CORE = "AVR_LTE64K"  ## No chips with this core are supported in mikroSDK2.0 at this time
## --------------------------------------

if ( $silent ) {
    $Global:silent = $true
} else {
    $Global:silent = $false
}

if ( $coreSelect -ne $false ) {
    $Env:CORE = $coreSelect
}

if ( Utils-SetValues($Env:CORE) ) {
    Exit -1
}

# -----------------------------------------------------------------------------
# Common configuration.
$Global:cnt = 0
$freq = '1'
$board = "GENERIC_BOARD"
$toolchain = $Global:selectedToolchain
$flags = $Global:selectedFlags
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Find NECTO Studio def files.
$defsPath = Utils-JoinPath -Path $Env:MIKROE_STUDIO_ROOT `
                           -ChildPath "compilers/$Global:architecture/mikroC/Defs"
if ( $chipRegex -ne $false ) {
    $defFiles = Get-ChildItem -Path $defsPath | `
                Where-Object -FilterScript { $_.Name -match "$chipRegex.json" }
} else {
    $defFiles = Get-ChildItem -Path $defsPath -Filter *.json
}
$Global:chipBuildCount = $defFiles.Count
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Find mikroSDK mcu_definitions.h files.
$mcuDefinitions = Get-ChildItem -Path $(Join-Path -Path $PSScriptRoot `
                                -ChildPath $Global:mcuDefPath) -Name
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Set output paths.
$srcDir = Utils-JoinPath -Path $PSScriptRoot -ChildPath '..'
$rootOutDir = Utils-JoinPath -Path $srcDir -ChildPath ../build/$Global:buildOut
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Set log paths.
$buildLogFile = "$rootOutDir/build.log"
$errorLogFile = "$rootOutDir/errors.log"
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Save run date-time.
$dateStamp = Get-Date -uformat "%Y-%m-%d@%H-%M-%S"
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Remove any previous generated files.
if(Test-Path -Path $rootOutDir){
    Remove-Item -Path $rootOutDir -Recurse -Force
}
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
foreach( $defFile in $defFiles ) {
    ## Get json content from def file.
    $def = Get-JsonObjFromFile -File $defFile.FullName

    $packageCount = 0
    if ( $def.packages ) {
        $packageCount = $def.packages.Length
    }

    for ( $counter = 0; $counter -le $packageCount; $counter++ ) {

        if ( $packageCount -eq 0 ) {
            $mcuName = $def.mcu
            $package = ""
        } else {
            $mcuName = $def.mcu + $def.packages[$counter]
            $package = $def.packages[$counter]
        }

        if ( $mcuDefinitions -contains $mcuName ) {

            if ( $def.core -eq $selectedCore ) {

                $outDir = Utils-JoinPath -Path  $rootOutDir -ChildPath $mcuName

                $configuration = @()
                if ( $packageCount -ne 0 ) {
                    $configuration += Utils-Config `
                    -Name "MSDK_PACKAGE_NAME" -Value $def.packages[$counter]
                }
                if ( $def.core -eq "M4DSP" ) {
                    $configuration += Utils-Config `
                    -Name "MEMAKE_DELAY_SOURCE_PATH" -Value $(Join-Path -Path $Env:MIKROE_STUDIO_ROOT `
                                                                        -ChildPath "compilers/ARM/mikroC/delays/m4ef/__lib_delays.c")
                }
                $configuration += Utils-Config `
                    -Name "MSDK_BUILD_COMPONENTS" -Value "False"
                $configuration += Utils-Config `
                    -Name "MSDK_BUILD_HAL_RECURSION" -Value "True"
                $configuration += Utils-Config `
                    -Name "MSDK_HAL_LOW_LEVEL_TARGET" -Value "mikroe"
                $configuration += Utils-Config `
                    -Name "MEMAKE_SDK_TYPE" -Value "normal"
                if ( $examples ) {
                    $configuration += Utils-Config `
                        -Name "MSDK_TEST_EXAMPLES" -Value "true"
                }

                Utils-Generate-Cfg-File -mcu $mcuName -output $rootOutDir -package $package
                $configuration += Utils-Config `
                    -Name "MEMAKE_LINKER_CFG" -Value "$rootOutDir/$mcuName/CFG_DIR/$mcuName.json"

                ## Configure project.
                $memakeOutput = Memake-Configure -SrcDir $srcDir `
                                                 -OutDir $outDir `
                                                 -Mcu $def.mcu `
                                                 -Board $board `
                                                 -Flags $flags `
                                                 -Core $def.core `
                                                 -Freq $freq `
                                                 -Toolchain $toolchain `
                                                 -Configuration $configuration
                Utils-CheckForErrors -mcu $mcuName `
                                     -buildLogFile $buildLogFile `
                                     -errorLogFile $errorLogFile `
                                     -outDirPath $outDir

                ## Build SDK
                $memakeOutput = Memake-BuildAll -OutDir $outDir
                Utils-CheckForErrors -mcu $mcuName `
                                     -buildLogFile $buildLogFile `
                                     -errorLogFile $errorLogFile `
                                     -outDirPath $outDir `
                                     -build

                ## Log output
                Utils-RecursionLog -Mcu $mcuName -LogFile $buildLogFile
                if ( $remove ) {
                    Remove-Item -Path $outDir -Recurse
                }

            }

        }
    }

}
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
Write-Host "Recursion build finished." -ForegroundColor Blue

if( $Global:cnt -eq 0 ){
    Write-Host "No Errors" -ForegroundColor Green
    Write-Host $dateStamp -ForegroundColor Green
}else {
    Write-Host "Building finished with errors." -ForegroundColor Red
    Write-Host $dateStamp -ForegroundColor Green
    Exit -1
}

if(Test-Path -Path $buildLogFile){
    "Recursion build finished." | Out-File -FilePath $buildLogFile -Append
}
# -----------------------------------------------------------------------------
