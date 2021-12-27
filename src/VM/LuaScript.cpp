#include "../VM/LuaScript.h"
#include <iostream>
#include <functional>
#include "../ResourceManager.h"
#include "../UI/Image.h"
#include <cassert>
#include "../Lua/Graphics/Image.h"
#include "../Lua/SceneManager/Scene.h"
#include "../Lua/EventHandlerContext.h"
#include <filesystem>
#include "../Exception.h"
#include "../Lua/VFSModuleLoader.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace Falltergeist {
    namespace VM {



        LuaScript::LuaScript(const std::string& script, State::State* state) {
            luaState = luaL_newstate();
            auto L = luaState;
            luaL_openlibs(luaState);

            _moduleLoaders.emplace_back(std::make_unique<Lua::VFSModuleLoader>(ResourceManager::getInstance()->vfs()));


            // set custom module loader
            {
                lua_getglobal(L, LUA_LOADLIBNAME);
                assert(lua_istable(L, -1));
                lua_getfield(L, -1, "searchers");
                assert(lua_istable(L, -1));
                lua_pushlightuserdata(L, this);
                lua_pushcclosure(L, [](lua_State* L)->int {
                    auto script = (LuaScript*)lua_touserdata(L, lua_upvalueindex(1));
                    const char *moduleName = luaL_checkstring(L, -1);
                    for (auto& loader : script->_moduleLoaders) {
                        if (loader->loadModule(moduleName, L)) {
                            return 1;
                        }
                    }

                    return 0;
                }, 1);
                lua_rawseti(L, -2, 2);
            }


//            std::string pathToModules = std::string(std::filesystem::current_path()) + "/scripts/?.lua";
//
//            lua_getglobal(luaState, "package" );
//            lua_pushstring(luaState, pathToModules.c_str() );
//            lua_setfield(luaState, -2, "path" );
//            lua_pop(luaState, 1 );
//
//            this->state = state;
//
//            auto AddEventListener = [](lua_State* L)->int {
//                std::cout << "AddEventListener" << std::endl;
//
//
//                assert(lua_isuserdata(L, -3));
//                auto image = (UI::Image*)lua_touserdata(L, -3);
//                assert(lua_isstring(L, -2));
//                const char* eventName = lua_tostring(L, -2);
//                assert(lua_isfunction(L, -1));
//                int function_index = luaL_ref(L, LUA_REGISTRYINDEX);
//                std::cout << function_index << std::endl;
//                lua_pushvalue(L, -2);
//                assert(lua_isuserdata(L, -1));
//                int image_index = luaL_ref(L, LUA_REGISTRYINDEX);
//                std::cout << image_index << std::endl;
//                lua_pop(L, 1);
//                Lua::EventHandlerContext eventHandlerContext(image_index,function_index);
//
//                if (strcmp(eventName, "mouse_down") == 0) {
//                    image->mouseDownHandler().add([L, eventHandlerContext](Event::Mouse* event)->void {
//                        std::cout << "handler invoked" << std::endl;
//                        lua_rawgeti(L, LUA_REGISTRYINDEX, eventHandlerContext.handlerIndex);
//                        assert(lua_isfunction(L, -1));
//
//                        lua_newtable(L);
//
//                        lua_pushstring(L, "name");
//                        lua_pushstring(L, "click");
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "x");
//                        lua_pushnumber(L, event->position().x());
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "y");
//                        lua_pushnumber(L, event->position().y());
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "target");
//                        lua_rawgeti(L, LUA_REGISTRYINDEX, eventHandlerContext.targetIndex);
//                        lua_settable(L, -3);
//
//                        lua_pcall(L, 1, 0, 0);
//                    });
//                }
//
//                if (strcmp(eventName, "mouse_up") == 0) {
//                    image->mouseUpHandler().add([L, eventHandlerContext](Event::Mouse* event)->void {
//                        std::cout << "handler invoked" << std::endl;
//                        lua_rawgeti(L, LUA_REGISTRYINDEX, eventHandlerContext.handlerIndex);
//                        assert(lua_isfunction(L, -1));
//
//                        lua_newtable(L);
//
//                        lua_pushstring(L, "name");
//                        lua_pushstring(L, "click");
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "x");
//                        lua_pushnumber(L, event->position().x());
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "y");
//                        lua_pushnumber(L, event->position().y());
//                        lua_settable(L, -3);
//
//                        lua_pushstring(L, "target");
//                        lua_rawgeti(L, LUA_REGISTRYINDEX, eventHandlerContext.targetIndex);
//                        lua_settable(L, -3);
//
//                        lua_pcall(L, 1, 0, 0);
//                    });
//                }
//
//                return 0;
//            };
//
//            lua_newtable(luaState);
//            lua_pushstring(luaState, "addEventListener");
//            lua_pushcfunction(luaState, AddEventListener);
//            lua_settable(luaState, -3);
//            lua_pushstring(luaState, "x");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::setX);
//            lua_settable(luaState, -3);
//            lua_pushstring(luaState, "y");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::setY);
//            lua_settable(luaState, -3);
//            lua_pushstring(luaState, "show");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::show);
//            lua_settable(luaState, -3);
//            lua_pushstring(luaState, "hide");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::hide);
//            lua_settable(luaState, -3);
//            lua_setglobal(luaState, "Image");
//
//            luaL_newmetatable(luaState, "ImageMeta");
//            lua_pushstring(luaState, "__index");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::metaIndex);
//            lua_settable(luaState, -3);
//            lua_pushstring(luaState, "__newindex");
//            lua_pushcfunction(luaState, Lua::Graphics::Image::metaNewIndex);
//            lua_settable(luaState, -3);
//
//            lua_newtable(luaState);
//            lua_pushstring(luaState, "newImage");
//            lua_pushcclosure(luaState, Lua::Graphics::Image::create, 0);
//            lua_settable(luaState, -3);
//            lua_setglobal(luaState, "graphics");
//
//            Lua::SceneManager::Scene::addToLua(luaState, state);

            if (luaL_loadstring(luaState, script.c_str()) != LUA_OK) {
                std::cout << "can not load script " << std::endl;
                throw 1;
            }
        }

        void LuaScript::execute() {
            if (lua_pcall(luaState, 0, 0, 0) != LUA_OK) {
                std::cout << "can not execute script: " << lua_tostring(luaState, -1) << std::endl;
                throw 1;
            }
        }

        LuaScript::~LuaScript() {
            lua_close(luaState);
        }
    }
}
