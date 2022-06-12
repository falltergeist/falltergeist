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

        WorldMap::WorldMap(
            std::shared_ptr<UI::IResourceManager> resourceManager
        ) : State(), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);

            // loading city size images
            _citySizes = {
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr0.frm"),
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr1.frm"),
                std::make_shared<Graphics::TranslucentMask>("art/intrface/wrldspr2.frm"),
            };

            auto cityFile = ResourceManager::getInstance()->cityTxt();
            for (auto& city : cityFile->cities()) {
                _cities.emplace_back(std::make_unique<Game::WorldMapCity>(city, _citySizes[(int)city.size - 1]));
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
            _tiles = std::make_shared<UI::ImageList>(Graphics::Point(0, 0), std::vector<std::shared_ptr<UI::Image>>({
                _resourceManager->getImage("art/intrface/wrldmp00.frm"),
                _resourceManager->getImage("art/intrface/wrldmp01.frm"),
                _resourceManager->getImage("art/intrface/wrldmp02.frm"),
                _resourceManager->getImage("art/intrface/wrldmp03.frm"),
                _resourceManager->getImage("art/intrface/wrldmp04.frm"),
                _resourceManager->getImage("art/intrface/wrldmp05.frm"),
                _resourceManager->getImage("art/intrface/wrldmp06.frm"),
                _resourceManager->getImage("art/intrface/wrldmp07.frm"),
                _resourceManager->getImage("art/intrface/wrldmp08.frm"),
                _resourceManager->getImage("art/intrface/wrldmp09.frm"),
                _resourceManager->getImage("art/intrface/wrldmp10.frm"),
                _resourceManager->getImage("art/intrface/wrldmp11.frm"),
                _resourceManager->getImage("art/intrface/wrldmp12.frm"),
                _resourceManager->getImage("art/intrface/wrldmp13.frm"),
                _resourceManager->getImage("art/intrface/wrldmp14.frm"),
                _resourceManager->getImage("art/intrface/wrldmp15.frm"),
                _resourceManager->getImage("art/intrface/wrldmp16.frm"),
                _resourceManager->getImage("art/intrface/wrldmp17.frm"),
                _resourceManager->getImage("art/intrface/wrldmp18.frm"),
                _resourceManager->getImage("art/intrface/wrldmp19.frm")
            }));

            //auto cross = new Image("art/intrface/wmaploc.frm");
            _hotspot = _imageButtonFactory->getByType(ImageButtonType::MAP_HOTSPOT, {0, 0});
            //addUI(_hotspot);

            // creating screen
            if (Game::Game::getInstance()->settings()->worldMapFullscreen())
            {
                _panel = _resourceManager->getImage("art/intrface/wminfce2.frm"); // panel small
                _mapWidth = renderWidth - 168;
                _mapHeight = renderHeight;
                _mapMinX = 0;
                _mapMinY = 0;
            }
            else
            {
                _panel = _resourceManager->getImage("art/intrface/wmapbox.frm"); // panel full
                _mapWidth = 450;   // fallout 2 map screen width
                _mapHeight = 442;  // fallout 2 map screen height
                _mapMinX = (renderWidth - 640)/2 + 22;
                _mapMinY = (renderHeight - 480)/2 + 21;
            }
        }

        void WorldMap::render()
        {
            // calculating render size, screen size, etc
            unsigned int renderWidth = Game::Game::getInstance()->renderer()->size().width();
            unsigned int renderHeight = Game::Game::getInstance()->renderer()->size().height();

            // MAP SHOW
            // calculating delta (shift of map to fit to screen)
            _deltaX = _worldMapX - _mapWidth /2;
            _deltaY = _worldMapY - _mapHeight /2;

            unsigned int worldMapSizeX = _tilesNumberX * _tileWidth;
            unsigned int worldMapSizeY = _tilesNumberY * _tileHeight;

            // correcting delta
            if (_deltaX <0)
            {
                _deltaX = 0;
            }
            if (_deltaY <0)
            {
                _deltaY = 0;
            }
            if (worldMapSizeX- _deltaX < _mapWidth)
            {
                _deltaX = worldMapSizeX - _mapWidth;
            }
            if (worldMapSizeY- _deltaY < _mapHeight)
            {
                _deltaY = worldMapSizeY - _mapHeight;
            }

            signed int worldTileMinX = 0; // start X coordinate of current tile on world map
            signed int worldTileMinY = 0; // start Y coordinate of current tile on world map
            // NB: can be unsigned, but it compared with signed _deltaX and _deltaY, so...

            // copy tiles to screen if needed
            for (unsigned int y=0; y< _tilesNumberY; y++)
            {
                for (unsigned int x=0; x< _tilesNumberX; x++)
                {
                    _tiles->setCurrentImage(y* _tilesNumberX +x);
                    worldTileMinX = x* _tileWidth;
                    worldTileMinY = y* _tileHeight;
                    // checking if tile is visible on screenMap
                    // checking current tile borders
                    // either xmin or xmax SHOULD belongs to map area AND
                    // either ymin or ymax SHOULD belongs to map area
                    if((((_deltaX <=worldTileMinX) && (worldTileMinX<= _deltaX +(signed int)_mapWidth)) ||
                        ((_deltaX <=worldTileMinX+(signed int)_tileWidth) && (worldTileMinX+(signed int)_tileWidth <= _deltaX +(signed int)_mapWidth))) &&
                        (((_deltaY <=worldTileMinY) && (worldTileMinY<= _deltaY +(signed int)_mapHeight)) ||
                        ((_deltaY <=worldTileMinY+(signed int)_tileHeight) && (worldTileMinY+(signed int)_tileHeight <= _deltaY +(signed int)_mapHeight))) )
                    {
                        _tiles->images().at(y* _tilesNumberX +x)->setPosition(Point(x* _tileWidth - _deltaX, y* _tileHeight - _deltaY));
                        _tiles->images().at(y* _tilesNumberX +x)->render();
                    }
                }
            }

            // cities
            auto shift = Graphics::Point(_deltaX + 22, _deltaY + 21);
            for (auto& city : _cities) {
                if (city->state()) {
                    city->render(city->worldPos() - shift);
                }
            }

            // hostpot show
            _hotspot->setPosition(Point(_mapMinX + _worldMapX - _deltaX, _mapMinY + _worldMapY - _deltaY));
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
                    Graphics::Rectangle mapRectangle(Point(_mapMinX, _mapMinY), Graphics::Size(_mapWidth, _mapHeight));

                    // check if point clicked belongs to the screen
                    if (mapRectangle.contains(mouse->position())){
                        // change destination point
                        _worldMapX = mouse->position().x() + _deltaX - _mapMinX;
                        _worldMapY = mouse->position().y() + _deltaY - _mapMinY;
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
