//
// Created by gaspar_q on 6/2/16.
//

#include "AGameObject.hpp"
#include "BomberMap.hpp"
#include "LuaBomberMap.hpp"

template <>
const std::string Lua::LuaClass<BomberMap>::className = "BomberMap";

int LuaBomberMap::objsAtPos(lua_State *state)
{
    BomberMap   *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);
    Lua::LuaClass<std::vector<AGameObject *>>  objs(thisptr->getObjsFromVector2(irr::core::vector2df(x, y)));

    objs.dontDelete();
    return 0;
}

int LuaBomberMap::getNbOfType(lua_State *state)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);
    AGameObject::Type type = static_cast<AGameObject::Type >(Lua::LuaClass<BomberMap>::getInteger(4));
    std::vector<AGameObject *>  objs = thisptr->getObjsFromVector2(irr::core::vector2df(x, y));
    int nb = 0;

    for (std::vector<AGameObject *>::iterator it = objs.begin(), end = objs.end(); it != end; ++it)
    {
        if ((*it)->getType() == type)
            ++nb;
    }
    lua_pushinteger(state, static_cast<lua_Integer >(nb));
    return 1;
}

int LuaBomberMap::getDangerAtPos(lua_State *state)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);
    int ret = thisptr->giveDangerMap().getDangerAt(irr::core::vector2df(x, y));

    if (ret == -1)
        return 0;
    lua_pushinteger(state, static_cast<lua_Integer >(ret));
    return 1;
}
