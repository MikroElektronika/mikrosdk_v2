local lunajson = require("lunajson")
local lfs = require("lfs")

local params = {...}

local pathToSDK = params[1]
local pathToBoards = pathToSDK .. "bsp/board/include/boards/"
local pathToShields = pathToSDK .. "bsp/board/include/shields/"


function get_folders_on_path(directory_path)
    local folders = {}

    for entry in lfs.dir(directory_path) do
        if entry ~= "." and entry ~= ".." then
            local full_path = directory_path .. "/" .. entry
            local mode = lfs.attributes(full_path, "mode")
            if mode == "directory" then
                table.insert(folders, entry)
            end
        end
    end

    return folders
end

function getAllNucleoElements(path_to_scan)
    local result = {}

    local all_folders = get_folders_on_path(path_to_scan)
    for _, folder_name in ipairs(all_folders) do
        if (string.match(folder_name, ".*nucleo.*")) then
            table.insert(result, folder_name)
        end
    end

    return result
end

local nucleoBoards = getAllNucleoElements(pathToBoards)
local nucleoShields = getAllNucleoElements(pathToShields)

local boardData = {}
local shieldData = {}
boardData.boards = {}
shieldData.shields = {}

for _, board in pairs(nucleoBoards) do
    local headerFile = io.open(pathToBoards .. "/" .. board .. "/board.h", "r")
    local formFactor = string.match(board, "nucleo_%d+")
    local pinMap = {}

    if headerFile then
        for w in headerFile:lines() do
            if string.match(w, "(.*HEADER_CONNECTOR.*)") then
                w = string.sub(w, string.find(w, " ") + 1, -1)
                w = string.gsub(w, "%s+", " ")
                local splitPos = string.find(w, " ")
                local headerConnector = string.sub(w, 1, string.find(w, " "))
                local mappedTo = string.sub(w, splitPos + 1, string.find(w, " ", splitPos + 1))
                headerConnector = string.gsub(headerConnector, "%s*", "")
                mappedTo = string.gsub(mappedTo, "%s*", "")

                if mappedTo == "" or mappedTo == "//" then
                    mappedTo = nil
                end

                pinMap[headerConnector] = {}
                pinMap[headerConnector].MappedTo = mappedTo
            end
        end
    else
        warn("failed to open header file for " .. board)
    end


    local boardObject = {}
    boardObject.board = board
    boardObject.formFactor = formFactor
    boardObject.mappingDictionary = pinMap
    table.insert(boardData.boards, boardObject)
end


for _, shield in pairs(nucleoShields) do
    local headerFile = io.open(pathToShields .. "/" .. shield .. "/shield.h", "r")
    local formFactor = string.match(shield, "nucleo_%d+")


    local pinMap = {}
    if headerFile then
        for w in headerFile:lines() do
            if string.match(w, "(.*HEADER_CONNECTOR.*)") then
                w = string.sub(w, string.find(w, " ") + 1, -1)
                w = string.gsub(w, "%s+", " ")
                local shieldConnector = string.sub(w, 1, string.find(w, " "))
                local mappedTo = string.sub(w, string.find(w, " ") + 1, -1)
                shieldConnector = string.gsub(shieldConnector, "%s*", "")
                mappedTo = string.gsub(mappedTo, "%s*", "")


                pinMap[shieldConnector] = {}
                pinMap[shieldConnector].MappedTo = mappedTo
            end
        end
    else
        warn("failed to open header file for " .. shield)
    end

    local shieldObject = {}
    shieldObject.shield = shield
    shieldObject.formFactor = formFactor
    shieldObject.mappingDictionary = pinMap
    table.insert(shieldData.shields, shieldObject)
end


local boardJsonString = lunajson.encode(boardData)
local shieldJsonString = lunajson.encode(shieldData)

local boardOutputFile = io.open("../PinMaps/board_map.json", "w+")

if boardOutputFile then
    boardOutputFile:write(boardJsonString)
    boardOutputFile:flush()
    boardOutputFile:close()
else
    error("failed to write board_map.json")
end

local shieldOutputFile = io.open("../PinMaps/shield_map.json", "w+")

if shieldOutputFile then
    shieldOutputFile:write(shieldJsonString)
    shieldOutputFile:flush()
    shieldOutputFile:close()
else
    error("failed to write shield_map.json")
end

print("Mapping successful!")
