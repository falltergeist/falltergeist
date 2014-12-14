/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// Falltergeist includes
#include "WallObject.h"
#include "Game.h"
#include "DudeObject.h"
#include "../PathFinding/Hexagon.h"
#include "../State/Location.h"
#include "../Graphics/ActiveUI.h"
#include "../Graphics/Renderer.h"
#include "../LocationCamera.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameWallObject::GameWallObject() : GameObject()
{
    _type = TYPE_WALL;
}

GameWallObject::~GameWallObject()
{
}

void GameWallObject::render()
{
    if (!_ui) return;

    auto game = Game::getInstance();
    auto dude = game->player();
    auto hex = dude->hexagon();

    int dx = (hexagon()->number() % 200) - (hex->number() % 200);
    int dy = (hexagon()->number() / 200) - (hex->number() / 200);

    _transparent = false;
    switch (_lightOrientation)
    {
        case ORIENTATION_NS:
            if ((dx>=0 && dx<=3 && dy>=-3 && dy<=3))
                _transparent = true;
            break;
        case ORIENTATION_EW:
        case ORIENTATION_EC:
        case ORIENTATION_SC:
            if ((dx>=-3 && dx<=3 && dy>=0 && dy<=3))
                _transparent = true;
            break;
    }

    if (_transparent)
    {
        auto camera = game->locationState()->camera();
        _ui->setX(hexagon()->x() - camera->x() - std::floor(static_cast<double>(_ui->width())/2));
        _ui->setY(hexagon()->y() - camera->y() - _ui->height());

        setInRender(false);

        if (_ui->x() + (int)_ui->width() < 0) return;
        if (_ui->x() > (int)camera->width()) return;
        if (_ui->y() + (int)_ui->height() < 0) return;
        if (_ui->y() > (int)camera->height()) return;

        setInRender(true);
        if (!_tmptex) _tmptex = new Texture(_ui->texture()->width(),_ui->texture()->height());
        _ui->texture()->copyTo(_tmptex);

        int egg_x = hex->x() - camera->x() - 63;
        int egg_y = hex->y() - camera->y() - 98;
        int egg_dx = _ui->x() - egg_x;
        int egg_dy = _ui->y() - egg_y;

        for (unsigned x =0;x<_ui->texture()->width();x++)
        {
            for (unsigned y =0;y<_ui->texture()->height();y++)
            {
                if (x+egg_dx >= game->renderer()->egg()->width()) continue;
                if (y+egg_dy >= game->renderer()->egg()->height()) continue;
                if (x+egg_dx < 0) continue;
                if (y+egg_dy < 0) continue;
                _tmptex->setPixel(x,y, _tmptex->pixel(x,y) & game->renderer()->egg()->pixel(x+egg_dx, y+egg_dy));
            }
        }
        game->renderer()->drawTexture(_tmptex, _ui->x(),_ui->y());
    }
    else
    {
        GameObject::render();
    }
}

}
}
