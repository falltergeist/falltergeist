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