// Project includes
#include "../State/WorldMap.h"
#include "../Game/Game.h"
#include "../Game/WorldMapCity.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/Location.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        WorldMap::WorldMap(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);

            // loading city size images
            _citySizes = {
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr0.frm"),
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr1.frm"),
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr2.frm"),
            };

            auto cityFile = ResourceManager::getInstance()->cityTxt();
            for (auto it = cityFile->cities().begin(); it != cityFile->cities().end(); ++it)
            {
                auto city = *it;
                this->_cities.push_back(new Game::WorldMapCity(city, _citySizes[(int)city.size - 1]));
            }
        }

        void WorldMap::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            unsigned int renderWidth = Game::Game::getInstance()->renderer()->size().width();
            unsigned int renderHeight = Game::Game::getInstance()->renderer()->size().height();

            // loading map tiles
            _tiles = new UI::ImageList({0, 0}, {
                resourceManager->getImage("art/intrface/wrldmp00.frm"),
                resourceManager->getImage("art/intrface/wrldmp01.frm"),
                resourceManager->getImage("art/intrface/wrldmp02.frm"),
                resourceManager->getImage("art/intrface/wrldmp03.frm"),
                resourceManager->getImage("art/intrface/wrldmp04.frm"),
                resourceManager->getImage("art/intrface/wrldmp05.frm"),
                resourceManager->getImage("art/intrface/wrldmp06.frm"),
                resourceManager->getImage("art/intrface/wrldmp07.frm"),
                resourceManager->getImage("art/intrface/wrldmp08.frm"),
                resourceManager->getImage("art/intrface/wrldmp09.frm"),
                resourceManager->getImage("art/intrface/wrldmp10.frm"),
                resourceManager->getImage("art/intrface/wrldmp11.frm"),
                resourceManager->getImage("art/intrface/wrldmp12.frm"),
                resourceManager->getImage("art/intrface/wrldmp13.frm"),
                resourceManager->getImage("art/intrface/wrldmp14.frm"),
                resourceManager->getImage("art/intrface/wrldmp15.frm"),
                resourceManager->getImage("art/intrface/wrldmp16.frm"),
                resourceManager->getImage("art/intrface/wrldmp17.frm"),
                resourceManager->getImage("art/intrface/wrldmp18.frm"),
                resourceManager->getImage("art/intrface/wrldmp19.frm")
            });

            //auto cross = new Image("art/intrface/wmaploc.frm");
            _hotspot = imageButtonFactory->getByType(ImageButtonType::MAP_HOTSPOT, {0, 0});
            //addUI(_hotspot);

            // creating screen
            if (Game::Game::getInstance()->settings()->worldMapFullscreen())
            {
                _panel = resourceManager->getImage("art/intrface/wminfce2.frm"); // panel small
                mapWidth = renderWidth - 168;
                mapHeight = renderHeight;
                mapMinX = 0;
                mapMinY = 0;
            }
            else
            {
                _panel = resourceManager->getImage("art/intrface/wmapbox.frm"); // panel full
                mapWidth = 450;   // fallout 2 map screen width
                mapHeight = 442;  // fallout 2 map screen height
                mapMinX = (renderWidth - 640)/2 + 22;
                mapMinY = (renderHeight - 480)/2 + 21;
            }
        }

        void WorldMap::render()
        {
            // calculating render size, screen size, etc
            unsigned int renderWidth = Game::Game::getInstance()->renderer()->size().width();
            unsigned int renderHeight = Game::Game::getInstance()->renderer()->size().height();

            // MAP SHOW
            // calculating delta (shift of map to fit to screen)
            deltaX = worldMapX - mapWidth/2;
            deltaY = worldMapY - mapHeight/2;

            unsigned int worldMapSizeX = tilesNumberX*tileWidth;
            unsigned int worldMapSizeY = tilesNumberY*tileHeight;

            // correcting delta
            if (deltaX<0)
            {
                deltaX = 0;
            }
            if (deltaY<0)
            {
                deltaY = 0;
            }
            if (worldMapSizeX-deltaX < mapWidth)
            {
                deltaX = worldMapSizeX - mapWidth;
            }
            if (worldMapSizeY-deltaY < mapHeight)
            {
                deltaY = worldMapSizeY - mapHeight;
            }

            signed int worldTileMinX = 0; // start X coordinate of current tile on world map
            signed int worldTileMinY = 0; // start Y coordinate of current tile on world map
            // NB: can be unsigned, but it compared with signed deltaX and deltaY, so...

            // copy tiles to screen if needed
            for (unsigned int y=0; y<tilesNumberY; y++)
            {
                for (unsigned int x=0; x<tilesNumberX; x++)
                {
                    _tiles->setCurrentImage(y*tilesNumberX+x);
                    worldTileMinX = x*tileWidth;
                    worldTileMinY = y*tileHeight;
                    // checking if tile is visible on screenMap
                    // checking current tile borders
                    // either xmin or xmax SHOULD belongs to map area AND
                    // either ymin or ymax SHOULD belongs to map area
                    if((((deltaX<=worldTileMinX) && (worldTileMinX<=deltaX+(signed int)mapWidth)) ||
                        ((deltaX<=worldTileMinX+(signed int)tileWidth) && (worldTileMinX+(signed int)tileWidth<=deltaX+(signed int)mapWidth))) &&
                        (((deltaY<=worldTileMinY) && (worldTileMinY<=deltaY+(signed int)mapHeight)) ||
                        ((deltaY<=worldTileMinY+(signed int)tileHeight) && (worldTileMinY+(signed int)tileHeight<=deltaY+(signed int)mapHeight))) )
                    {
                        _tiles->images().at(y*tilesNumberX+x)->setPosition(Point(x*tileWidth-deltaX, y*tileHeight-deltaY));
                        _tiles->images().at(y*tilesNumberX+x)->render();
                    }
                }
            }

            // cities
            auto renderer = Game::Game::getInstance()->renderer();
            auto shift = Graphics::Point(deltaX + 22, deltaY + 21);
            for (auto it = _cities.begin(); it != _cities.end(); ++it)
            {
                Game::WorldMapCity* city = (*it);
                if (city->state())
                {
                    city->render(city->worldPos() - shift);
                }
            }

            // hostpot show
            _hotspot->setPosition(Point(mapMinX + worldMapX - deltaX, mapMinY + worldMapY - deltaY));
            _hotspot->render();

            // panel
            unsigned int panelX = 0;
            unsigned int panelY = 0;

            if (Game::Game::getInstance()->settings()->worldMapFullscreen())
            {
                panelX = renderWidth - 168; // only panel right
            }
            else
            {
                panelX = (renderWidth - _panel->size().width()) / 2;
            }
            panelY = (renderHeight - _panel->size().height()) / 2;

            _panel->setPosition(Point(panelX, panelY));
            _panel->render();
        }

        void WorldMap::handle(Event::Event* event)
        {
            auto game = Game::Game::getInstance();

            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                auto mouse = game->mouse();

                // Left button down
                if (mouseEvent->name() == "mousedown" && mouseEvent->leftButton()) {
                    Graphics::Rectangle mapRectangle(Point(mapMinX, mapMinY), Graphics::Size(mapWidth, mapHeight));

                    // check if point clicked belongs to the screen
                    if (mapRectangle.contains(mouse->position())){
                        // change destination point
                        worldMapX = mouse->position().x() + deltaX - mapMinX;
                        worldMapY = mouse->position().y() + deltaY - mapMinY;
                    }
                }
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                if (keyboardEvent->name() == "keydown") {
                    onKeyDown(keyboardEvent);
                }
            }
        }

        void WorldMap::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void WorldMap::onStateDeactivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->popState();
        }

        void WorldMap::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                {
                    Game::Game::getInstance()->popState();
                }
            }
        }
    }
}
