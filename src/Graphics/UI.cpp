/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Game/DudeObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Graphics/UI.h"
#include "../LocationCamera.h"
#include "../Lua/Script.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

// Third party includes

namespace Falltergeist
{

UI::UI(int x, int y)
{
    _x = x;
    _y = y;
}

UI::~UI()
{
    // Delete texture only if it wasn't allocated by Resource Manager
    if (_texture)
    {
        bool found = false;
        for (auto it = ResourceManager::textures()->begin(); it != ResourceManager::textures()->end(); ++it)
        {
            if (it->second == _texture)
            {
                found = true;
                break;
            }
        }
        if (!found) delete _texture;
    }
}

void UI::export_to_lua_script(Lua::Script* script)
{
    luabridge::getGlobalNamespace(script->luaState())
        .beginNamespace("game")
            .beginNamespace("ui")
                .beginClass<UI>("UI")
                    //.addProperty("x", &UI::x, &UI::setX)
                    //.addProperty("y", &UI::y, &UI::setY)
                .endClass()
            .endNamespace()
        .endNamespace();
}

int UI::x() const
{
    return _x + _xOffset;
}

void UI::setX(int value)
{
    _x = value;
}

int UI::y() const
{
    return _y + _yOffset;
}

void UI::setY(int value)
{
    _y = value;
}

Texture* UI::texture()
{
    return _texture;
}

void UI::setTexture(Texture* texture)
{
    _texture = texture;
}

void UI::think()
{
}

void UI::render(bool eggTransparency)
{

    if (eggTransparency)
    {
        auto dude = Game::getInstance()->player();

        if (!dude || !Game::getInstance()->locationState())
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();

        int egg_x = dude->hexagon()->x() - camera->x() - 63 + dude->ui()->xOffset();
        int egg_y = dude->hexagon()->y() - camera->y() - 78 + dude->ui()->yOffset();

        int egg_dx = x() - egg_x;
        int egg_dy = y() - egg_y;

        auto egg = ResourceManager::texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { egg_x, egg_y, (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { x(), y(), (int)texture()->width(), (int)texture()->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
            return;
        }

        if (!_tmptex) _tmptex = new Texture(texture()->width(),texture()->height());
        texture()->copyTo(_tmptex);

        _tmptex->blitWithAlpha(egg, egg_dx, egg_dy);
        Game::getInstance()->renderer()->drawTexture(_tmptex, x(), y());
    }
    else
    {
        Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
    }



}

void UI::setVisible(bool value)
{
    _visible = value;
}

bool UI::visible()
{
    return _visible;
}

int UI::xOffset()
{
    return _xOffset;
}

void UI::setXOffset(int xOffset)
{
    _xOffset = xOffset;
}

int UI::yOffset()
{
    return _yOffset;
}

void UI::setYOffset(int yOffset)
{
    _yOffset = yOffset;
}

unsigned int UI::width()
{
    if (!texture()) return 0;
    return texture()->width();
}

unsigned int UI::height()
{
    if (!texture()) return 0;
    return texture()->height();
}

unsigned int UI::pixel(unsigned int x, unsigned int y)
{
    return texture() ? texture()->pixel(x, y) : 0;
}

}
