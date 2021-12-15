#pragma once

extern "C" {
    #include "lua.h"
}
#include "../../State/State.h"
#include "../../UI/Image.h"
#include <iostream>

namespace Falltergeist {
    namespace Lua {
        namespace SceneManager {
            struct Scene final {
                static void addToLua(lua_State* L, State::State* state) {
                    lua_newtable(L);
                    lua_pushstring(L, "add");
                    lua_pushlightuserdata(L, state);
                    lua_pushcclosure(L, Scene::add, 1);
                    lua_settable(L, -3);
                    lua_setglobal(L, "scene");
                }

                static int add(lua_State* L) {
                    std::cout << "Scene::add" << std::endl;
                    auto state = (State::State*)lua_touserdata(L, lua_upvalueindex(1));
                    auto image = (UI::Image*)lua_touserdata(L, -1);
                    state->addUI(image);
                    return 0;
                }
            };
        }
    }
}