[CmdletBinding()]
param (
    [Switch]$gccArm,
    [Switch]$gccRiscv,
    [Switch]$mikrocArm,
    [Switch]$mikrocAvr,
    [Switch]$mikrocPic18,
    [Switch]$mikrocDspic,
    [Switch]$mikrocPic32,
    [Switch]$useCurrentBranch,
    [Parameter(Mandatory=$false)][String]$branchName,
    [Parameter(Mandatory=$false)][String]$sdkVersion,
    [Parameter(Mandatory=$false)][String]$cicdDockerImage,
    [Parameter(Mandatory=$false)][String]$cicdToken

)

function getUserInput($title, $message) {
    [void][Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic')
    $userIn = [Microsoft.VisualBasic.Interaction]::InputBox($message, $title)
    return $userIn
}

function fillOutObject([ref]$objectIn) {
    $counter = 0
    if ($gccArm) {
        $objectIn.Value[$counter++] = @('gccArm','gcc_arm_none_eabi')
    }
    if ($gccRiscv) {
        $objectIn.Value[$counter++] = @('gccRiscv','xpack-riscv-none-embed-gcc')
    }
    if ($mikrocArm) {
        $objectIn.Value[$counter++] = @('mikrocArm','mikrocarm')
    }
    if ($mikrocAvr) {
        $objectIn.Value[$counter++] = @('mikrocAvr','mikrocavr')
    }
    if ($mikrocPic18) {
        $objectIn.Value[$counter++] = @('mikrocPic18','mikrocpic')
    }
    if ($mikrocDspic) {
        $objectIn.Value[$counter++] = @('mikrocDspic','mikrocdspic')
    }
    if ($mikrocPic32) {
        $objectIn.Value[$counter++] = @('mikrocPic32','mikrocpic32')
    }
}

function TriggerDeploy {
    Param(
        [Parameter(Mandatory = $true, ValueFromPipeline = $true, ValueFromPipelineByPropertyName = $true)]
        [string]$cicdBranchOrTagName,
        [Parameter(Mandatory = $true, ValueFromPipeline = $true, ValueFromPipelineByPropertyName = $true)]
        [string]$cicdArtifactPath,
        [Parameter(Mandatory = $true, ValueFromPipeline = $true, ValueFromPipelineByPropertyName = $true)]
        [string]$cicdCompiler,
        [Parameter(Mandatory = $true, ValueFromPipeline = $true, ValueFromPipelineByPropertyName = $true)]
        [string]$cicdSdk
    )

    $Body = @{
        token                              = $cicdToken
        ref                                = $cicdBranchOrTagName

        "variables[TRIGGER_DOCKER_IMAGE]"  = $cicdDockerImage
        "variables[TRIGGER_ARTIFACT_PATH]" = $cicdArtifactPath
        "variables[TRIGGER_COMPILER]"      = $cicdCompiler
        "variables[TRIGGER_SDK]"           = $cicdSdk
    }

    ## mikroSDK project webhook with parameters.
    Invoke-WebRequest 'https://gitlab.mikroe.com/api/v4/projects/1500/trigger/pipeline' -Method 'POST' -Body $Body
    ## Wait for webhook to finish.
    ## NOTE that this might need to be increased based on PC performance.
    ## i.e. slower PC higher timeout.
    Start-Sleep -Seconds 2
}

## Select SDK version and branch.
if (!$sdkVersion) {
    if ($useCurrentBranch) {
        $sdkVersion = 'mikrosdk_v' +
                      $($(Get-Content -Path $PSScriptRoot/../manifest.json | ConvertFrom-Json).'sdk-version' -replace '\.','')
    } else {
        $sdkVersion = 'mikrosdk_v' + $(getUserInput ('SDK selector') `
                                                    ("Provide sdk version:`n(i.e `"280 for mikroSDK v2.8.0`")."))
    }
}

if (!$branchName) {
    if ($useCurrentBranch) {
        $branchName = git rev-parse --abbrev-ref HEAD
    } else {
        $branchName = getUserInput ('Branch selector') `
                                   ("Provide full branch name:`n(i.e `"topic/chart-log`").")
    }
}

$sdk_version = $sdkVersion
$branch = $branchName

if (!$cicdDockerImage) {
    $cicdDockerImage = $(getUserInput ('Docker image selector') `
                                      ("Provide Docker image for deploy trigger:`n(i.e `"ns2:gcc/ns2:latest etc...`")."))
    ## Use latest image by default if no valid image provided.
    if ($cicdDockerImage -eq '') {
        $cicdDockerImage = 'ns5:latest'
    }
}

## Check if token is provided or not.
if (!$cicdToken) {
    ## Default token if not passed to script.
    ## Tokens can be generated on GITLAB repository via browser.
    switch ($Env:UserName) {
        'strahinja.jacimovic' { $cicdToken = '8f9e42fcb02d4228614431b74baefb' }
        # 'marko.zivanovic' { $cicdToken = 'TODO' }
        # 'esma.niksic' { $cicdToken = 'TODO' }
        # 'stefan.djordjevic' { $cicdToken = 'TODO' }
        # 'ivan.ruzavin' { $cicdToken = 'TODO' }

        Default { $cicdToken = '8f9e42fcb02d4228614431b74baefb' }
    }
}

$objectIn = @{}
fillOutObject ([ref]$objectIn)

## Trigger appropriate deploy build
$selectArtifact = 0
$selectCompiler = 1
foreach ($item in $objectIn.Values) {
    TriggerDeploy -cicdBranchOrTagName $branch `
                  -cicdArtifactPath $item[$selectArtifact] `
                  -cicdCompiler $item[$selectCompiler] `
                  -cicdSdk $sdk_version
}
