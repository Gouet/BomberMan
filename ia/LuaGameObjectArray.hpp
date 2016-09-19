//
// Created by gaspar_q on 6/2/16.
//

#ifndef CPP_INDIE_STUDIO_LUAGAMEOBJECTARRAY_HPP
#define CPP_INDIE_STUDIO_LUAGAMEOBJECTARRAY_HPP

# include "LuaClass.hpp"

class LuaGameObjectArray
{
public:
    static int typeAtIndex(lua_State *state);

    static int posAtIndex(lua_State *state);

    static int size(lua_State *state);

    static int hasType(lua_State *state);
};

#endif //CPP_INDIE_STUDIO_LUAGAMEOBJECTARRAY_HPP
