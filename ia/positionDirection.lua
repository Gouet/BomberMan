--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/26/16
-- Time: 11:12 AM
-- To change this template use File | Settings | File Templates.
--

--[[
--Return a table of 4 directions with the key corresponding to the macro
 ]]
function dirTab()
    return {[RIGHT] = Vector2.creat(1, 0), [LEFT] = Vector2.creat(-1, 0), [UP] = Vector2.creat(0, 1), [DOWN] = Vector2.creat(0, -1)};
end

--[[
--Return the direction corresponding to the code send in parameter
 ]]
function getDirFromCode(code)
    return (dirTab()[code]);
end

--[[
--Check if the position is in the map
 ]]
function isInMap(pos)
    if (pos:getX() < 0 or pos:getX() >= MapW or
            pos:getY() < 0 or pos:getY() >= MapH) then
        return (false);
    end
    return (true);
end

--[[
--Check if the player can move to pos
 ]]
function canMoveOnPos(pos)
    local tocheck = bomberMap:getDangerAtPos(pos:getX(), pos:getY());

    if (tocheck == BLOCKED or isInMap(pos) == false) then
        return (false);
    end
    return true;
end

--[[
--Check if the player can move safely on the position
 ]]
function canMoveSafelyOnPos(pos)
    local tocheck = bomberMap:getDangerAtPos(pos:getX(), pos:getY());

    if (canMoveOnPos(pos) == false or tocheck == DANGEROUS) then
        return (false);
    end
    return true;
end

--[[
--Get all possibles position that the player is allowed to go
 ]]
function getPossiblePos(pos)
    local tocheck = dirTab();
    local possib = {};
    local i = 0;

    for k, dir in pairs(tocheck) do
        local gonnasee = pos:add(dir);
        if (canMoveOnPos(gonnasee)) then
            i = i + 1;
            possib[i] = k;
        end
    end
    return possib, i;
end

--[[
-- Get all possibles and safe position that the player can go
 ]]
function getPossibleSafePos(pos)
    local tocheck = dirTab();
    local possib = {};
    local i = 0;

    for k, dir in pairs(tocheck) do
        local gonnasee = pos:add(dir);
        if (canMoveSafelyOnPos(gonnasee)) then
            i = i + 1;
            possib[i] = k;
        end
    end
    return possib, i;
end