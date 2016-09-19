//
// Created by gaspar_q on 6/4/16.
//

#ifndef CPP_INDIE_STUDIO_LUASCRIPT_HPP
# define CPP_INDIE_STUDIO_LUASCRIPT_HPP

# include "LuaScriptClass.hpp"
# include "LuaHandler.hpp"

namespace Lua
{
    class LuaScript
    {
    public:
        LuaScript();
        LuaScript(lua_State *state);
        LuaScript(LuaScript const &);
        ~LuaScript();
        LuaScript   &operator=(LuaScript const &);

    public:
        template <typename toRegister>
        void RegisterClass(std::map<std::string, lua_CFunction> const &functions = {})
        {
            typename Lua::LuaScriptClass<toRegister>::LuaPrototype(state, functions).Register();
            registeredClasses.push_back(Lua::LuaScriptClass<toRegister>::className);
        }
        template <typename toInstantiate>
        toInstantiate *New(void) const throw(Lua::LuaException)
        {
            if (!IsRegistered<toInstantiate>())
                throw Lua::LuaException("Class " + Lua::LuaScriptClass<toInstantiate>::className + " has not been registered in this script yet");
            return (*Lua::LuaScriptClass<toInstantiate>(state));
        }
        template <typename toCheck>
        bool     IsRegistered(void) const
        {
            return (std::find(registeredClasses.begin(), registeredClasses.end(), Lua::LuaScriptClass<toCheck>::className) != registeredClasses.end());
        }
        template <typename toGet>
        toGet *GetObject(int rank = 1) const
        {
            return Lua::LuaScriptClass<toGet>::getThis(state, rank);
        }
        int GetInteger(int rank = 1) const;

    public:
        static int          pushVar(lua_State *state);
        static int          pushVar(lua_State *state, int topush);
        static int          pushVar(lua_State *state, double topush);
        static int          pushVar(lua_State *state, bool topush);
        static int          pushVar(lua_State *state, const char *topush);

        /**
         * \brief Polymorphism on user data argument. In that case it is recommended to use LuaClass object '&' operator
         * \param topush The argument to push
         */
        template<typename classtype>
        static int          pushVar(lua_State *state, classtype *topush)
        {
            LuaScriptClass<classtype> luaconv(state, topush);

            luaconv.dontDelete();
            return 0;
        }

        template<typename classtype>
        static int          pushVar(lua_State *state, classtype topush)
        {
            LuaScriptClass<classtype> luaconv(state, topush);

            luaconv.dontDelete();
            return 0;
        }

    public:
        lua_State   *operator*(void);

    private:
        lua_State                   *state;
        std::vector<std::string>    registeredClasses;
    };
};

#endif //CPP_INDIE_STUDIO_LUASCRIPT_HPP
