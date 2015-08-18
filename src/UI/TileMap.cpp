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

// Related headers
#include "../UI/TileMap.h"

// C++ standard includes
#include <algorithm>
#include <cmath>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../LocationCamera.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Tile.h"

// Thrird party includes

namespace  Falltergeist
{
namespace UI
{

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
    delete _texture;
}

std::vector<Tile*>* TileMap::tiles()
{
    return &_tiles;
}

void TileMap::render()
{
    if (!_texture) _generateTexture();

    auto camera = Game::getInstance()->locationState()->camera();
    auto renderer = Game::getInstance()->renderer();

    for (auto tile : _tiles)
    {

        if (tile->x() + 80 < (int)camera->x()) continue;
        if (tile->y() + 36 < (int)camera->y()) continue;
        if (tile->x() - (int)camera->width()  > (int)camera->x()) continue;
        if (tile->y() - (int)camera->height() > (int)camera->y()) continue;

        auto x = tile->x() - camera->x();
        auto y = tile->y() - camera->y();
        auto sx = (tile->index() % _square) * 80;
        auto sy = (tile->index() / _square) * 36;

        renderer->drawTexture(_texture, x, y, sx, sy, 80, 36);
    }
}

void TileMap::_generateTexture()
{
    std::vector<unsigned int> numbers;
    for (auto tile : _tiles)
    {
        auto position = std::find(numbers.begin(), numbers.end(), tile->number());
        if ( position == numbers.end())
        {
            tile->setIndex(numbers.size());
            numbers.push_back(tile->number());
        }
        else
        {
            for (unsigned int i = 0; i != numbers.size(); ++i)
            {
                if (numbers.at(i) == tile->number())
                {
                    tile->setIndex(i);
                    break;
                }
            }
        }
    }

    _square = std::ceil(std::sqrt(numbers.size()));

    _texture = new Texture(_square*80, _square*36);

    auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");
    for (unsigned int i = 0; i != numbers.size(); ++i)
    {
        auto texture = ResourceManager::getInstance()->texture("art/tiles/" + tilesLst->strings()->at(numbers.at(i)));
        unsigned int x = (i%_square)*80;
        unsigned int y = (i/_square)*36;
        texture->copyTo(_texture, x, y);
    }
}

}
}
