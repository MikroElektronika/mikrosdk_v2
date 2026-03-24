# Devdocs

## 1. Situation

MikroSDK provides support for **Click Shields**, that expose multiple mikroBUS sockets on compatible devboards. Board to shield compatibility is determined by two conditions:
- Physical compatibility (ie. Nucleo 32 Board is compatible with Nucleo 32 Shield, and not with Nucleo 64 shield)
- Logical compatibility (all pins referenced in shield.h<sup>1)</sup> are defined and assigned (or whitelisted<sup>2)</sup>) in board.h<sup>1)</sup>)



1) board.h and shield.h live in bsp/board/include/*
2) whitelisting will be explained further in this document

## 2. Task
Having to manually check for compatibility in such a way is busywork, automating that process was the motivation behind this internship project.


## 3. Execution
This project consists of 3 logical units (and scripts):
1. PinMapper
    - Reads all board.h and shield.h, prepares 2 JSON files (board_map and shield_map), one for boards and one for shields, maps describe the following data:
        - Board/shield name, form factor (Nucleo 32/64/144) and pin assignments
2. Validator
    - Reads and compares the JSON files provided by PinMapper. According to the validation results, creates 2 JSON files, compatibilityMap and actionMap Results of comparison can be:
        - Board and shield pair is compatible, physical and logical compatibility is achieved, this result is added into compatibilityMap and no further action from the developer is required
        - Board and shield pair is compatible physically, but not logically. This means that the board has missing pin definitions, those are detected, added into actionMap, and will require action from the developer to achieve compatibility
        - Board and shield are not physically compatible, nothing can be done about it, and this pair is not saved anywhere
3. HeaderUpdater
    - Reads the JSON files (compatibilityMap, actionMap) provided by Validator. Performs the following operations:
        - For every compatible board/shield in compatibilityMap, generates new cmake that will enable compilation with shields, adds *#include "shield.h"* in the source code of board.h, updates *resources/queries/boardName/Board.json* to add a shield tag in a relevant area of the file, required for other automations
        - Reads actionMap, if there are any new pin definitions made by the developer inside that file, applies them to the relevant header file.


# How to use

0. <ins>**_Checkout new feature branch_**</ins>
1. Edit the updateBoardShieldCompatibility.yaml so the pull request creation step references the new feature branch from step 0.
2. Execute the workflow upon the new branch from step 0
    - This step will update all boards that are already compatible, update the actionMap and create a pull request on the branch from step 0.
3. Merge the PR
4. Edit the actionMap if needed
    - The developer can add new pin definitions within the actionMap.json itself, those changes will be applied to relevant board headers with the next workflow execution
5. Execute the workflow upon the branch from step 0.
6. Merge the PR

If at any point the execution fails, an adequate error message will be displayed by the scripts, remediate the error and restart from step 1.


##  Details
All relevant scripts and map outputs are located in *scripts/BoardToShield/\**

## Future improvements
The workflow can be improved by utilizing workflow artifacts for developer input (instead of having to push the updated files on the branch, the script could automatically download the files from release/assets, where the developer would upload them manually)