//
// Created by gaspar_q on 6/4/16.
//

#ifndef CPP_INDIE_STUDIO_LUASCRIPTCLASS_HPP
#define CPP_INDIE_STUDIO_LUASCRIPTCLASS_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <string.h>

extern "C" {
#include "lua-5.3.2/src/lua.h"
#include "lua-5.3.2/src/lualib.h"
#include "lua-5.3.2/src/lauxlib.h"
}

namespace Lua
{
    /**
     * \brief constants for internal Lua usage
     */
    static const std::string luaPrefix = "luaL_";

    /**
     * \brief Template class that overload a class to be a Lua usable class
     * \param classType the type of the class to overload
     */
    template <typename classType>
    class LuaScriptClass
    {
    public:
        /**
         * \brief When you overload a class you have to specify the class name through this constant
         */
        static const std::string className;

    public:
        /**
         * \brief The principal constructor of a lua class that bind the metatable to the object
         * \param thisptr A pointer on the object to overload
         * \param todelete Tell if the object will be delete on ~LuaScriptClass() call
         */
        LuaScriptClass(lua_State *state, classType *thisptr) :
                userData(NULL),
                thisptr(thisptr),
                todelete(false),
                state(state)
        {
            userData = static_cast<classType **>(lua_newuserdata(state, sizeof(*userData)));
            bindMetatable();
            *userData = thisptr;
        }
        /**
         * \brief An other constructor that will be used like the constructor of the object
         * \param todelete Tells if the object will be delete on ~LuaScriptClass() call
         * \param args The arguments of the constructor of the new object
         */
        template <typename ... Types>
        LuaScriptClass(lua_State *state, Types ... args) :
                LuaScriptClass(state, new classType(args...))
        {
        }
        /**
         * \brief A default constructor like
         * \param todelete Tells if the object will be delete on ~LuaScriptClass() call
         */
        LuaScriptClass(lua_State *state) :
                LuaScriptClass(state, new classType())
        {
        }
        /**
         * \brief A Copy constructor implementation
         * \param ref The object to copy
         */
        LuaScriptClass(lua_State *state, classType const &ref) :
                LuaScriptClass(state, new classType(ref))
        {
        }
        /**
         * \brief The lua class copy constructor
         * \param ref A reference on the object to copy
         */
        LuaScriptClass(LuaScriptClass<classType> const &ref) :
                LuaScriptClass(ref.state, ref.thisptr)
        {
            dontDelete();
        }
        /**
         * \brief The copy operator of a lua class
         * \param ref A reference on the object to copy
         * \return A reference on this pointer
         */
        LuaScriptClass    &operator=(LuaScriptClass<classType> const &ref)
        {
            thisptr = ref.thisptr;
            *userData = thisptr;
            dontDelete();
            return (*this);
        }
        /**
         * \brief overload of referencing operator to get the adress of the real object
         * \return The adress of the real object
         */
        classType   **getUserData()
        {
            return (userData);
        }
        /**
         * \brief Destructor that will delete the object only if the todelete construcor argument have been set to true
         */
        ~LuaScriptClass()
        {
            if (todelete)
                delete(thisptr);
        }
        /**
         * \brief Tells to the class to not detele the object on destruction
         */
        void dontDelete(void)
        {
            todelete = false;
        }
        /**
         * \brief Bind a metatable to the user data
         */
        void bindMetatable(void)
        {
            luaL_getmetatable(state, (luaPrefix + className).c_str());
            lua_setmetatable(state, -2);
        }
        /**
         * \brief Access the reference of the overloaded pointer
         * \return A reference on internal pointer
         */
        classType   &operator*(void)
        {
            return (*thisptr);
        }
        /**
         * \brief Allow the user to access methods on internal pointer
         * \return The internal pointer
         */
        classType   *operator->(void)
        {
            return (thisptr);
        }

