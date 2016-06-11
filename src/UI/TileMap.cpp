/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <vector>
#include <memory>

// Falltergeist includes
#include "../Format/Lst/File.h"
#include "../Game/Game.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Tilemap.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Tile.h"

// Thrird party includes
#include <SDL_image.h>

namespace  Falltergeist
{
namespace UI
{

TileMap::TileMap()
{
}

void TileMap::init()
{
    auto ticks = SDL_GetTicks();
    std::vector<unsigned int> numbers;

    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UV;

    uint32_t maxW = Game::getInstance()->renderer()->maxTextureSize() / 80;
    uint32_t maxH = Game::getInstance()->renderer()->maxTextureSize() / 36;
    _tilesPerAtlas = maxW*maxH;

    Logger::info("GAME") << "Tilemap tiles " << _tiles.size() << std::endl;

    for (auto& it : _tiles)
    {
        auto& tile = it.second;



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

    for (auto& it : _tiles)
    {
        auto& tile = it.second;
        // push vertices
        float vx = tile->position().x();
        float vy = tile->position().y();
        float vw = vx+80.0;
        float vh = vy+36.0;

        vertices.push_back(glm::vec2(vx, vy));
        vertices.push_back( glm::vec2(vw, vy) );
        vertices.push_back(glm::vec2(vx, vh));
        vertices.push_back(glm::vec2(vw, vh));

        //push tilecoords
        uint32_t tIndex = tile->index() % _tilesPerAtlas;

        float x = (float)((tIndex % maxW) * 80);
        float fx = x / (float)Game::getInstance()->renderer()->maxTextureSize();

        float y = (float)((tIndex / maxW) * 36);
        float fy = y / (float)Game::getInstance()->renderer()->maxTextureSize();

        float w = (x+80.0) / (float)Game::getInstance()->renderer()->maxTextureSize();
        float h = (y+36.0) / (float)Game::getInstance()->renderer()->maxTextureSize();

        UV.push_back(glm::vec2(fx,fy));
        UV.push_back(glm::vec2(w,fy));
        UV.push_back(glm::vec2(fx,h));
        UV.push_back(glm::vec2(w,h));

    }

    _tilemap = std::make_unique<Graphics::Tilemap>(vertices, UV);

    Logger::info("GAME") << "Tilemap uniq tiles " << numbers.size() << std::endl;

    _atlases = (uint32_t)std::ceil((float)numbers.size()/(float)_tilesPerAtlas);
    Logger::info("GAME") << "Tilemap atlases " << _atlases << std::endl;

    auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");

    for (uint8_t i=0;i<_atlases;i++)
    {
        SDL_Surface* tmp = SDL_CreateRGBSurface(0,Game::getInstance()->renderer()->maxTextureSize(), Game::getInstance()->renderer()->maxTextureSize(), 32, 0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
        SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);
        for (unsigned int j = _tilesPerAtlas*i; j < std::min((uint32_t)numbers.size(), (uint32_t)_tilesPerAtlas*(i+1)); ++j)
        {
            auto frm = ResourceManager::getInstance()->frmFileType("art/tiles/" + tilesLst->strings()->at(numbers.at(j)));

            SDL_Surface* tileSurf = SDL_CreateRGBSurfaceFrom(frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")), 82, 38, 32, 82*4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
            SDL_SetSurfaceBlendMode(tileSurf, SDL_BLENDMODE_NONE);
            int x = (j % maxW) * 80;
            int y = (j / maxW) * 36;
            SDL_Rect srcrect = {1,1,80,36};
            SDL_Rect rect = {x,y,80,36};
            SDL_BlitSurface(tileSurf,&srcrect,tmp,&rect);
            SDL_FreeSurface(tileSurf);
        }
        //push new atlas
        _tilemap->addTexture(tmp);
        //IMG_SavePNG(tmp, "text.png");
        SDL_FreeSurface(tmp);
    }

    Logger::info("GAME") << "Tilemap generated in " << (SDL_GetTicks() - ticks) << std::endl;
}

TileMap::~TileMap()
{
}

void TileMap::render()
{
    auto camera = Game::getInstance()->locationState()->camera();
    std::vector<std::vector<GLuint>> indexes;
    for (uint8_t i =0; i<_atlases;i++)
    {
        indexes.push_back(std::vector<GLuint>());
    }
    int cnt=0;

    auto topLeft = camera->topLeft();
    auto size = camera->size();
    for (auto& it : _tiles)
    {
        auto& tile = it.second;
        const Size tileSize = Size(80, 36);
        if (tile->enabled() && Rect::intersects(tile->position(), tileSize, topLeft, size))
        {
            uint32_t aIndex = tile->index() / _tilesPerAtlas;
            indexes.at(aIndex).push_back(cnt*4);
            indexes.at(aIndex).push_back(cnt*4+1);
            indexes.at(aIndex).push_back(cnt*4+2);
            indexes.at(aIndex).push_back(cnt*4+3);
            indexes.at(aIndex).push_back(cnt*4+2);
            indexes.at(aIndex).push_back(cnt*4+1);
        }
        cnt++;
    }

    for (uint32_t i = 0; i< _atlases; i++)
    {
        //render atlas with indexes->at(atlasIndex)
        _tilemap.get()->render(topLeft, indexes.at(i), i);

    }

}

void TileMap::setInside(bool inside)
{
    _inside = inside;
}

bool TileMap::inside()
{
    return _inside;
}

void TileMap::enableAll()
{
    for (auto& tile: _tiles)
    {
        tile.second->enable();
    }

}

std::map<unsigned int, std::unique_ptr<Tile>> &TileMap::tiles() {
    return _tiles;
}

void TileMap::disable(unsigned int num)
{
    int x = num % 100;
    int y = num / 100;
    _floodDisable(x,y);
}

void TileMap::_floodDisable(int x, int y)
{
    // TODO: this is basic 4-way floodfill
    // maybe better replace it with scanlines or QuickFill
    int num = y*100+x;
    if (_tiles.count(num) && _tiles.at(num)->enabled())
    {
        _tiles.at(num)->disable();
        _floodDisable(x+1,y);
        _floodDisable(x-1,y);
        _floodDisable(x,y+1);
        _floodDisable(x,y-1);
    }
}

bool TileMap::opaque(const Point &pos)
{
    auto camera = Game::getInstance()->locationState()->camera();


    auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");
    for (auto& it : _tiles)
    {
        auto& tile = it.second;
        const Size tileSize = Size(80, 36);
        if (tile->enabled() && Rect::inRect(pos+camera->topLeft(), tile->position(),tileSize))
        {
            auto frm = ResourceManager::getInstance()->frmFileType("art/tiles/" + tilesLst->strings()->at(tile->number()));
            auto mask = frm->mask(ResourceManager::getInstance()->palFileType("color.pal"));
            auto position = pos-tile->position()+camera->topLeft()+Point(1,1);

            if ((position.y()*82+position.x()) > 0 &&  ((unsigned)(position.y()*82+position.x()) < mask->size())) {
                if (mask->at(position.y()*82+position.x())) return true;
            }
        }
    }
    return false;
}
}
}
