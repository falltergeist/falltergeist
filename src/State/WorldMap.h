#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
    namespace State
    {
        class WorldMap final : public State
        {
            public:
                WorldMap(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

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

                UI::Image* _panel = nullptr;

                UI::ImageList* _tiles = nullptr;

                UI::ImageButton* _hotspot = nullptr;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;

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
