//
// Created by gaspar_q on 6/4/16.
//

#include "LuaScript.hpp"

Lua::LuaScript::LuaScript()
{
    state = luaL_newstate();
}

Lua::LuaScript::LuaScript(lua_State *state) :
    state(state)
{
}

Lua::LuaScript::LuaScript(const Lua::LuaScript &script)
{
    *this = script;
}

Lua::LuaScript::~LuaScript()
{
    lua_close(state);
}

Lua::LuaScript &Lua::LuaScript::operator=(const Lua::LuaScript &script)
{
    state = script.state;
    registeredClasses = script.registeredClasses;
    return *this;
}

lua_State *Lua::LuaScript::operator*(void)
{
    return state;
}

int Lua::LuaScript::GetInteger(int rank) const
{
    return luaL_checkinteger(state, rank);
}

/**
 * \brief Polymorphism on no argument
 */
int Lua::LuaScript::pushVar(lua_State *state)
{
    return 0;
}

/**
 * \brief Polymorphism on integer argument
 * \param topush The argument to push
 */
int Lua::LuaScript::pushVar(lua_State *state, int topush)
{
    lua_pushinteger(state, static_cast<lua_Integer >(topush));
    return 0;
}

/**
 * \brief Polymorphism on double argument
 * \param topush The argument to push
 */
int Lua::LuaScript::pushVar(lua_State *state, double topush)
{
    lua_pushnumber(state, topush);
    return 0;
}

/**
 * \brief Polymorphism on boolean argument
 * \param topush The argument to push
 */
int Lua::LuaScript::pushVar(lua_State *state, bool topush)
{
    lua_pushboolean(state, topush);
    return 0;
};

/**
 * \brief Polymorphism on string argument
 * \param topush The argument to push
 */
int Lua::LuaScript::pushVar(lua_State *state, const char *topush)
{
    lua_pushstring(state, topush);
    return 0;
}