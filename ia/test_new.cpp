//
// Created by gaspar_q on 6/4/16.
//

#include "LuaScript.hpp"

class testClass
{
public:
    testClass() :
            toto(false)
    {
        std::cout << "Coucou" << std::endl;
    }

public:
    static int methode(lua_State *)
    {
        std::cout << "La méthode est appelée" << std::endl;
        return 0;
    }

private:
    bool    toto;
};

template <>
const std::string Lua::LuaScriptClass<testClass>::className = "Test";

int main()
{
    Lua::LuaScript  script;
    Lua::LuaHandler handler(*script, "helloworld.lua");
    testClass   testClass1;

    script.RegisterClass<testClass>({
                                            {"meth", testClass::methode}
                                    });
    handler["testuserdata"](&testClass1);
    return 0;
}