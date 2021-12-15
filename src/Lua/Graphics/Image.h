#pragma once

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
}
#include "../../Graphics/Sprite.h"

namespace Falltergeist::Lua::Graphics {
            struct Image final {
                static int create(lua_State* L) {
                    std::cout << "Image::create" << std::endl;
                    const char* filename = lua_tostring(L, -1);
                    auto image = new UI::Image(std::make_unique<Falltergeist::Graphics::Sprite>(filename));
                    lua_pushlightuserdata(L, image);
                    luaL_setmetatable(L, "ImageMeta");
                    return 1;
                }

                static int metaIndex(lua_State* L) {
                    assert(lua_isuserdata(L, -2));
                    auto image = (UI::Image*) lua_touserdata(L, -2);
                    assert(lua_isstring(L, -1));
                    const char* member = lua_tostring(L, -1);
                    if (strcmp(member, "x") == 0) {
                        lua_pushnumber(L, (lua_Number) image->position().x());
                        return 1;
                    }
                    if (strcmp(member, "y") == 0) {
                        lua_pushnumber(L, (lua_Number) image->position().y());
                        return 1;
                    }

                    lua_getglobal(L, "Image");
                    assert(lua_istable(L, -1));
                    lua_pushstring(L, member);
                    lua_rawget(L, -2);
                    return 1;
                }

                static int metaNewIndex(lua_State* L) {
                    assert(lua_isuserdata(L, -3));
                    auto image = (UI::Image*) lua_touserdata(L, -3);
                    assert(lua_isstring(L, -2));
                    const char* member = lua_tostring(L, -2);
                    std::cout << member << std::endl;
                    if (strcmp(member, "x") == 0) {
                        lua_Number x = lua_tonumber(L, -1);
                        std::cout << (int) x << std::endl;
                        image->setX((int) x);
                        return 0;
                    }

                    if (strcmp(member, "y") == 0) {
                        lua_Number y = lua_tonumber(L, -1);
                        std::cout << (int) y << std::endl;
                        image->setY((int) y);
                        return 0;
                    }

                    assert(false); // custom user data is not supported yet
                }

                static int setX(lua_State* L) {
                    std::cout << "Image::setX" << std::endl;
                    assert(lua_isuserdata(L, -2));
                    auto image = (UI::Image*)lua_touserdata(L, -2);
                    assert(lua_isnumber(L, -1));
                    lua_Number x = lua_tonumber(L, -1);
                    image->setX((int) x);
                    return 0;
                };

                static int setY(lua_State* L) {
                    std::cout << "Image::setY" << std::endl;
                    assert(lua_isuserdata(L, -2));
                    auto image = (UI::Image*)lua_touserdata(L, -2);
                    assert(lua_isnumber(L, -1));
                    lua_Number y = lua_tonumber(L, -1);
                    image->setY((int) y);
                    return 0;
                };
            };
        }