#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>
#include <SDL_image.h>
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
#include "../UI/TileMap.h"

namespace  Falltergeist
{
    namespace UI
    {
        using Point = Graphics::Point;
        using Rect = Graphics::Rect;
        using Size = Graphics::Size;

        TileMap::TileMap(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);
        }

        TileMap::~TileMap()
        {
        }

        void TileMap::init()
        {
            std::vector<unsigned int> numbers;

            std::vector<glm::vec2> vertices;
            std::vector<glm::vec2> UV;

            uint32_t maxW = Game::Game::getInstance()->renderer()->maxTextureSize() / 80;
            uint32_t maxH = Game::Game::getInstance()->renderer()->maxTextureSize() / 36;
            _tilesPerAtlas = maxW*maxH;

            logger->info() << "[GAME] Tilemap tiles " << _tiles.size() << std::endl;

            for (auto& it : _tiles)
            {
                auto& tile = it.second;

                auto position = std::find(numbers.begin(), numbers.end(), tile->number());
                if (position == numbers.end())
                {
                    tile->setIndex(static_cast<unsigned>(numbers.size()));
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
                float vx = static_cast<float>(tile->position().x());
                float vy = static_cast<float>(tile->position().y());
                float vw = static_cast<float>(vx + 80.0);
                float vh = static_cast<float>(vy + 36.0);

                vertices.push_back(glm::vec2(vx, vy));
                vertices.push_back(glm::vec2(vw, vy));
                vertices.push_back(glm::vec2(vx, vh));
                vertices.push_back(glm::vec2(vw, vh));

                //push tilecoords
                uint32_t tIndex = tile->index() % _tilesPerAtlas;

                float x = (float)((tIndex % maxW) * 80);
                float fx = x / (float)Game::Game::getInstance()->renderer()->maxTextureSize();

                float y = (float)((tIndex / maxW) * 36);
                float fy = y / (float)Game::Game::getInstance()->renderer()->maxTextureSize();

                float w = static_cast<float>(x + 80.0) / Game::Game::getInstance()->renderer()->maxTextureSize();
                float h = static_cast<float>(y + 36.0) / Game::Game::getInstance()->renderer()->maxTextureSize();

                UV.push_back(glm::vec2(fx, fy));
                UV.push_back(glm::vec2(w, fy));
                UV.push_back(glm::vec2(fx, h));
                UV.push_back(glm::vec2(w, h));

            }

            // Can be empty if f.e. there is no roof on location
            if (vertices.empty() || UV.empty()) {
                _tilemap = nullptr;
            } else {
                _tilemap = std::make_unique<Graphics::Tilemap>(vertices, UV);
            }

            logger->info() << "[GAME] Tilemap uniq tiles " << numbers.size() << std::endl;

            _atlases = (uint32_t)std::ceil((float)numbers.size() / (float)_tilesPerAtlas);
            logger->info() << "[GAME] Tilemap atlases " << _atlases << std::endl;

            auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");

            for (uint8_t i = 0; i < _atlases; i++)
            {
                SDL_Surface* tmp = SDL_CreateRGBSurface(0, Game::Game::getInstance()->renderer()->maxTextureSize(), Game::Game::getInstance()->renderer()->maxTextureSize(), 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
                SDL_SetSurfaceBlendMode(tmp, SDL_BLENDMODE_NONE);
                for (unsigned int j = _tilesPerAtlas*i; j < std::min((uint32_t)numbers.size(), (uint32_t)_tilesPerAtlas*(i + 1)); ++j)
                {
                    auto frm = ResourceManager::getInstance()->frmFileType("art/tiles/" + tilesLst->strings()->at(numbers.at(j)));

                    SDL_Surface* tileSurf = SDL_CreateRGBSurfaceFrom(frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")), 80, 36, 32, 80 * 4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
                    SDL_SetSurfaceBlendMode(tileSurf, SDL_BLENDMODE_NONE);
                    int x = (j % maxW) * 80;
                    int y = (j / maxW) * 36;
                    SDL_Rect srcrect = { 0,0,80,36 };
                    SDL_Rect rect = { x,y,80,36 };
                    SDL_BlitSurface(tileSurf, &srcrect, tmp, &rect);
                    SDL_FreeSurface(tileSurf);
                }
                //push new atlas
                if (_tilemap != nullptr) {
                    _tilemap->addTexture(tmp);
                }
                //IMG_SavePNG(tmp, "text.png");
                SDL_FreeSurface(tmp);
            }
        }

        void TileMap::render()
        {
            if (_tilemap == nullptr) {
                return;
            }

            auto camera = Game::Game::getInstance()->locationState()->camera();
            std::vector<std::vector<GLuint>> indexes;
            for (uint8_t i = 0; i < _atlases; i++)
            {
                indexes.push_back(std::vector<GLuint>());
            }
            int cnt = 0;

            auto topLeft = camera->topLeft();
            auto size = camera->size();
            for (auto& it : _tiles)
            {
                auto& tile = it.second;
                const Size tileSize = Size(80, 36);
                if (tile->enabled() && Rect::intersects(tile->position(), tileSize, topLeft, size))
                {
                    uint32_t aIndex = tile->index() / _tilesPerAtlas;
                    indexes.at(aIndex).push_back(cnt * 4);
                    indexes.at(aIndex).push_back(cnt * 4 + 1);
                    indexes.at(aIndex).push_back(cnt * 4 + 2);
                    indexes.at(aIndex).push_back(cnt * 4 + 3);
                    indexes.at(aIndex).push_back(cnt * 4 + 2);
                    indexes.at(aIndex).push_back(cnt * 4 + 1);
                }
                cnt++;
            }

            for (uint32_t i = 0; i < _atlases; i++)
            {
                //render atlas with indexes->at(atlasIndex)
                if (indexes.at(i).empty()) {
                    continue;
                }
                _tilemap->render(topLeft, indexes.at(i), i);
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
            for (auto& tile : _tiles)
            {
                tile.second->enable();
            }

        }

        std::map<unsigned int, std::unique_ptr<Tile>> &TileMap::tiles()
        {
            return _tiles;
        }

        void TileMap::disable(unsigned int num)
        {
            int x = num % 100;
            int y = num / 100;
            _floodDisable(x, y);
        }

        void TileMap::_floodDisable(int x, int y)
        {
            // TODO: this is basic 4-way floodfill
            // maybe better replace it with scanlines or QuickFill
            int num = y * 100 + x;
            if (_tiles.count(num) && _tiles.at(num)->enabled())
            {
                _tiles.at(num)->disable();
                _floodDisable(x + 1, y);
                _floodDisable(x - 1, y);
                _floodDisable(x, y + 1);
                _floodDisable(x, y - 1);
            }
        }

        bool TileMap::opaque(const Graphics::Point &pos)
        {
            auto camera = Game::Game::getInstance()->locationState()->camera();

            auto tilesLst = ResourceManager::getInstance()->lstFileType("art/tiles/tiles.lst");
            for (auto& it : _tiles)
            {
                auto& tile = it.second;
                const Size tileSize = Size(80, 36);
                if (tile->enabled() && Rect::inRect(pos + camera->topLeft(), tile->position(), tileSize))
                {
                    auto frm = ResourceManager::getInstance()->frmFileType("art/tiles/" + tilesLst->strings()->at(tile->number()));
                    auto& mask = frm->mask(ResourceManager::getInstance()->palFileType("color.pal"));
                    auto position = pos - tile->position() + camera->topLeft() + Point(1, 1);

                    if ((position.y() * 80 + position.x()) > 0 && ((unsigned)(position.y() * 80 + position.x()) < mask.size()))
                    {
                        if (mask.at(position.y() * 80 + position.x()))
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }
}
