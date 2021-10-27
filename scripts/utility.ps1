Function Terminate-On-Exitcode($message) {
    if (($null -ne $Global:LASTEXITCODE) -and ($Global:LASTEXITCODE -ne 0)) {
        Write-Host $message -ForegroundColor Red
        Write-Host "LASTEXITCODE is $Global:LASTEXITCODE" -ForegroundColor Red
        Exit $LASTEXITCODE
    }
    if ($Global:Error.Count -ne 0){
        Write-Host $message -ForegroundColor Red
        Write-Host "Error var: $Global:Error" -ForegroundColor Red
        Exit -1
    }

    Write-Host "LASTEXITCODE is $Global:LASTEXITCODE" -ForegroundColor Blue
}

function ErrorHandler () {
    Param(
        [switch]$noExitOnFault
    )

    if ($LASTEXITCODE -ne 0) {
        Write-Host "Error occured."
        Write-Host "Last exit code is $LASTEXITCODE."
        if (!$noExitOnFault) {
            exit 1
        }
    }
}

Function Write-Success($message) {
    Write-Host $message -ForegroundColor Green
}

Function HexToCecBin-Convert($file) {
    $outPath = join-path ([system.io.fileinfo]$File).DirectoryName ([system.io.fileinfo]$file).BaseName
    $outPath += ".bin"
    Write-Host $outPath
    & $HexToCecBin "-device" "CEC1302" "-in" "$file" "-out" "$outPath" "-flashSize" "128KB"
    Terminate-On-Exitcode "Failed to convert .hex: $file to .bin"
}

Function Utils-JoinPath {
    param(
        [parameter(Mandatory = $true)]$Path,
        [parameter(Mandatory = $true)]$ChildPath
    )
    return [System.IO.Path]::GetFullPath($(Join-Path -Path $Path -ChildPath $ChildPath))
}

$HexToCecBin = "$Env:MIKROE_STUDIO_ROOT/HexToCecBin"
$Memake = "$Env:MIKROE_STUDIO_ROOT/memake"

function Utils-Config {
    param (
        [parameter(Mandatory = $true)]$Name,
        [parameter(Mandatory = $true)]$Value
    )
    return "-C" + $Name + "=" + $Value
}

function Utils-CreateConfiguration {
    param (
        [parameter(Mandatory = $true)]$Configuration
    )

    $Result = @()

    foreach ($Entry in $Configuration.PSObject.Properties) {
        $Result += "-C" + $Entry.Name + "=" + $Entry.Value
    }
    return $Result
}

Function Memake-Configure {
    param(
        [parameter(Mandatory = $true)]$OutDir,
        [parameter(Mandatory = $true)]$SrcDir,
        [parameter(Mandatory = $true)]$Mcu,
        [parameter(Mandatory = $true)]$Toolchain,
        [parameter(Mandatory = $true)]$Board,
        [parameter(Mandatory = $true)]$Flags,
        [parameter(Mandatory = $true)]$Core,
        [parameter(Mandatory = $true)]$Freq,
        [parameter(Mandatory = $false)]$Cfg,
        $Configuration,
        $InstallPrefix,
        $PrefixPaths
    )

    if ($Toolchain -eq 'mikrocarm') {
        $CompilerLibsPath = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/ARM/mikroC/" -ChildPath "libs"
        $MikroCCmd = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/ARM/mikroC/mikroCARM" -ChildPath "."
    } elseif ($Toolchain -eq 'mikrocpic') {
        $CompilerLibsPath = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/PIC/mikroC/" -ChildPath "libs"
        $MikroCCmd = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/PIC/mikroC/mikroCPIC1618" -ChildPath "."
    } elseif ($Toolchain -eq 'mikrocpic32') {
        $CompilerLibsPath = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/PIC32/mikroC/" -ChildPath "libs"
        $MikroCCmd = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/PIC32/mikroC/mikroCPIC32" -ChildPath "."
    } elseif ($Toolchain -eq 'mikrocdspic') {
        $CompilerLibsPath = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/dsPIC/mikroC/" -ChildPath "libs"
        $MikroCCmd = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/dsPIC/mikroC/mikroCdsPIC" -ChildPath "."
    } elseif ($Toolchain -eq 'mikrocavr') {
        $CompilerLibsPath = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/AVR/mikroC/" -ChildPath "libs"
        $MikroCCmd = Utils-JoinPath -Path "$Env:MIKROE_STUDIO_ROOT/compilers/AVR/mikroC/mikroCAvr" -ChildPath "."
    }

    $PrefixPaths += $CompilerLibsPath
    $MemakePrefixPaths += $PrefixPaths -join ';'

    if ($null -ne $Cfg) {
        $Configuration += "-CMEMAKE_LINKER_CFG=$Cfg"
    }

    return & $Memake '-o' "$OutDir" '--generate' "$SrcDir" "-CMEMAKE_TOOLCHAIN=$MikroCCmd" "-CMEMAKE_DEVICES=$Mcu" "-CMEMAKE_MCU_NAME=$Mcu" "-CMEMAKE_DELAY_FREQ=$Freq" "-CBOARD_NAME=$Board" "-CMEMAKE_PREFIX_PATH=$MemakePrefixPaths" "-CMEMAKE_COMPILER_FLAGS=$Flags" "-CMEMAKE_LINKER_FLAGS=$Flags" "-CMEMAKE_CORE_NAME=$Core" "-CMEMAKE_INSTALL_PREFIX=$InstallPrefix" $Configuration

}

