#pragma once

#include <map>
#include <memory>
#include "../Graphics/Point.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../ILogger.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture;
        class Tilemap;
    }
    namespace UI
    {
        using Graphics::Point;
        using Graphics::Rect;

        class Tile;

        class TileMap
        {
            public:
                TileMap(std::shared_ptr<ILogger> logger);
                ~TileMap();

                std::map<unsigned int, std::unique_ptr<Tile>>& tiles();
                void render();
                void init();
                void setInside(bool inside);
                bool inside();
                void enableAll();
                void disable(unsigned int num);

                // Tests if there is a non-transparent pixel at the given point.
                bool opaque(const Point& pos);

            private:
                std::shared_ptr<ILogger> logger;
                std::map<unsigned int, std::unique_ptr<Tile>> _tiles;
                uint32_t _tilesPerAtlas;
                std::unique_ptr<Graphics::Tilemap> _tilemap;
                uint32_t _atlases;
                bool _inside = false;
                void _floodDisable(int x, int y);
        };
    }
}