    public:
        /**
         * \brief Nested class that will define the metatable of the LuaScriptClass inside Lua
         */
        class LuaPrototype
        {
        public:
            /**
             * \brief The constructor only take a map of symbols to will be registered for the class
             * \param symbols All methods of the object
             */
            LuaPrototype(lua_State *state, std::map<std::string, lua_CFunction> const &symbols = {}) :
                    symbols(symbols),
                    state(state)
            {
            }

        public:
            /**
             * \brief Getter of prototype symbols
             * \return The table of methods of the prototypes
             */
            const std::map<std::string, lua_CFunction>  &getSymbols(void) const
            {
                return (symbols);
            }
            /**
             * \brief Convert the map into a luaL_Reg array needed by luaL_setfuncs
             * \return A unique ptr (for garbage collection) of luaL_Reg[] that can be used for metatable registration
             */
            std::unique_ptr<luaL_Reg[]>    getRegs(void) const
            {
                luaL_Reg    *regs;
                size_t      i = 0;

                regs = new luaL_Reg[symbols.size() + 1];
                for (std::map<std::string, lua_CFunction>::const_iterator it = symbols.begin(), end = symbols.end(); it != end; ++it, ++i)
                {
                    regs[i].func = it->second;
                    regs[i].name = it->first.c_str();
                }
                regs[i].name = NULL, regs[i].func = NULL;
                return (std::unique_ptr<luaL_Reg[]>(regs));
            }
            /**
             * \brief Getter for the lua state of the prototype
             * \return The lua state currently used by the prototype
             */
            const lua_State   *getState(void) const
            {
                return (state);
            }
            /**
             * \brief The access operator for assiging a new function to the prototype
             * \param name The name that will bind the function you will assign
             * \return A reference on the function binded by name
             */
            lua_CFunction &operator[](const std::string &name)
            {
                return (symbols[name]);
            }
            /**
             * \brief A simple getter ultra-const to get the function binded by name
             * \param name The name of the function to get
             * \return The function binded by name
             */
            lua_CFunction const &operator[](const std::string &name) const
            {
                return (symbols.find(name)->second);
            }
            /**
             * \brief Will register the prototype into a lua metatable, it will allow you to use the LuaScriptClass into lua script
             */
            void Register()
            {
                luaL_newmetatable(state, (luaPrefix + className).c_str());
                lua_pushvalue(state, -1);
                lua_setfield(state, -2, "__index");
                luaL_setfuncs(state, &getRegs()[0], 0);
                lua_setglobal(state, className.c_str());
            }

        private:
            std::map<std::string, lua_CFunction>    symbols;
            lua_State *state;
        };
        /**
         * \brief Allows you to get the 'this' pointer when a method is called
         * \param n The correspond to the index of the object to get in the lua stack (1 if you are nice)
         * \return The this arguments if you call it in very first inside the method
         */
        static classType *getThis(lua_State *state, int n = 1)
        {
            return *(classType **)luaL_checkudata(state, n, (luaPrefix + className).c_str());
        }
        /**
         * \brief Allows you to get an integer in the lua stack
         * \param n Correspond to the index on the lua stack
         * \return The integer at n index in the lua stack
         */
        static int getInteger(lua_State *state, int n = 1)
        {
            return luaL_checkinteger(state, n);
        }
        /**
         * \brief An implementation of the most basic constructor for a lua class
         * \return The index of the new instance in the lua stack
         */
        static int defaultConstructor(lua_State *state)
        {
            Lua::LuaScriptClass<classType>   thisptr(state);

            thisptr.dontDelete();
            return (1);
        }
        /**
         * \brief An implementation of the most basic destructor for a lua class
         */
        static int defaultDestructor(lua_State *state)
        {
            classType   *thisptr = getThis(state);

            delete(thisptr);
            return (1);
        }
        /**
         * \brief An implementation of a null destructor for classes you don't want to delete but for garbage collection
         */
        static int destrucNull(lua_State *)
        {
            return (1);
        }

    private:
        classType   **userData;
        classType   *thisptr;
        bool        todelete;

    protected:
        lua_State   *state;
    };
};

#endif //CPP_INDIE_STUDIO_LUASCRIPTCLASS_HPP