Function Memake-BuildAll {
    param(
        [parameter(Mandatory = $true)]$OutDir
    )
    return & $Memake "-o" "$OutDir" "--build" "all"
}

Function Memake-Install {
    param(
        [parameter(Mandatory = $true)]$OutDir
    )
    return & $Memake "-o" "$OutDir" "--install"
}

function Get-JsonObjFromFile {
    param(
        [parameter(Mandatory = $true)]$File
    )

    $JsonObject = Get-Content $File | out-string | ConvertFrom-Json -ErrorAction Stop #out-string necessary for build on WIN7
    return $JsonObject;
}

function Utils-WriteTarget {
    param (
        $Target
    )

    Write-Host "Name:" $Target.Name
    Write-Host "Mcu:" $Target.Mcu
    Write-Host "Board:" $Target.Board
}

function Utils-MemakeLog {
    param (
        [parameter(Mandatory = $true)]$Mcu,
        [parameter(Mandatory = $true)]$LogFile,
        [switch]$Failed
    )

    Write-Host "Running memake for $Mcu " -ForegroundColor White -NoNewline
    "Running memake for $Mcu " | Out-File -File $LogFile -NoNewline -Append
    if ($Failed) {
        Write-Host 'FAILED.' -ForegroundColor Red
        "FAILED." | Out-File -File $LogFile -Append
    }
    else {
        Write-Host 'OK.' -ForegroundColor Green
        "OK." | Out-File -File $LogFile -Append
    }
}

function Utils-RecursionLog {
    param (
        [parameter(Mandatory = $true)]$Mcu,
        [parameter(Mandatory = $true)]$LogFile,
        [switch]$Failed
    )

    Write-Host "[$Global:currentCount/$Global:chipBuildCount] Building $Mcu " -ForegroundColor White -NoNewline
    "[$Global:currentCount/$Global:chipBuildCount Building $Mcu " | Out-File -File $LogFile -NoNewline -Append
    $Global:currentCount++
    if ($Failed) {
        Write-Host 'FAILED.' -ForegroundColor Red
        "FAILED." | Out-File -File $LogFile -Append
    }
    else {
        Write-Host 'OK.' -ForegroundColor Green
        "OK." | Out-File -File $LogFile -Append
    }
}

function Utils-RecursionLogError {
    param(
        [parameter(Mandatory = $true)]$LogFile,
        [parameter(Mandatory = $true)]$Output,
        [parameter(Mandatory = $true)]$Mcu
    )

    $ErrorMatches = $(($Output -split "[\r\n]+") | Select-String -Pattern "error\[\d+\]")

    foreach ($ErrorMatch in $ErrorMatches) {
        $ErrorMatch | Out-File -FilePath $LogFile -Append
    }
}

