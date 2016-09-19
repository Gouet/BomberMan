//
// Created by gaspar_q on 6/2/16.
//

#include <vector2d.h>
#include "LuaVector2.hpp"

template <>
const std::string Lua::LuaClass<irr::core::vector2df>::className = "Vector2";

int LuaVector2::createPos(lua_State *state)
{
    int x = Lua::LuaClass<irr::core::vector2df>::getInteger(1);
    int y = Lua::LuaClass<irr::core::vector2df>::getInteger(2);
    Lua::LuaClass<irr::core::vector2df> newpos(x, y);

    newpos.dontDelete();
    return 1;
}

int LuaVector2::getX(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushinteger(state, static_cast<lua_Integer >(thisptr->X));
    return 1;
}

int LuaVector2::getY(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushinteger(state, static_cast<lua_Integer >(thisptr->Y));
    return 1;
}

int LuaVector2::setX(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int toset = Lua::LuaClass<irr::core::vector2df>::getInteger(2);

    thisptr->X = toset;
    return 0;
}

int LuaVector2::setY(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int toset = Lua::LuaClass<irr::core::vector2df>::getInteger(2);

    thisptr->Y = toset;
    return 0;
}

int LuaVector2::mul(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int fact = Lua::LuaClass<irr::core::vector2df>::getInteger(2);
    irr::core::vector2df    multi = *thisptr * fact;
    Lua::LuaClass<irr::core::vector2df> torepush(multi);

    torepush.dontDelete();
    return 1;
}

int LuaVector2::add(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    irr::core::vector2df    *toAdd = Lua::LuaClass<irr::core::vector2df>::getThis(2);
    irr::core::vector2df    addition = *thisptr + *toAdd;
    Lua::LuaClass<irr::core::vector2df> torepush(addition);

    torepush.dontDelete();
    return 1;
}

int LuaVector2::equal(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    irr::core::vector2df    *cmp = Lua::LuaClass<irr::core::vector2df>::getThis(2);

    lua_pushboolean(state, *thisptr == *cmp);
    return 1;
}