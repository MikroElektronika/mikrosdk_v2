local lunajson = require("lunajson")


local fileShield = io.open("../PinMaps/shield_map.json", "r")
local fileBoard = io.open("../PinMaps/board_map.json", "r")

local jsonStrShield
if fileShield then
    jsonStrShield = fileShield:read("a")
    fileShield:close()
else
    error("no input file for shield data found", 2)
end

local jsonStrBoard
if fileBoard then
    jsonStrBoard = fileBoard:read("a")
    fileBoard:close()
else
    error("no input file for board data found", 3)
end
local shieldDataTable = lunajson.decode(jsonStrShield)
local boardDataTable = lunajson.decode(jsonStrBoard)



--find all boards with the targeted formFactor (ie. formFactor = "nucleo_64" => board = board_nucleo_64_with_xxxxxx)
function getBoardsWithFormFactor(targetFormFactor)
    local boardDataArray = {}
    for i, j in pairs(boardDataTable.boards) do
        local board = j.board
        local formFactor = j.formFactor
        local mappingDictionary = j.mappingDictionary

        if (formFactor == targetFormFactor) then
            local boardData = {}
            boardData.board = board
            boardData.formFactor = formFactor
            boardData.mappingDictionary = mappingDictionary
            table.insert(boardDataArray, boardData)
        end
    end

    return boardDataArray
end

--find all shields with the targeted formFactor (ie. formFactor = "nucleo_64" => shield = shield_nucleo_64)
function getShieldsWithFormFactor(targetFormFactor)
    local shieldDataArray = {}
    for i, j in pairs(shieldDataTable.shields) do
        local shield = j.shield
        local formFactor = j.formFactor
        local mappingDictionary = j.mappingDictionary

        if (formFactor == targetFormFactor) then
            local shieldData = {}
            shieldData.shield = shield
            shieldData.formFactor = formFactor
            shieldData.mappingDictionary = mappingDictionary
            table.insert(shieldDataArray, shieldData)
        end
    end

    return shieldDataArray
end

--Compare board and shield pin maps, to see if all referenced pins on the shield are mapped in the board map
function isMapped(pinMapBoard, pinMapShield)
    for k, v in pairs(pinMapShield) do
        --check if pin exists in map and if it is mapped to something
        if not pinMapBoard[v.MappedTo] or not pinMapBoard[v.MappedTo].MappedTo then
            return false
        end
    end
    return true
end

--get all compatible shields for a given board based on form factor (physical compatibility) and pin map (logical compatibility)
function findCompatibleShields()
    local compatibilityMap = {}
    for _, j in pairs(boardDataTable.boards) do
        local compatibilityKVP = {}
        local board = j.board
        local formFactor = j.formFactor
        local mappingDictionary = j.mappingDictionary
        local possibleShields = getShieldsWithFormFactor(formFactor)

        local compatibleShields = {}
        for _, v in pairs(possibleShields) do
            if isMapped(mappingDictionary, v.mappingDictionary) then
                table.insert(compatibleShields, v.shield)
            end
        end
        compatibilityKVP.board = board
        compatibilityKVP.shields = compatibleShields
        table.insert(compatibilityMap, compatibilityKVP)
    end
    return compatibilityMap
end

--get all compatible boards for a given shield based on form factor (physical compatibility) and pin map (logical compatibility)
function findCompatibleBoards()
    local compatibilityMap = {}
    for _, j in pairs(shieldDataTable.shields) do
        local compatibilityKVP = {}
        local shield = j.shield
        local formFactor = j.formFactor
        local mappingDictionary = j.mappingDictionary
        local possibleBoards = getBoardsWithFormFactor(formFactor)

        local compatibleBoards = {}
        for _, v in pairs(possibleBoards) do
            if isMapped(v.mappingDictionary, mappingDictionary) then
                table.insert(compatibleBoards, v.board)
            end
        end
        compatibilityKVP.shield = shield
        compatibilityKVP.boards = compatibleBoards
        table.insert(compatibilityMap, compatibilityKVP)
    end
    return compatibilityMap
end


--find all pins mentioned in a certain shield pin map that are non existent or non mapped in the board pin map
function comparePinMaps(pinMapBoard, pinMapShield)
    local result = {}
    for _, shieldPin in pairs(pinMapShield) do
        if not pinMapBoard[shieldPin.MappedTo] then
            result[shieldPin.MappedTo] = "NOT DEFINED"
        elseif not pinMapBoard[shieldPin.MappedTo].MappedTo then
            result[shieldPin.MappedTo] = "NOT ASSIGNED"
        end
    end

    return result
end


--find all boards that are non compatible with a given shield because of bad or missing mapping
function findActionsForNonCompatibleBoards()
    local actionMap = {}
    --iterate through all shields
    for _, j in pairs(shieldDataTable.shields) do
        local actionKVP = {}
        local shield = j.shield
        local formFactor = j.formFactor
        local mappingDictionary = j.mappingDictionary
        local possibleBoards = getBoardsWithFormFactor(formFactor)

        local nonCompatibleBoards = {}
        --find all boards that are not compatible due to bad mapping
        for _, v in pairs(possibleBoards) do
            if not isMapped(v.mappingDictionary, mappingDictionary) then
                table.insert(nonCompatibleBoards, v)
            end
        end

        --assemble a list of all pins that are wrongly mapped or undefined
        for _, v in pairs(nonCompatibleBoards) do
            local badPinMap = comparePinMaps(v.mappingDictionary, mappingDictionary)
            v.mappingDictionary = badPinMap
        end

        actionKVP.shield = shield
        actionKVP.boards = nonCompatibleBoards
        table.insert(actionMap, actionKVP)
    end
    return actionMap
end

local compatibilityMap = findCompatibleBoards()
local compatibilityJson = lunajson.encode(compatibilityMap)


local actionMap = findActionsForNonCompatibleBoards()
local actionJson = lunajson.encode(actionMap)


local compatibilityFile = io.open("../OutputMaps/compatibilityMap.json", "w+")
if compatibilityFile then
    compatibilityFile:write(compatibilityJson)
    compatibilityFile:close()
else
    error("could not write compatibility file", 3)
end


local actionFile = io.open("../OutputMaps/actionMap.json", "w+")
if actionFile then
    actionFile:write(actionJson)
    actionFile:close()
else
    error("could not write action file", 3)
end

print("Validation successful! Compatibility map and action map created!")
