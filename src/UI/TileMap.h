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

#ifndef FALLTERGEIST_UI_TILEMAP_H
#define FALLTERGEIST_UI_TILEMAP_H

// C++ standard includes
#include <vector>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Graphics
{
    class Texture;
}
namespace UI
{

class Tile;

class TileMap
{
public:
    TileMap();
    ~TileMap();

    std::vector<std::unique_ptr<Tile>>& tiles();
    void render();

protected:
    unsigned int _square = 0;
    std::unique_ptr<Graphics::Texture> _texture = nullptr;
    std::vector<std::unique_ptr<Tile>> _tiles;
    void _generateTexture();

};

}
}
#endif // FALLTERGEIST_UI_TILEMAP_H
