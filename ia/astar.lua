--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/26/16
-- Time: 10:44 AM
-- To change this template use File | Settings | File Templates.
--

Queue = {};
Stack = {};

function Queue.new()
    return {first = 0, last = -1};
end

function Queue.push(list, value)
    local topush = list.first - 1;
    list.first = topush;
    list[topush] = value;
end

function Queue.pop(list)
    local last = list.last;
    if list.first > last then
        return nil;
    end
    local value = list[last];
    list[last] = nil;
    list.last = last - 1;
    return value;
end

function Stack.new()
    return {first = 0, last = -1};
end

function Stack.push(list, value)
    local topush = list.first - 1;
    list.first = topush;
    list[topush] = value;
end

function Stack.pop(list)
    local first = list.first;
    if first > list.last then
        return nil;
    end
    local value = list[first];
    list[first] = nil;
    list.first = first + 1;
    return value;
end

function getHeuristique(pos, focus, cost)
    local diffX = focus:getX() - pos:getX();
    local diffY = focus:getY() - pos:getY();
    local dist = math.sqrt(diffX * diffX + diffY * diffY);
    local heur = dist + cost;

    if (canMoveSafelyOnPos(pos) == false) then
        heur = heur + 3;
    end
    if (bomberMap:getDangerAtPos(pos:getX(), pos:getY()) == BONUSED) then
        heur = heur - 1;
    end
    return heur;
end

saw = {}

function alreadySaw(pos)
    for _, curr in pairs(saw) do
        if (pos:equal(curr)) then
            return (true);
        end
    end
    return (false);
end

--todo push in queue and stack depending on heuristique
function astarGetNextPos(currPos, focus)
    local runQueue = Queue.new();
    local saveStack = Stack.new();
    local popedValue;
    local possib;
    local cost = 0;
    local lower;
    local firstMove;

    saw = {};
    Queue.push(runQueue, currPos);
    repeat

        --[[
        --pop the good value
         ]]
        popedValue = Queue.pop(runQueue);
        if (popedValue == nil) then
            popedValue = Stack.pop(saveStack);
            cost = cost - 1;
        else
            cost = cost + 1;
        end

        if (popedValue ~= nil) then

            --[[
            --get possible posses around the current position
             ]]
            table.insert(saw, popedValue);
            possib = getPossiblePos(popedValue);
            lower = {euri = 10000000, pos = nil};
            for k, dir in pairs(possib) do
                local posToCheck = popedValue:add(getDirFromCode(dir));
                local heur = getHeuristique(posToCheck, focus, cost);

                if (alreadySaw(posToCheck) == false) then
                    if (lower.euri > heur) then
                        if (lower.pos ~= nil) then
                            Stack.push(saveStack, lower.pos);
                        end
                        lower.euri = heur;
                        lower.pos = posToCheck;
                        if (cost == 1) then
                            firstMove = dir;
                        end
                    else
                        Stack.push(saveStack, posToCheck)
                    end
                end
                if (focus:equal(posToCheck)) then
                    return (firstMove);
                end
            end
            if (lower.pos ~= nil) then
                Queue.push(runQueue, lower.pos);
            end
        end
    until (popedValue == nil)
    return (nil);
end