function Utils-WriteSeparator {
    Write-Host "--------------------------------------------------------------------------------"
}

function Utils-CheckForErrors {
    [CmdletBinding()]
    param (
        [Parameter(Mandatory=$true)]
        [String]$mcu,
        [Parameter(Mandatory=$true)]
        [String]$buildLogFile,
        [Parameter(Mandatory=$true)]
        [String]$errorLogFile,
        [Parameter(Mandatory=$true)]
        [String]$outDirPath,
        [Switch]$build
    )
    if ($LASTEXITCODE -ne 0) {
        if ( -not $build ) {
            Utils-RecursionLog -Mcu $mcu -LogFile $buildLogFile -Failed
            $memakeOutput | Out-File -File $errorLogFile -Append

            if ( -not $Global:silent ) {
                Write-Host $memakeOutput
            }

            Remove-Item -Path $outDirPath -Recurse
            $Global:cnt++
            Continue
        } else {
            Utils-RecursionLog -Mcu $mcu -LogFile $buildLogFile -Failed

            "-------------------------------------------------------------" | `
            Out-File -FilePath $errorLogFile -Append

            "Build failed for $mcu" | `
            Out-File -FilePath $errorLogFile -Append

            "-------------------------------------------------------------" | `
            Out-File -FilePath $errorLogFile -Append

            Utils-RecursionLogError -Mcu $mcu `
                                    -LogFile $errorLogFile `
                                    -Output $memakeOutput

            if ( -not $Global:silent ) {
                Write-Host $MemakeOutput
            }

            Remove-Item -Path $outDirPath -Recurse
            $Global:cnt++
            Continue
        }
    }
}

function Utils-SetValues($core) {
    $Global:currentCount = 1
    switch ($core) {
        "STM32_M0" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_STM_M0"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M0'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/STM32/"
            return $false
        }
        "STM32_M3" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_STM_M3"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M3'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/STM32/"
            return $false
        }
        "STM32_M4" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_STM_M4"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M4EF'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/STM32/"
            return $false
        }
        "STM32_M7" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_STM_M7"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M7'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/STM32/"
            return $false
        }
        "NXP_M4DSP" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_NXP_M4DSP"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M4DSP'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/NXP/"
            return $false
        }
        "NXP_M4EF" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_NXP_M4EF"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M4EF'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/NXP/"
            return $false
        }
        "NXP_M7" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_NXP_M7"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M7'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/NXP/"
            return $false
        }
        "TIVA_M4EF" {
            $Global:architecture = "ARM"
            $Global:buildOut = "recursion_TIVA_M4EF"
            $Global:selectedToolchain = "mikrocarm"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'M4EF'
            $Global:mcuDefPath = "../targets/arm/mikroe/common/include/mcu_definitions/TIVA/"
            return $false
        }
        "PIC18" {
            $Global:architecture = "PIC"
            $Global:buildOut = "recursion_PIC18"
            $Global:selectedToolchain = "mikrocpic"
            $Global:selectedFlags = "-DBG -O11111114 -C"
            $Global:selectedCore = 'P18'
            $Global:mcuDefPath = "../targets/pic_8bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "DSPIC" {
            $Global:architecture = "DSPIC"
            $Global:buildOut = "recursion_DSPIC"
            $Global:selectedToolchain = "mikrocdspic"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'DSPIC'
            $Global:mcuDefPath = "../targets/pic_16bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "PIC32_MIPS32" {
            $Global:architecture = "PIC32"
            $Global:buildOut = "recursionPIC32_MIPS32"
            $Global:selectedToolchain = "mikrocpic32"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'MIPS32'
            $Global:mcuDefPath = "../targets/pic_32bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "PIC32_MICROAPTIV" {
            $Global:architecture = "PIC32"
            $Global:buildOut = "recursion_PIC32_MICROAPTIV"
            $Global:selectedToolchain = "mikrocpic32"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'MICROAPTIV'
            $Global:mcuDefPath = "../targets/pic_32bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "PIC32_MICROAPTIV_FP" {
            $Global:architecture = "PIC32"
            $Global:buildOut = "recursion_PIC32_MICROAPTIV_FP"
            $Global:selectedToolchain = "mikrocpic32"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'MICROAPTIV_FP'
            $Global:mcuDefPath = "../targets/pic_32bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "AVR_GT64K" {
            $Global:architecture = "AVR"
            $Global:buildOut = "recursion_AVR_GT64K"
            $Global:selectedToolchain = "mikrocavr"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'GT64K'
            $Global:mcuDefPath = "../targets/avr_8bit/mikroe/common/include/mcu_definitions/"
            return $false
        }
        "AVR_LTE64K" {
            $Global:architecture = "AVR"
            $Global:buildOut = "recursion_AVR_LTE64K"
            $Global:selectedToolchain = "mikrocavr"
            $Global:selectedFlags = "-DBG -O11111114 -C -SSA"
            $Global:selectedCore = 'LTE64K'
            $Global:mcuDefPath = "../targets/avr_8bit/mikroe/common/include/mcu_definitions/"
            return $false
        }

        Default
        {
            Write-Host "Check values passed to script and try again.`n"
            return $true
        }
    }
}

