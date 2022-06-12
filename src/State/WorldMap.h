#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"
#include "Graphics/TranslucentMask.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
        class Image;
        class ImageButton;
        class ImageList;
    }
    namespace Game
    {
        class WorldMapCity;
    }
    namespace State
    {
        class WorldMap final : public State
        {
            public:
                WorldMap(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~WorldMap() = default;

                void init() override;

                void render() override;

                void handle(Event::Event* event) override;

                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                std::shared_ptr<UI::Image> _panel = nullptr;

                std::shared_ptr<UI::ImageList> _tiles = nullptr;

                std::shared_ptr<UI::ImageButton> _hotspot = nullptr;

                std::vector<std::unique_ptr<Game::WorldMapCity>> _cities;

                std::vector<std::shared_ptr<Graphics::TranslucentMask>> _citySizes;

                // temporary!
                // @todo: move it to other place!
                // coordinates of the player on world map
                unsigned int _worldMapX = 0;

                unsigned int _worldMapY = 0;

                // delta (shift of map to fit to screen)
                signed int _deltaX = 0;

                signed int _deltaY = 0;

                // fallout2 map size: 4x5 tiles, so texture size is 1400x1500
                unsigned int _tilesNumberX = 4; // fallout 2 tiles by X

                unsigned int _tilesNumberY = 5; // fallout 2 tiles by Y

                unsigned int _tileWidth = 350;  // fallout 2 map tile width

                unsigned int _tileHeight = 300; // fallout 2 map tile height

                // default size data
                unsigned int _mapWidth = 450;   // fallout 2 map screen width

                unsigned int _mapHeight = 442;  // fallout 2 map screen height

                unsigned int _mapMinX = 0;      // start X point of map screen

                unsigned int _mapMinY = 0;      // start Y point of map screen
        };
    }
}
