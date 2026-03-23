local params = { ... }

-- for _,v in pairs(params) do
--     print(v)
-- end



local lunajson = require("lunajson")
local prettyjson = require("lua-pretty-json")

local actionMapFile = io.open("../OutputMaps/actionMap.json", "r")
local compatibilityMapFile = io.open("../OutputMaps/compatibilityMap.json", "r")
local pathToSDK = params[1]
local pathToHeaderFolder = pathToSDK .. "bsp/board/include/boards/"

if not actionMapFile then
    error("No actionMap.json")
end

if not compatibilityMapFile then
    error("No compatibilityMap.json")
end

local actionMap = lunajson.decode(actionMapFile:read("a"))

if not actionMap then
    error("Error while decoding actionMap.json")
end

local compatibilityMap = lunajson.decode(compatibilityMapFile:read("a"))

if not compatibilityMap then
    error("Error while decoding compatibilityMap.json")
end

function readHeaderFile(boardName)
    local headerPath = pathToHeaderFolder .. boardName .. "/board.h"
    local headerFile = io.open(headerPath, "r")
    local lines = {}

    if not headerFile then
        warn("Cant find header file for " .. boardName)
    else
        for line in headerFile:lines() do
            table.insert(lines, line)
        end
    end

    return lines
end

function getMappingAreaBounds(lines)
    local mappingStartPos = nil
    local mappingEndPos = nil

    local bounds = {}

    for i, line in pairs(lines) do
        if (line == "// Mapping") then
            mappingStartPos = i
        elseif (line == "}" and lines[i - 1] == "#ifdef __cplusplus") then
            mappingEndPos = i - 2
        end
    end

    if not mappingStartPos or not mappingEndPos then
        error("board.h file not in valid format, missing \"// Mapping\" comment marking mapping area")
        return
    end

    bounds["start"] = mappingStartPos
    bounds["end"] = mappingEndPos

    return bounds
end

function updateHeader(lines, startPos, endPos, updates)
    for k, v in pairs(updates) do
        local pinName = k
        local value = v
        local updated = false

        if string.upper(value) == "WHITELIST" then
            value = "//##!!WHITELIST!!##"
        elseif value == "NOT DEFINED" or value == "NOT ASSIGNED" then
            --print("continuing")
            goto continue
        end

        local line = "#define " .. pinName .. "    " .. value
        --print(line)



        --to assign non assigned pins
        for i = startPos, endPos, 1 do
            if (string.find(lines[i], pinName)) then
                lines[i] = line
                updated = true
                break
            end
        end

        --to define non defined
        if not updated then
            table.insert(lines, endPos, line)
            updated = true
        end



        ::continue::
    end



    return lines
end

function writeHeader(board, lines)
    local headerFile = io.open(pathToHeaderFolder .. board .. "/board.h", "w+")

    if not headerFile then
        warn("failed to write header for " .. board)
    else
        for _, line in pairs(lines) do
            headerFile:write(line .. "\n")
        end
        headerFile:flush()
        headerFile:close()
    end
end

function applyActionsOnBoardHeader(board, actions)
    local lines = readHeaderFile(board)
    local positions = getMappingAreaBounds(lines)
    lines = updateHeader(lines, positions["start"], positions["end"], actions)
    writeHeader(board, lines)
end

function writeShieldCMake(boardName, value)
    local cmakeFile = io.open(pathToHeaderFolder .. boardName .. "/shield.cmake", "w+")
    if (not cmakeFile) then
        warn("failed to write cmake for " .. boardName)
    else
        if value then
            cmakeFile:write("set(SHIELD TRUE)")
        else
            cmakeFile:write("set(SHIELD FALSE)")
        end
        cmakeFile:flush()
        cmakeFile:close()
    end
end

function includeShieldHeader(boardName)
    local lines = readHeaderFile(boardName)
    local bounds = getMappingAreaBounds(lines)

    local shieldIncluded = false
    for _, v in pairs(lines) do
        if string.find(v, "#include \"shield.h\"") then
            shieldIncluded = true
        end
    end



    if not shieldIncluded then
        table.insert(lines, bounds["start"] - 1, "#include \"shield.h\"")
    end

    writeHeader(boardName, lines)
end

function string.insert(str1, str2, pos)
    return str1:sub(1, pos - 1) .. str2 .. str1:sub(pos)
end

function updateQueryJson(boardName, shieldName)
    local path = pathToSDK .. "resources/queries/boards/" .. boardName .. "/Boards.json"
    local jsonFile = io.open(path, "r")
    if jsonFile then
        local queryJson = lunajson.decode(jsonFile:read("a"))
        jsonFile:close()
        if not string.find(queryJson["sdk_config"], "_MSDK_SHIELD_") then
            jsonFile = io.open(path, "w+")


            queryJson["sdk_config"] = string.insert(queryJson["sdk_config"],
                "," .. "\\" .. "\"_MSDK_SHIELD_" .. "\\" .. "\":" .. "\\" .. "\"" .. shieldName .. "\\" .. "\"", -1)

            local jsonString = prettyjson:pretty_print(queryJson, nil, "\\")
            jsonFile:write(jsonString)
            jsonFile:flush()

            jsonFile:close()
        end
    else
        warn("Unable to update query json for " .. boardName)
    end
end

for _, v in pairs(actionMap) do
    for _, k in pairs(v.boards) do
        applyActionsOnBoardHeader(k.board, k.mappingDictionary)
    end
end





for _, k in pairs(compatibilityMap) do
    for _, v in pairs(k.boards) do
        writeShieldCMake(v, true)
        includeShieldHeader(v)
        updateQueryJson(v, k.shield)
    end
end
