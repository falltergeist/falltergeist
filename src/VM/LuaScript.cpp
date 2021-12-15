#include "../VM/LuaScript.h"
#include <iostream>
#include <functional>
#include "../Scripting/Lua/Binding/Graphics/Image.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"
#include "assert.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
}

int addEventListener(lua_State *L)
{
    std::cout << "addEventListener" << std::endl;
    return 0;
}

int newImageFunction(lua_State *L)
{
    std::cout << "newImageFunction" << std::endl;
    lua_newtable(L);
    lua_pushstring(L, "addEventListener");
    lua_pushcfunction(L, addEventListener);
    lua_settable(L, -3);
    return 1;
};

namespace Falltergeist {
    namespace VM {

        LuaScript::LuaScript(const std::string &filename, State::State* state) {
            luaState = luaL_newstate();
            luaL_openlibs(luaState);

            this->state = state;

            auto CreateImage = [](lua_State* L)->int {
                std::cout << "CreateImage" << std::endl;
                const char* filename = lua_tostring(L, -1);
                auto image = new UI::Image(std::make_unique<Graphics::Sprite>(filename));
                lua_pushlightuserdata(L, image);
                luaL_setmetatable(L, "ImageMeta");
                return 1;
            };

            auto AddEventListener = [](lua_State* L)->int {
                std::cout << "AddEventListener" << std::endl;
                assert(lua_isuserdata(L, -3));
                auto image = (UI::Image*)lua_touserdata(L, -3);
                assert(lua_isstring(L, -2));
                const char* eventName = lua_tostring(L, -2);
                assert(lua_isfunction(L, -1));
                int function_index = luaL_ref(L, LUA_REGISTRYINDEX);

                image->mouseClickHandler().add([L, function_index](Event::Mouse* event)->void {
                    std::cout << "handler invoked" << std::endl;
                    lua_rawgeti(L, LUA_REGISTRYINDEX, function_index);
                    assert(lua_isfunction(L, -1));
                    lua_pcall(L, 0, 0, 0);
                });
                return 0;
            };

            auto SceneAdd = [](lua_State* L)->int {
                std::cout << "SceneAdd" << std::endl;
                auto state = (State::State*)lua_touserdata(L, lua_upvalueindex(1));
                auto image = (UI::Image*)lua_touserdata(L, -1);
                state->addUI(image);
                return 0;
            };

            lua_newtable(luaState);
            lua_pushstring(luaState, "addEventListener");
            lua_pushcfunction(luaState, AddEventListener);
            lua_settable(luaState, -3);
            lua_setglobal(luaState, "Image");

            luaL_newmetatable(luaState, "ImageMeta");
            lua_pushstring(luaState, "__index");
            lua_getglobal(luaState, "Image");
            lua_settable(luaState, -3);

            lua_newtable(luaState);
            lua_pushstring(luaState, "newImage");
            lua_pushcclosure(luaState, CreateImage, 0);
            lua_settable(luaState, -3);
            lua_setglobal(luaState, "graphics");

            lua_newtable(luaState);
            lua_pushstring(luaState, "add");
            lua_pushlightuserdata(luaState, state);
            lua_pushcclosure(luaState, SceneAdd, 1);
            lua_settable(luaState, -3);
            lua_setglobal(luaState, "scene");

            if (luaL_loadfile(luaState, filename.c_str())) {
                std::cout << "can not load script " << std::endl;
                throw 1;
            }
        }

        void LuaScript::execute() {
            if (lua_pcall(luaState, 0, 0, 0)) {
                std::cout << "can not execute script: " << lua_tostring(luaState, -1) << std::endl;
                throw 1;
            }
        }

        LuaScript::~LuaScript() {
            lua_close(luaState);
        }
    }
}
