# HAL Recursion build CI/CD

*Directory contains everything required for successful SDK recursive build.*

## Prerequisites

In order for the script to be run, following prerequisites **MUST** be met:

+ Define following environment variable:
  + Variable: `MIKROE_STUDIO_ROOT`
  + Value: `PATH_TO_NECTO_INSTALL_ROOT`
    + By default: `c:/NectoStudio/NectoStudio`
+ If running script with the `customParams` switch
  + Fill out following fields in `customParams.json` file
    + `silent`
      + true
      + false
    + `coreSelect`
      + Desired core, i.e `STM32_M0`, etc.
    + `chipRegex`
      + Desired chip regex, i.e `(^STM32(F|L|G)0(.+)$)`
  + Filling this file will run the script automatically with your predefined values

## Script parameters

+ `silent`
  + Defines whether or not compiler will outpul full return messages
+ `coreSelect`
  + Defines which chip cores are to be built
+ `chipRegex`
  + Defines which chips are to be built
  + Use regular expressions for this parameter
+ `customParams`
  + If switch is set, script will take parameters from `customParams.json` file

## Example run

+ Open PowerShell terminal
+ Change directory to script root
  + `cd DIR_PATH/mikrosdk-praksa/scripts`
+ Run script by typing `./build-hal-recursion-ci.ps1`
  + Pass any parameters you want

For example, running build for all STM32 M0 chips would look like this:
`./build-hal-recursion-ci.ps1 -coreSelect "M0"`

An even quicker run would look like this:
`./build-hal-recursion-ci.ps1 -coreSelect "M0" -chipRegex "^(STM32(F|L|G)0(.+))"`

The regex `^(STM32(F|L|G)0(.+))` will select all `STM32F0xx`, `STM32L0xx` and `STM32G0xx` chips.

Alternatively, set desired values in `customParams.json` file and just run the `customRun.bat` or `customRun.sh` file.

> **LINUX NOTE**
>>
>> **In order to be able to run `.sh` files**
>> **run following command from terminal:**
>>> `chmod +x <sh_file_name>`
>>
>> **Where `<sh_file_name>` represents**
>> **shell file name.**
>>
>> **For example:**
>>> `chmod +x customRun.sh`

## `customParams.json` valid core values

+ `coreSelect`
  + `STM32_M0`
  + `STM32_M3`
  + `STM32_M4`
  + `STM32_M7`
  + `PIC18`
  + `PIC32_MIPS32`
  + `PIC32_MICROAPTIV`
  + `PIC32_MICROAPTIV_FP`
  + `NXP_M4DSP`
  + `NXP_M4EF`
  + `NXP_M7`
  + `TIVA_M4EF`
  + `DSPIC`
  + `AVR_GT64K`
  + `AVR_LTE64K`

## Script output

**Script outputs log files relative to script root path.**

**PATH:** ***../../build***

## Files included in directory

+ [build-hal-recursion-ci.ps1](./build-hal-recursion-ci.ps1)
+ [utility.ps1](./utility.ps1)
+ [customRun.bat](./customRun.bat)
+ [customRun.sh](./customRun.sh)
+ [customParams.json](./customParams.json)

---