function Utils-Format-Json([Parameter(Mandatory, ValueFromPipeline)][String] $json) {
    $indent = 0;
    ($json -Split '\n' |
      % {
        if ($_ -match '[\}\]]') {
          # This line contains  ] or }, decrement the indentation level
          $indent--
        }
        $line = (' ' * $indent * 4) + $_.TrimStart().Replace(':  ', ': ')
        if ($_ -match '[\{\[]') {
          # This line contains [ or {, increment the indentation level
          $indent++
        }
        $line
    }) -Join "`n"
}

function Utils-Generate-Cfg-File() {
    [CmdletBinding()]
    param (
        [Parameter(Mandatory=$true)]
        [String]$mcu,
        [Parameter(Mandatory=$true)]
        [String]$output,
        [String]$package
    )

    $mcuJsonRootPath = Join-Path -Path $Env:MIKROE_STUDIO_ROOT -ChildPath "./compilers/$Global:architecture/mikroC/Defs" -Resolve

    if ( $package.Length -gt 1 ) {
        $mcuTmp = $mcu.Substring(0, $mcu.Length - $package.Length)
    } else {
        $mcuTmp = $mcu
    }

    $mcuJsonFileContent = Get-Content -Path "$mcuJsonRootPath/$mcuTmp.json" | ConvertFrom-Json

    $generatedJsonFile = [PSCustomObject]@{
        clock = [Int]$mcuJsonFileContent.clock
        mcu = [String]$mcuTmp
        package = ''
        config_registers = [Array]''
    }

    foreach ( $node in $mcuJsonFileContent.config_registers ) {
        $subNode = [PSCustomObject]@{
            key = [String]$node.key
            fields = [Array]''
        }

        foreach ( $field in $node.fields ) {
            $subField = [PSCustomObject]@{
                key = [String]$field.key
                value = [String]$field.init
            }
            $subNode.fields += $subField
        }

        $generatedJsonFile.config_registers += $subNode
    }

    if ( !(Test-Path -Path $output/$mcu/CFG_DIR) ) {
        New-Item -Path $output/$mcu/CFG_DIR -ItemType Directory | Out-Null
    }

    $generatedJsonFile | ConvertTo-Json -Depth 10 | ForEach-Object {
        [Regex]::Replace($_,
            "\\u(?<Value>[a-zA-Z0-9]{4})", {
                param($m) ([char]([int]::Parse($m.Groups['Value'].Value,
                    [System.Globalization.NumberStyles]::HexNumber))).ToString() } )} | Utils-Format-Json | Set-Content $output/$mcu/CFG_DIR/$mcu.json -Encoding Ascii
}
