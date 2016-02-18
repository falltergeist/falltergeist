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
#include <SDL_image.h>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Format/Lst/File.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Tilemap.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../Point.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Tile.h"

// Thrird party includes

namespace  Falltergeist
{
namespace UI
{

using namespace Base;

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

    for (auto& tile : _tiles)
    {
        // push vertices
        std::cout << (float)(tile->position().x()) << " : " << (float)(tile->position().y()) << std::endl;
//        vertices.push_back(glm::vec2(0.0,0.0));
//        vertices.push_back(glm::vec2(80.0,0.0));
//        vertices.push_back(glm::vec2(0.0,36.0));

        //double vx = tile->position().x() - 4560.0;
        //double vy = tile->position().y() - 2016.0;
        double vx = 4560.0;
        double vy = 2016.0;
        double vw = 80.0;
        double vh = 36.0;

        vertices.push_back(glm::vec2(vx, vy));
        vertices.push_back( glm::vec2(vx+vw, vy) );
        vertices.push_back(glm::vec2(vx, vy+vh));
        vertices.push_back(glm::vec2(vx+vw, vy+vh));


/*        vertices.push_back(glm::vec2(0.0,0.0));
        vertices.push_back(glm::vec2(80.0,0.0));
        vertices.push_back(glm::vec2(0.0,36.0));
        vertices.push_back(glm::vec2(80.0,36.0));
*/


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
        //push tilecoords
        uint32_t tIndex = tile->index() % _tilesPerAtlas;

        float x = (tIndex % maxW) * 80;
        float fx = x / (float)Game::getInstance()->renderer()->maxTextureSize();

        float y = (tIndex / maxW) * 36;
        float fy = y / (float)Game::getInstance()->renderer()->maxTextureSize();

        float w = (fx+80.f) / (float)Game::getInstance()->renderer()->maxTextureSize();
        float h = (fy+36.f) / (float)Game::getInstance()->renderer()->maxTextureSize();

        UV.push_back(glm::vec2(x,y));
        UV.push_back(glm::vec2(w,y));
        UV.push_back(glm::vec2(x,h));
        UV.push_back(glm::vec2(w,h));

    }

    _tilemap = make_unique<Graphics::Tilemap>(vertices, UV);

    Logger::info("GAME") << "Tilemap uniq tiles " << numbers.size() << std::endl;

    _atlases = (uint32_t)std::ceil((float)numbers.size()/(float)_tilesPerAtlas);
    Logger::info("GAME") << "Tilemap atlases " << _atlases << std::endl;

    auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");

    for (uint8_t i=0;i<_atlases;i++)
    {
        SDL_Surface* tmp = SDL_CreateRGBSurface(0,Game::getInstance()->renderer()->maxTextureSize(), Game::getInstance()->renderer()->maxTextureSize(), 32, 0,0,0,0);
        for (unsigned int j = _tilesPerAtlas*i; j < std::min((uint32_t)numbers.size(), (uint32_t)_tilesPerAtlas*(i+1)); ++j)
        {
            auto frm = ResourceManager::getInstance()->frmFileType("art/tiles/" + tilesLst->strings()->at(numbers.at(j)));

            SDL_Surface* tileSurf = SDL_CreateRGBSurfaceFrom(frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")), 80, 36, 32, 80*4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
            int x = (j % maxW) * 80;
            int y = (j / maxW) * 36;
            SDL_Rect rect = {x,y,80,36};
            SDL_BlitSurface(tileSurf,NULL,tmp,&rect);
            SDL_FreeSurface(tileSurf);
        }
        //push new atlas
        _tilemap->addTexture(tmp);
        SDL_FreeSurface(tmp);
    }

    Logger::info("GAME") << "Tilemap generated in " << (SDL_GetTicks() - ticks) << std::endl;
}

TileMap::~TileMap()
{
}

std::vector<std::unique_ptr<Tile>>& TileMap::tiles()
{
    return _tiles;
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

    for (auto& tile : _tiles)
    {
        const Size tileSize = Size(80, 36);
        if (Rect::intersects(tile->position(), tileSize, camera->topLeft(), camera->size()))
        {
            std::cout << "t: " << tile->position().x() << " : " << tile->position().y() << std::endl;
            std::cout << "c: " << camera->topLeft().x() << " : " << camera->topLeft().y() << std::endl;
            //Point positionOnScreen = tile->position() - camera->topLeft();
            //std::cout << "p: " << positionOnScreen.x() << " : " << positionOnScreen.y() << std::endl;
            uint32_t aIndex = tile->index() / _tilesPerAtlas;
            //std::cout << "aIndex: " << aIndex << " vsize: " << indexes.size();
            indexes.at(aIndex).push_back(cnt*4);
            indexes.at(aIndex).push_back(cnt*4+1);
            indexes.at(aIndex).push_back(cnt*4+2);
            indexes.at(aIndex).push_back(cnt*4+3);
            indexes.at(aIndex).push_back(cnt*4+2);
            indexes.at(aIndex).push_back(cnt*4+1);

            //Point positionOnScreen = tile->position() - camera->topLeft();
        }
        cnt++;
    }

    for (uint32_t i = 0; i< _atlases; i++)
    {
        //render atlas with indexes->at(atlasIndex)
        _tilemap.get()->render(camera->topLeft(), indexes.at(i), i);

    }

}

}
}
