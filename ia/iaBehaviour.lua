--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

--[[
--Global BomberMap
 ]]
bomberMap = {};

--[[
--Function for loading a file into another
 ]]
function dofile(file)
    local lib = assert(loadfile(file));
    return lib();
end

--[[
--Define:
--  -   dirTab
--  -   getDirFromCode
--  -   isInMap
--  -   canMoveOnPos
--  -   getPossiblePos
 ]]
dofile(BINARY.."ia/positionDirection.lua");

--[[
--Define:
 ]]
dofile(BINARY.."ia/astar.lua");

--[[
--Used for positions that are already saw
 ]]
posSeen = {};

--[[
--Find the first impasse in the map
 ]]
function findFirstImpasse(pos)
    local directions = dirTab();

    posSeen[pos:getX() + pos:getY() * MapW] = true;
    for _, dir in pairs(directions) do
        local togo = pos:add(dir);

        if (posSeen[togo:getX() + MapW * togo:getY()] == nil and canMoveOnPos(togo)) then
            return (findFirstImpasse(togo));
        end
    end
    return (pos);
end

--[[
--Will find a bonused focus
 ]]
function findBonusedFocus(pos)
    local directions = dirTab();

    posSeen[pos:getX() + pos:getY() * MapW] = true;
    for _, dir in pairs(directions) do
        local togo = pos:add(dir);

        if (bomberMap:getDangerAtPos(togo:getX(), togo:getY()) == BONUSED) then
            return togo;
        end
        if (posSeen[togo:getX() + MapW * togo:getY()] == nil and canMoveOnPos(togo)) then
            return (findBonusedFocus(togo));
        end
    end
    return (pos);
end

--[[
--Will check for a logic bomb drop
 ]]
function canDropBomb(iaplayer)
    local nextFocus;
    local pos = iaplayer:getPos();
    local directions = dirTab();

    if (canMoveSafelyOnPos(iaplayer:getPos()) == false) then
        return nil;
    end
    for _, dir in pairs(directions) do
        local tocheck = pos:add(dir);
        if (iaplayer:canDropBomb() or bomberMap:getNbOfType(tocheck:getX(), tocheck:getY(), OTHER) > 0--[[ or bomberMap:getNbOfType(pos:getX(), pos:getY(), CHARACTER) > 1]]) then
            posSeen = {};
            nextFocus = iaplayer:bombDropSimul();
            if (nextFocus ~= nil) then
                return nextFocus;
            end
        end
    end
    return nil;
end

--[[
--Choose if the IA will move, drop a bomb or idle
 ]]
function waitBombOrMove(iaplayer, lastCaseMove)
    local possibMove, nbPossib = getPossibleSafePos(iaplayer:getPos());
    local fimp;
    local nextFocus;

    if (iaplayer:getPos():equal(iaplayer:getFocus())) then
        posSeen = {}
        fimp = findFirstImpasse(iaplayer:getPos());
        if (nbPossib == 0 and canMoveSafelyOnPos(iaplayer:getPos())) then
            return IDLE;
        end
    end
    nextFocus = canDropBomb(iaplayer);
    if (nextFocus ~= nil) then
        return DROPBOMB, nextFocus;
    end
    return lastCaseMove(possibMove, nbPossib, iaplayer), fimp;
end

function runIa(iaplayer, lastCaseMove, findFocus)
    local fimp;
    local action;

    action, fimp = waitBombOrMove(iaplayer, lastCaseMove);
    if (fimp ~= nil) then
        iaplayer:setFocus(fimp);
    elseif (findFocus ~= nil and iaplayer:getFocus():equal(iaplayer:getPos())) then
        posSeen = {};
        iaplayer:setFocus(findFocus(iaplayer:getPos()));
    end
    return action;
end

--[[
--Function for logical ia moves
 ]]
function mediumMove(possibMove, nbPossib, iaplayer)
    local acttoRet;

    if (iaplayer:getPos():equal(iaplayer:getFocus()) == false) then
        acttoRet = astarGetNextPos(iaplayer:getPos(), iaplayer:getFocus());
    end
    if (acttoRet == nil) then
        if (nbPossib > 0) then
            return (possibMove[math.random(1, nbPossib)]);
        end
        return (IDLE);
    end
    if (canMoveSafelyOnPos(iaplayer:getPos()) and canMoveSafelyOnPos(iaplayer:getPos():add(getDirFromCode(acttoRet))) == false) then
        return (IDLE);
    end
    return (acttoRet);
end

--[[
--Function for an IA easy behaviour
--Will choose a focus, drop bomb logically but move randomly
 ]]
function easyBehaviour(iaplayer)
    return (runIa(iaplayer, function (possibMove, nbPossib)
        if (nbPossib > 0) then
            return possibMove[math.random(1, nbPossib)];
        end
        return math.random(LEFT, DOWN);
    end));
end

--[[
--Function for an IA medium behaviour
--Will choose a focus, drop bomb logically and move logically
 ]]
function mediumBehaviour(iaplayer)
  return runIa(iaplayer, mediumMove);
end

--[[
--Function for an IA hard behaviour
--Will choose a bonused focus, drop bomb logically and move logically
 ]]
function hardBehaviour(iaPlayer)
    return runIa(iaPlayer, mediumMove, findBonusedFocus);
end