//
// Created by gaspar_q on 6/2/16.
//

#ifndef CPP_INDIE_STUDIO_LUABOMBERMAP_HPP
#define CPP_INDIE_STUDIO_LUABOMBERMAP_HPP

# include "LuaClass.hpp"

class LuaBomberMap
{
public:
    static int objsAtPos(lua_State *state);

    static int getNbOfType(lua_State *state);

    static int getDangerAtPos(lua_State *state);
};

#endif //CPP_INDIE_STUDIO_LUABOMBERMAP_HPP
