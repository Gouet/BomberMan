//
// Created by gaspar_q on 6/2/16.
//

#include <stddef.h>
#include "BomberMap.hpp"
#include "LuaGameObjectArray.hpp"

template <>
const std::string Lua::LuaClass<std::vector<AGameObject *> >::className = "GameObjectArray";

int LuaGameObjectArray::typeAtIndex(lua_State *state)
{
    std::vector<AGameObject *> *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->size())
        return 0;
    lua_pushinteger(state, (*thisptr)[index]->getType());
    return 1;
}

int LuaGameObjectArray::posAtIndex(lua_State *)
{
    std::vector<AGameObject *> *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->size())
        return 0;

    Lua::LuaClass<irr::core::vector2df> toreturn((*thisptr)[index]->getMapPos());
    toreturn.dontDelete();
    return 1;
}

int LuaGameObjectArray::size(lua_State *state)
{
    std::vector<AGameObject *>  *thisptr = Lua::LuaClass<std::vector<AGameObject *>>::getThis();

    lua_pushinteger(state, static_cast<int>(thisptr->size()));
    return 1;
}

int LuaGameObjectArray::hasType(lua_State *state)
{
    std::vector<AGameObject *>  *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int type = Lua::LuaClass<std::vector<AGameObject *>>::getInteger(2);
    bool isOfType = false;

    for (std::vector<AGameObject *>::iterator it = thisptr->begin(), end = thisptr->end(); it != end; ++it)
    {
        if ((*it)->getType() == type)
            isOfType = true;
    }
    lua_pushboolean(state, isOfType);
    return true;
}
