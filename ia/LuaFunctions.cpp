//
// Created by gaspar_q on 5/21/16.
//

#include "LuaClass.hpp"

/**
 * \brief Function which will initialise the lua library and return the apropriate state
 * \param toset The lua state to set if you want to change the singleton
 * \return The pointer on the singleton that represent a lua state
 */
lua_State *Lua::acquireState(lua_State *toset, bool set)
{
    static lua_State *state = NULL;

    if (!set && state == NULL)
    {
        state = luaL_newstate();
        luaL_openlibs(state);
    }
    else if (set)
    {
        if (toset == NULL)
            lua_close(state);
        state = toset;
    }
    return (state);
}

/**
 * \brief Polymorphism on no argument
 */
int Lua::pushVar(void)
{
    return 0;
}

/**
 * \brief Polymorphism on integer argument
 * \param topush The argument to push
 */
int Lua::pushVar(int topush)
{
    lua_pushinteger(Lua::acquireState(), static_cast<lua_Integer >(topush));
    return 0;
}

/**
 * \brief Polymorphism on double argument
 * \param topush The argument to push
 */
int Lua::pushVar(double topush)
{
    lua_pushnumber(Lua::acquireState(), topush);
    return 0;
}

/**
 * \brief Polymorphism on boolean argument
 * \param topush The argument to push
 */
int Lua::pushVar(bool topush)
{
    lua_pushboolean(Lua::acquireState(), topush);
    return 0;
};

/**
 * \brief Polymorphism on string argument
 * \param topush The argument to push
 */
int Lua::pushVar(const char *topush)
{
    lua_pushstring(Lua::acquireState(), topush);
    return 0;
}