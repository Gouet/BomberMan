//
// Created by gaspar_q on 6/2/16.
//

#ifndef CPP_INDIE_STUDIO_LUAVECTOR2_HPP
#define CPP_INDIE_STUDIO_LUAVECTOR2_HPP

# include "LuaClass.hpp"

class LuaVector2
{
public:
    static int createPos(lua_State *state);

    static int getX(lua_State *state);

    static int getY(lua_State *state);

    static int setX(lua_State *state);

    static int setY(lua_State *state);

    static int mul(lua_State *state);

    static int add(lua_State *state);

    static int equal(lua_State *state);
};

#endif //CPP_INDIE_STUDIO_LUAVECTOR2_HPP
