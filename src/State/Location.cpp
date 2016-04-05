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
#include "../State/Location.h"

// C++ standard includes
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Base/StlFeatures.h"
#include "../Event/Mouse.h"
#include "../Exception.h"
#include "../Format/Map/File.h"
#include "../Format/Map/Elevation.h"
#include "../Format/Map/Object.h"
#include "../Format/Map/Script.h"
#include "../Format/Txt/MapsFile.h"
#include "../Format/Gam/File.h"
#include "../functions.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/Defines.h"
#include "../Game/DoorSceneryObject.h"
#include "../Game/DudeObject.h"
#include "../Game/ExitMiscObject.h"
#include "../Game/Game.h"
#include "../Game/Object.h"
#include "../Game/ObjectFactory.h"
#include "../Game/SpatialObject.h"
#include "../Game/Time.h"
#include "../Game/WeaponItemObject.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../PathFinding/HexagonGrid.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/CursorDropdown.h"
#include "../State/ExitConfirm.h"
#include "../State/MainMenu.h"
#include "../UI/Animation.h"
#include "../UI/AnimationFrame.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"
#include "../UI/Tile.h"
#include "../UI/TileMap.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        using namespace Base;

        const int Location::DROPDOWN_DELAY = 350;
        const int Location::KEYBOARD_SCROLL_STEP = 35;

        Location::Location() : State()
        {
            auto game = Game::getInstance();
            game->mouse()->setState(Input::Mouse::Cursor::ACTION);

            _camera = make_unique<LocationCamera>(game->renderer()->size(), Point(0, 0));

            _hexagonInfo = make_unique<UI::TextArea>("", game->renderer()->width() - 135, 25);
            _hexagonInfo->setWidth(135);
            _hexagonInfo->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

        }

        Location::~Location()
        {
        }

        void Location::init()
        {
            if (initialized()) return;
            State::init();

            setFullscreen(true);
            setModal(true);

            auto game = Game::getInstance();
            setLocation("maps/" + game->settings()->initialLocation() + ".map");

            _playerPanel = makeUI<UI::PlayerPanel>();

            _mouseDownHandler.add(std::bind(&Location::onMouseDown, this, std::placeholders::_1));
            _mouseUpHandler.add(std::bind(&Location::onMouseUp, this, std::placeholders::_1));
            _mouseMoveHandler.add(std::bind(&Location::onMouseMove, this, std::placeholders::_1));

            // action cursor stuff
            _actionCursorTimer.setInterval((unsigned)DROPDOWN_DELAY);
            _actionCursorTimer.tickHandler().add([this](Event::Event*)
                {
                    if (!_objectUnderCursor) return;

                    auto game = Game::getInstance();
                    if (_actionCursorButtonPressed || game->mouse()->state() == Input::Mouse::Cursor::ACTION)
                    {
                        if (!_actionCursorButtonPressed && (_actionCursorLastObject != _objectUnderCursor))
                        {
                            _objectUnderCursor->look_at_p_proc();
                            _actionCursorLastObject = _objectUnderCursor;
                        }
                        auto icons = getCursorIconsForObject(_objectUnderCursor);
                        if (icons.size() > 0)
                        {
                            if (dynamic_cast<CursorDropdown*>(game->topState()) != nullptr)
                            {
                                game->popState();
                            }
                            auto state = new CursorDropdown(std::move(icons), !_actionCursorButtonPressed);
                            state->setObject(_objectUnderCursor);
                            Game::getInstance()->pushState(state);
                        }
                    }
                    _actionCursorButtonPressed = false;
                });
        }

        void Location::onStateActivate(Event::State* event)
        {
            // correct position of "red hexagon" after popups
            auto mouse = Game::getInstance()->mouse();
            auto hexagon = hexagonGrid()->hexagonAt(mouse->position() + _camera->topLeft());
            if (mouse->state() == Input::Mouse::Cursor::HEXAGON_RED && hexagon)
            {
                mouse->ui()->setPosition(hexagon->position() - _camera->topLeft());
            }
        }

        void Location::onStateDeactivate(Event::State* event)
        {
            _objectUnderCursor = nullptr;
            _actionCursorTimer.stop();
        }

        void Location::setLocation(const std::string& name)
        {
            _floor = make_unique<UI::TileMap>();
            _roof = make_unique<UI::TileMap>();
            _hexagonGrid = make_unique<HexagonGrid>();
            _objects.clear();
            std::vector<glm::vec2> _vertices;
            for (auto hex : _hexagonGrid->hexagons())
            {
                _vertices.push_back(glm::vec2(hex->position().x(), hex->position().y()));
            }
            std::vector<GLuint> indexes;
            for (auto hexagon : _hexagonGrid->hexagons())
            {
                /*if (!Rect::inRect(hexagon->position()-camera()->topLeft(),Size(Game::getInstance()->renderer()->width(),Game::getInstance()->renderer()->height())))
                {
                    continue;
                }*/
                bool doup=true;
                bool dodown = true;
                if (hexagon->number() % 200 == 0)
                {
                    doup=false;
                }
                if ((hexagon->number()+1) % 200 == 0)
                {
                    dodown=false;
                }
                if (hexagon->number()<200)
                {
                    doup = false;
                }
                if (hexagon->number()>=39800)
                {
                    dodown = false;
                }
                if (dodown)
                {
                    indexes.push_back(hexagon->number());
                    if (hexagon->number() % 2) // odd
                    {
                        indexes.push_back(hexagon->number()+200);
                        indexes.push_back(hexagon->number()+1);
                    }
                    else
                    {
                        indexes.push_back(hexagon->number()+200);
                        indexes.push_back(hexagon->number()+201);
                    }
                }
                if (doup)
                {
                    indexes.push_back(hexagon->number());
                    if (hexagon->number() % 2) // odd
                    {
                        indexes.push_back(hexagon->number()-200);
                        indexes.push_back(hexagon->number()-201);
                    }
                    else
                    {
                        indexes.push_back(hexagon->number()-200);
                        indexes.push_back(hexagon->number()-1);
                    }
                }
            }
            _lightmap = new Graphics::Lightmap(_vertices,indexes);

            auto mapFile = ResourceManager::getInstance()->mapFileType(name);

            if (mapFile == nullptr)
            {
                auto defaultSettings = new Settings;
                Logger::warning() << "No such map: `" << name << "`; using default map" << std::endl;
                mapFile = ResourceManager::getInstance()->mapFileType("maps/" + defaultSettings->initialLocation() + ".map");
            }

            _currentElevation = mapFile->defaultElevation();

            // Set camera position on default
            camera()->setCenter(hexagonGrid()->at(mapFile->defaultPosition())->position());

            // Initialize MAP vars
            if (mapFile->MVARS()->size() > 0)
            {
                auto name = mapFile->name();
                auto gam = ResourceManager::getInstance()->gamFileType("maps/" + name.substr(0, name.find(".")) + ".gam");
                for (auto mvar : *gam->MVARS())
                {
                    _MVARS.push_back(mvar.second);
                }
            }

            auto mapObjects = mapFile->elevations()->at(_currentElevation)->objects();

            auto ticks = SDL_GetTicks();
            // @todo remove old objects from hexagonal grid
            for (auto mapObject : *mapObjects)
            {
                auto object = Game::ObjectFactory::getInstance()->createObject(mapObject->PID());
                if (!object)
                {
                    Logger::error() << "Location::setLocation() - can't create object with PID: " << mapObject->PID() << std::endl;
                    continue;
                }

                object->setFID(mapObject->FID());
                object->setElevation(_currentElevation);
                object->setOrientation(mapObject->orientation());
                object->setLightRadius(mapObject->lightRadius());
                object->setLightIntensity(mapObject->lightIntensity());
                object->setFlags(mapObject->flags());
                object->setDefaultFrame(mapObject->frameNumber());


                if (auto exitGrid = dynamic_cast<Game::ExitMiscObject*>(object))
                {
                    exitGrid->setExitMapNumber(mapObject->exitMap());
                    exitGrid->setExitElevationNumber(mapObject->exitElevation());
                    exitGrid->setExitHexagonNumber(mapObject->exitPosition());
                    exitGrid->setExitDirection(mapObject->exitOrientation());
                }

                if (auto door = dynamic_cast<Game::DoorSceneryObject*>(object))
                {
                    door->setOpened(mapObject->opened());
                }

                if (auto container = dynamic_cast<Game::ContainerItemObject*>(object))
                {
                    for (auto child : *mapObject->children())
                    {
                        auto item = dynamic_cast<Game::ItemObject*>(Game::ObjectFactory::getInstance()->createObject(child->PID()));
                        if (!item)
                        {
                            Logger::error() << "Location::setLocation() - can't create object with PID: " << child->PID() << std::endl;
                            continue;
                        }
                        item->setAmount(child->ammount());
                        container->inventory()->push_back(item);
                    }
                }

                // TODO: use common interface...
                if (auto critter = dynamic_cast<Game::CritterObject*>(object))
                {
                    for (auto child : *mapObject->children())
                    {
                        auto item = dynamic_cast<Game::ItemObject*>(Game::ObjectFactory::getInstance()->createObject(child->PID()));
                        if (!item)
                        {
                            Logger::error() << "Location::setLocation() - can't create object with PID: " << child->PID() << std::endl;
                            continue;
                        }
                        item->setAmount(child->ammount());
                        critter->inventory()->push_back(item);
                    }
                }

                if (mapObject->scriptId() > 0)
                {
                    auto intFile = ResourceManager::getInstance()->intFileType(mapObject->scriptId());
                    if (intFile) object->setScript(new VM::Script(intFile,object));
                }
                if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId())
                {
                    auto intFile = ResourceManager::getInstance()->intFileType(mapObject->mapScriptId());
                    if (intFile) object->setScript(new VM::Script(intFile, object));
                }

                auto hexagon = hexagonGrid()->at(mapObject->hexPosition());
                moveObjectToHexagon(object, hexagon, false);

                // flat objects are like tiles. they don't think (but has handlers) and rendered first.
                if (object->flat())
                {
                    _flatObjects.emplace_back(object);
                }
                else
                {
                    _objects.emplace_back(object);
                }

            }
            Logger::info("GAME") << "Objects loaded in " << (SDL_GetTicks() - ticks) << std::endl;

            // Adding dude
            {
                auto player = Game::getInstance()->player();
                player->setArmorSlot(nullptr);
                // Just for testing
                {
                    player->inventory()->push_back((Game::ItemObject*)Game::ObjectFactory::getInstance()->createObject(0x00000003)); // power armor
                    player->inventory()->push_back((Game::ItemObject*)Game::ObjectFactory::getInstance()->createObject(0x0000004A)); // leather jacket
                    player->inventory()->push_back((Game::ItemObject*)Game::ObjectFactory::getInstance()->createObject(0x00000011)); // combat armor
                    player->inventory()->push_back((Game::ItemObject*)Game::ObjectFactory::getInstance()->createObject(0x00000071)); // purple robe
                    auto leftHand = Game::ObjectFactory::getInstance()->createObject(0x0000000C); // minigun
                    player->setLeftHandSlot(dynamic_cast<Game::WeaponItemObject*>(leftHand));
                    auto rightHand = Game::ObjectFactory::getInstance()->createObject(0x00000007); // spear
                    player->setRightHandSlot(dynamic_cast<Game::WeaponItemObject*>(rightHand));
                    player->setActionAnimation("aa")->stop();
                }
                player->setPID(0x01000001);
                player->setOrientation(mapFile->defaultOrientation());

                // Player script
                player->setScript(new VM::Script(ResourceManager::getInstance()->intFileType(0), player));

                auto hexagon = hexagonGrid()->at(mapFile->defaultPosition());
                _objects.emplace_back(player);
                moveObjectToHexagon(player, hexagon);
            }

            // Location script
            if (mapFile->scriptId() > 0)
            {
                _locationScript = make_unique<VM::Script>(ResourceManager::getInstance()->intFileType(mapFile->scriptId()-1), nullptr);
            }

            // Spatials
            for (auto script: *mapFile->scripts())
            {
                if (script->type() == Format::Map::Script::Type::SPATIAL)
                {
                    auto tile = script->spatialTile();
                    auto hex = tile & 0xFFFF;
                    auto elev = ((tile >> 28) & 0xf) >> 1;
                    if (elev == _currentElevation)
                    {
                        auto spatial = new Game::SpatialObject(script->spatialRadius());
                        spatial->setElevation(elev);
                        spatial->setHexagon(_hexagonGrid->at(hex));
                        auto intFile = ResourceManager::getInstance()->intFileType(script->scriptId());
                        if (intFile) spatial->setScript(new VM::Script(intFile, spatial));

                        _spatials.emplace_back(spatial);
                    }

                }
            }

            // Generates floor and roof images
            {
                for (unsigned int i = 0; i != 100*100; ++i)
                {
                    unsigned int tileX = std::ceil(((double)i)/100);
                    unsigned int tileY = i%100;
                    unsigned int x = (100 - tileY - 1)*48 + 32*(tileX - 1);
                    unsigned int y = tileX*24 +(tileY - 1)*12 + 1;

                    unsigned int tileNum = mapFile->elevations()->at(_currentElevation)->floorTiles()->at(i);
                    if (tileNum > 1)
                    {
                        _floor->tiles()[i] = make_unique<UI::Tile>(tileNum, Point(x, y));
                    }

                    tileNum = mapFile->elevations()->at(_currentElevation)->roofTiles()->at(i);
                    if (tileNum > 1)
                    {
                        _roof->tiles()[i] = make_unique<UI::Tile>(tileNum, Point(x, y - 96));
                    }
                }
                _floor->init();
                _roof->init();
            }

            auto maps = ResourceManager::getInstance()->mapsTxt()->maps();
            auto mapShortName = path_basename(name, true);
            auto it = std::find_if(maps.begin(), maps.end(), [&](const Format::Txt::Map& map)
            {
                return map.name == mapShortName;
            });

            if (it != maps.end())
            {
                _currentMap = it-maps.begin();

                if (!it->music.empty() && Game::getInstance()->settings()->musicVolume() > 0.0001)
                {
                    Logger::info("Location") << "Playing music " << it->music << std::endl;
                    Game::getInstance()->mixer()->playACMMusic(it->music + ".acm");
                }
                else
                {
                    Logger::info("Location") << "Map " << mapShortName << " has no music." << std::endl;
                }
                _ambientSfx = it->ambientSfx;
                if (!_ambientSfx.empty())
                {
                    _ambientSfxTimer.tickHandler().add([this, mapShortName](Event::Event* evt)
                    {
                        unsigned char rnd = std::rand() % 100, sum = 0;
                        auto it = _ambientSfx.cbegin();
                        while (it != _ambientSfx.cend() && (sum + it->second) < rnd)
                        {
                            sum += it->second;
                            ++it;
                        }
                        if (it != _ambientSfx.cend())
                        {
                            Logger::info("Location") << "Playing ambient sfx " << it->first << std::endl;
                            Game::getInstance()->mixer()->playACMSound("sound/sfx/" + it->first + ".acm");
                        }
                        else
                        {
                            Logger::error("Location") << "Could not match ambient sfx for map " << mapShortName << " with " << rnd << std::endl;
                        }
                        _ambientSfxTimer.start(std::rand() % 10000 + 20000);
                    });
                    _ambientSfxTimer.start(10000);
                }
                else
                {
                    Logger::error("Location") << "No ambient sfx for map " << mapShortName << std::endl;
                }
            }
            initLight();

        }

        std::vector<Input::Mouse::Icon> Location::getCursorIconsForObject(Game::Object* object)
        {
            std::vector<Input::Mouse::Icon> icons;
            if (object->script() && object->script()->hasFunction("use_p_proc"))
            {
                icons.push_back(Input::Mouse::Icon::USE);
            }
            else if (dynamic_cast<Game::DoorSceneryObject*>(object))
            {
                icons.push_back(Input::Mouse::Icon::USE);
            }
            else if (dynamic_cast<Game::ContainerItemObject*>(object))
            {
                icons.push_back(Input::Mouse::Icon::USE);
            }

            switch (object->type())
            {
                case Game::Object::Type::ITEM:
                    break;
                case Game::Object::Type::DUDE:
                    icons.push_back(Input::Mouse::Icon::ROTATE);
                    break;
                case Game::Object::Type::SCENERY:
                    break;
                case Game::Object::Type::CRITTER:
                    icons.push_back(Input::Mouse::Icon::TALK);
                    break;
                default:
                    break;
            }
            icons.push_back(Input::Mouse::Icon::LOOK);
            icons.push_back(Input::Mouse::Icon::INVENTORY);
            icons.push_back(Input::Mouse::Icon::SKILL);
            icons.push_back(Input::Mouse::Icon::CANCEL);
            return icons;
        }


        void Location::onObjectMouseEvent(Event::Mouse* event, Game::Object* object)
        {
            if (!object) return;
            if (event->button() == Event::Mouse::Button::LEFT)
            {
                if (event->name() == "mousedown")
                {
                    _objectUnderCursor = object;
                    _actionCursorTimer.start();
                    _actionCursorButtonPressed = true;
                }
                else if (event->name() == "mouseclick")
                {
                    auto icons = getCursorIconsForObject(object);
                    if (icons.size() > 0)
                    {
                        handleAction(object, icons.front());
                        _actionCursorButtonPressed = false;
                    }
                }
            }
        }

        void Location::onObjectHover(Event::Mouse* event, Game::Object* object)
        {
            if (event->name() == "mouseout")
            {
                if (_objectUnderCursor == object)
                    _objectUnderCursor = nullptr;
            }
            else
            {
                if (_objectUnderCursor == nullptr || event->name() == "mousein")
                {
                    _objectUnderCursor = object;
                    _actionCursorButtonPressed = false;
                }
                _actionCursorTimer.start();
            }
        }

        void Location::onBackgroundClick(Event::Mouse* event)
        {
        }

        void Location::render()
        {
            _floor->render();


            _lightmap->render(_camera->topLeft());

            // render hex cursor
            if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HEXAGON_RED)
            {
                Game::getInstance()->mouse()->render();
            }
            //render only flat objects first
            for (auto &object: _flatObjects)
            {
                object->render();
                object->hexagon()->setInRender(object->inRender());
            }

            for (auto &object: _objects)
            {
                object->render();
                object->hexagon()->setInRender(object->inRender());
            }
        /*
            for (auto hexagon : _hexagonGrid->hexagons())
            {
                hexagon->setInRender(false);
                for (auto object : *hexagon->objects())
                {
                    if (object->flat())
                    {
                        object->render();
                        if (object->inRender())
                        {
                            hexagon->setInRender(true);
                        }
                    }
                }
            }

            // now render all other objects
            for (auto hexagon : _hexagonGrid->hexagons())
            {
                hexagon->setInRender(false);
                for (auto object : *hexagon->objects())
                {
                    if (!object->flat())
                    {
                        object->render();
                        if (object->inRender())
                        {
                            hexagon->setInRender(true);
                        }
                    }
                }
            }
        */
            for (auto &object: _objects)
            {
                object->renderText();
            }

            _roof->render();

            // render hex object outline
            if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HEXAGON_RED)
            {
                Game::getInstance()->mouse()->renderOutline();
            }


            // just for testing
            if (Game::getInstance()->settings()->targetHighlight())
            {
                for (auto &object: _objects) {
                    if (dynamic_cast<Game::CritterObject *>(object.get())) {
                        if (!dynamic_cast<Game::DudeObject *>(object.get())) {
                            object->renderOutline(1);
                        }
                    }
                }
            }

            if (active())
            {
                _hexagonInfo->render();
            }

            State::render();
        }

        void Location::think()
        {
            Game::getInstance()->gameTime()->think();

            auto player = Game::getInstance()->player();

            for (auto& object : _objects)
            {
                object->think();
            }
            player->think();

            // location scrolling
            if (_scrollTicks + 10 < SDL_GetTicks())
            {
                _scrollTicks = SDL_GetTicks();
                int scrollDelta = 5;

                //Game::getInstance()->mouse()->setType(Mouse::ACTION);

                Point pScrollDelta = Point(
                    _scrollLeft ? -scrollDelta : (_scrollRight ? scrollDelta : 0),
                    _scrollTop ? -scrollDelta : (_scrollBottom ? scrollDelta : 0)
                );
                _camera->setCenter(_camera->center() + pScrollDelta);

                auto mouse = Game::getInstance()->mouse();

                // if scrolling is active
                if (_scrollLeft || _scrollRight || _scrollTop || _scrollBottom)
                {
                    Input::Mouse::Cursor state;
                    if (_scrollLeft)   state = Input::Mouse::Cursor::SCROLL_W;
                    if (_scrollRight)  state = Input::Mouse::Cursor::SCROLL_E;
                    if (_scrollTop)    state = Input::Mouse::Cursor::SCROLL_N;
                    if (_scrollBottom) state = Input::Mouse::Cursor::SCROLL_S;
                    if (_scrollLeft && _scrollTop)     state = Input::Mouse::Cursor::SCROLL_NW;
                    if (_scrollLeft && _scrollBottom)  state = Input::Mouse::Cursor::SCROLL_SW;
                    if (_scrollRight && _scrollTop)    state = Input::Mouse::Cursor::SCROLL_NE;
                    if (_scrollRight && _scrollBottom) state = Input::Mouse::Cursor::SCROLL_SE;
                    if (mouse->state() != state)
                    {
                        if (mouse->scrollState())
                        {
                            mouse->popState();
                        }
                        mouse->pushState(state);
                    }
                }
                // scrolling is not active
                else
                {
                    if (mouse->scrollState())
                    {
                        mouse->popState();
                    }
                }

            }
            if (_locationEnter)
            {
                _locationEnter = false;

                if (_locationScript) _locationScript->initialize();

                for (auto& object : _objects)
                {
                    if (object->script())
                    {
                        object->script()->initialize();
                    }
                }
                for (auto& spatial: _spatials)
                {
                    if (spatial->script())
                    {
                        spatial->script()->initialize();
                    }
                }
                if (player->script())
                {
                    player->script()->initialize();
                }

                if (_locationScript) _locationScript->call("map_enter_p_proc");

                // By some reason we need to use reverse iterator to prevent scripts problems
                // If we use normal iterators, some exported variables are not initialized on the moment
                // when script is called
                player->map_enter_p_proc();
                for (auto it = _objects.rbegin(); it != _objects.rend(); ++it)
                {
                    (*it)->map_enter_p_proc();
                }
            }
            else
            {
                if (_scriptsTicks + 10000 < SDL_GetTicks())
                {
                    _scriptsTicks = SDL_GetTicks();
                    if (_locationScript)
                    {
                        _locationScript->call("map_update_p_proc");
                    }
                    for (auto& object : _objects)
                    {
                        object->map_update_p_proc();
                    }
                    player->map_update_p_proc();
                }
            }

            // timers processing
            _actionCursorTimer.think();
            _ambientSfxTimer.think();

            for (auto it = _timerEvents.begin(); it != _timerEvents.end(); )
            {
                it->timer.think();
                if (!it->timer.enabled())
                {
                    it = _timerEvents.erase(it);
                }
                else ++it;
            }

            State::think();
        }

        void Location::toggleCursorMode()
        {
            auto game = Game::getInstance();
            auto mouse = game->mouse();
            switch (mouse->state())
            {
                case Input::Mouse::Cursor::NONE: // just for testing
                {
                    mouse->pushState(Input::Mouse::Cursor::ACTION);
                    break;
                }
                case Input::Mouse::Cursor::ACTION:
                {
                    auto hexagon = hexagonGrid()->hexagonAt(mouse->position() + _camera->topLeft());
                    if (!hexagon)
                    {
                        break;
                    }
                    mouse->pushState(Input::Mouse::Cursor::HEXAGON_RED);
                    mouse->ui()->setPosition(hexagon->position() - _camera->topLeft());
                    _objectUnderCursor = nullptr;
                    break;
                }
                case Input::Mouse::Cursor::HEXAGON_RED:
                {
                    mouse->popState();
                    break;
                }
                default:
                    break;
            }
        }

        void Location::handle(Event::Event* event)
        {
            State::handle(event);
            if (event->handled()) return;

            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                using Mouse = Event::Mouse;
                auto mouse = Game::getInstance()->mouse();

                switch (mouseEvent->originalType())
                {
                    case Mouse::Type::BUTTON_DOWN:
                    {
                        emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseDownHandler);
                        break;
                    }
                    case Mouse::Type::BUTTON_UP:
                    {
                        emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseUpHandler);
                        break;
                    }
                    case Mouse::Type::MOVE:
                    {
                        emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseMoveHandler);

                        if (mouse->state() == Input::Mouse::Cursor::ACTION)
                        {
                            // optimization to prevent FPS drops on mouse move
                            // TODO: replace with a Timer?
                            auto ticks = SDL_GetTicks();
                            if (ticks - _mouseMoveTicks < 50)
                            {
                                event->setHandled(true);
                            }
                            else
                            {
                                _mouseMoveTicks = ticks;
                            }
                        }
                        break;
                    }
                }
                // let event fall down to all objects when using action cursor and within active view
                if (!mouseEvent->handled() && (mouse->state() == Input::Mouse::Cursor::ACTION || mouse->state() == Input::Mouse::Cursor::NONE))
                {
                    if (!_roof->opaque(mouse->position()))
                    {
                        handleByGameObjects(mouseEvent);
                    }
                }
            }
        }

        void Location::handleByGameObjects(Event::Mouse* event)
        {

            for (auto it = _objects.rbegin(); it != _objects.rend(); ++it)
            {
                auto object = (*it).get();
                if (event->handled()) return;
                if (!object->inRender()) continue;
                object->handle(event);
            }

            // sadly, flat objects do handle events.
            for (auto it = _flatObjects.rbegin(); it != _flatObjects.rend(); ++it)
            {
                auto object = (*it).get();
                if (event->handled()) return;
                if (!object->inRender()) continue;
                object->handle(event);
            }
        /*
            auto hexagons = _hexagonGrid->hexagons();
            for (auto it = hexagons.rbegin(); it != hexagons.rend(); ++it)
            {
                Hexagon* hexagon = *it;
                if (!hexagon->inRender()) continue;
                auto objects = hexagon->objects();
                for (auto itt = objects->rbegin(); itt != objects->rend(); ++itt)
                {
                    if (event->handled()) return;
                    auto object = *itt;
                    if (!object->inRender()) continue;
                    object->handle(event);
                }
            }
        */
        }

        void Location::onMouseDown(Event::Mouse* event)
        {
            if (event->rightButton())
            {
                toggleCursorMode();
                event->setHandled(true);
            }
        }

        void Location::onMouseUp(Event::Mouse* event)
        {
            if (event->leftButton())
            {
                auto game = Game::getInstance();
                auto mouse = game->mouse();
                if (mouse->state() == Input::Mouse::Cursor::HEXAGON_RED)
                {
                    // Here goes the movement
                    auto hexagon = hexagonGrid()->hexagonAt(mouse->position() + _camera->topLeft());
                    if (hexagon)
                    {
                        auto path = hexagonGrid()->findPath(game->player()->hexagon(), hexagon);
                        if (path.size())
                        {
                            game->player()->stopMovement();
                            game->player()->setRunning((_lastClickedTile != 0 && hexagon->number() == _lastClickedTile) || (event->shiftPressed() != game->settings()->running()));
                            for (auto pathHexagon : path)
                            {
                                game->player()->movementQueue()->push_back(pathHexagon);
                            }
                        }
                        event->setHandled(true);
                        _lastClickedTile = hexagon->number();
                    }
                }
            }
        }

        void Location::onMouseMove(Event::Mouse* mouseEvent)
        {
            auto mouse = Game::getInstance()->mouse();
            auto hexagon = hexagonGrid()->hexagonAt(mouse->position() + _camera->topLeft());
            if (mouse->states()->empty())
            {
                mouse->setState(Input::Mouse::Cursor::ACTION);
            }
            if (mouse->state() == Input::Mouse::Cursor::HEXAGON_RED && hexagon)
            {
                mouse->ui()->setPosition(hexagon->position() - _camera->topLeft());
            }

            int scrollArea = 8;
            auto renderer = Game::getInstance()->renderer();
            Point mpos = mouse->position();
            _scrollLeft = (mpos.x() < scrollArea);
            _scrollRight = (mpos.x() > renderer->width() - scrollArea);
            _scrollTop = (mpos.y() < scrollArea);
            _scrollBottom = (mpos.y() > renderer->height() - scrollArea);

            if (hexagon)
            {
                std::string text = "Hex number: " + std::to_string(hexagon->number()) + "\n";
                text += "Hex position: " + std::to_string(hexagon->number()%200) + "," + std::to_string((unsigned int)(hexagon->number()/200)) + "\n";
                text += "Hex coords: " + std::to_string(hexagon->position().x()) + "," + std::to_string(hexagon->position().y()) + "\n";
                auto dude = Game::getInstance()->player();
                auto hex = dude->hexagon();
                text += "Hex delta:\n dx=" + std::to_string(hex->cubeX()-hexagon->cubeX()) + "\n dy="+ std::to_string(hex->cubeY()-hexagon->cubeY()) + "\n dz=" + std::to_string(hex->cubeZ()-hexagon->cubeZ()) + "\n";
                text += "Hex light: " + std::to_string(hexagon->light()) + "\n";
                _hexagonInfo->setText(text);
            }
            else
            {
                _hexagonInfo->setText("No hex");
            }
        }

        void Location::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_m:
                    toggleCursorMode();
                    break;
                case SDLK_COMMA:
                {
                    auto player = Game::getInstance()->player();
                    player->setOrientation(player->orientation() + 5); // rotate left
                    break;
                }
                case SDLK_PERIOD:
                {
                    auto player = Game::getInstance()->player();
                    player->setOrientation(player->orientation() + 1); // rotate right
                    break;
                }
                case SDLK_HOME:
                    centerCameraAtHexagon(Game::getInstance()->player()->hexagon());
                    break;
                case SDLK_PLUS:
                case SDLK_KP_PLUS:
                    // @TODO: increase brightness
                    break;
                case SDLK_MINUS:
                case SDLK_KP_MINUS:
                    // @TODO: decrease brightness
                    break;
                case SDLK_1:
                    // @TODO: use skill: sneak
                    break;
                case SDLK_2:
                    // @TODO: use skill: lockpick
                    break;
                case SDLK_3:
                    // @TODO: use skill: steal
                    break;
                case SDLK_4:
                    // @TODO: use skill: traps
                    break;
                case SDLK_5:
                    // @TODO: use skill: first aid
                    break;
                case SDLK_6:
                    // @TODO: use skill: doctor
                    break;
                case SDLK_7:
                    // @TODO: use skill: science
                    break;
                case SDLK_8:
                    // @TODO: use skill: repair
                    break;
                case SDLK_LEFT:
                    _camera->setCenter(_camera->center() + Point(-KEYBOARD_SCROLL_STEP, 0));
                    break;
                case SDLK_RIGHT:
                    _camera->setCenter(_camera->center() + Point(KEYBOARD_SCROLL_STEP, 0));
                    break;
                case SDLK_UP:
                    _camera->setCenter(_camera->center() + Point(0, -KEYBOARD_SCROLL_STEP));
                    break;
                case SDLK_DOWN:
                    _camera->setCenter(_camera->center() + Point(0, KEYBOARD_SCROLL_STEP));
                    break;
            }
        }


        LocationCamera* Location::camera()
        {
            return _camera.get();
        }

        void Location::setMVAR(unsigned int number, int value)
        {
            if (number >= _MVARS.size())
            {
                throw Exception("Location::setMVAR(num, value) - num out of range: " + std::to_string((int)number));
            }
            _MVARS.at(number) = value;
        }

        int Location::MVAR(unsigned int number)
        {
            if (number >= _MVARS.size())
            {
                throw Exception("Location::MVAR(num) - num out of range: " + std::to_string((int)number));
            }
            return _MVARS.at(number);
        }

        std::map<std::string, VM::StackValue>* Location::EVARS()
        {
            return &_EVARS;
        }

        void Location::moveObjectToHexagon(Game::Object *object, Hexagon *hexagon, bool update)
        {
            auto oldHexagon = object->hexagon();
            if (oldHexagon)
            {
                if (update)
                {
                    //_hexagonGrid->initLight(oldHexagon, false);
                }

                for (auto it = oldHexagon->objects()->begin(); it != oldHexagon->objects()->end(); ++it)
                {
                    if (*it == object)
                    {
                        oldHexagon->objects()->erase(it);
                        break;
                    }
                }

                /* JUST FOR EXIT GRIDS TESTING
                for (auto obj : *hexagon->objects())
                {
                    if (auto exitGrid = dynamic_cast<GameExitMiscObject*>(obj))
                    {
                        auto &debug = Logger::critical("LOCATION");
                        debug << " PID: 0x" << std::hex << exitGrid->PID() << std::dec << std::endl;
                        debug << " name: " << exitGrid->name() << std::endl;
                        debug << " exitMapNumber: " << exitGrid->exitMapNumber() << std::endl;
                        debug << " exitElevationNumber: " << exitGrid->exitElevationNumber() << std::endl;
                        debug << " exitHexagonNumber: " << exitGrid->exitHexagonNumber() << std::endl;
                        debug << " exitDirection: " << exitGrid->exitDirection() << std::endl << std::endl;
                    }
                }
                */
            }

            object->setHexagon(hexagon);
            if (hexagon)
            {
                hexagon->objects()->push_back(object);
            }

            if (object->type() == Game::Object::Type::CRITTER || object->type() == Game::Object::Type::DUDE)
                for (auto &spatial: _spatials)
                {
                    if (_hexagonGrid->distance(spatial->hexagon(), hexagon) <= spatial->radius())
                    {
                        spatial->spatial_p_proc(object);
                    }
                }

            // TODO: recreate _objects array for rendering/handling
            if (update)
            {
                _objects.sort(
                        [](std::unique_ptr<Game::Object> &obj1, std::unique_ptr<Game::Object> &obj2) -> bool
                        {
                            return obj1->hexagon()->number() < obj2->hexagon()->number();
                        }
                );
                _flatObjects.sort(
                        [](std::unique_ptr<Game::Object> &obj1, std::unique_ptr<Game::Object> &obj2) -> bool
                        {
                            return obj1->hexagon()->number() < obj2->hexagon()->number();
                        }
                );
                if(hexagon)
                {
                    initLight();
                    /*_hexagonGrid->initLight(hexagon, true);
                    std::vector<float> lights;
                    for (auto hex: _hexagonGrid->hexagons())
                    {
                        int lightLevel = 100;
                        unsigned int light = hex->light();
                        if (light<=_lightLevel) light=655;
                        lightLevel = light / ((65536-655)/100);

                        float l = lightLevel/100.0;
                        lights.push_back(l);
                    }
                    _lightmap->update(lights);*/

                }
            }

            if (auto dude = dynamic_cast<Game::DudeObject*>(object))
            {
                int x = dude->hexagon()->number() % 200;
                int y = dude->hexagon()->number() / 200;
                x /= 2;
                y /= 2;
                int tilenum = y*100+x;

                if (!_roof->inside() && _roof->tiles().count(tilenum))
                {
                    // we was outside, now are inside
                    _roof->disable(tilenum);
                    _roof->setInside(true);
                }
                else if(_roof->inside() && !_roof->tiles().count(tilenum))
                {
                    // we was inside, now are outside
                    _roof->enableAll();
                    _roof->setInside(false);
                }
            }
        }


        void Location::removeObjectFromMap(Game::Object *object)
        {
            auto objectsAtHex = object->hexagon()->objects();

            for (auto it = objectsAtHex->begin(); it != objectsAtHex->end(); ++it)
            {
                if (*it == object)
                {
                    objectsAtHex->erase(it);
                    break;
                }
            }
            if (_objectUnderCursor == object) _objectUnderCursor = nullptr;
            for (auto it = _objects.begin(); it != _objects.end(); ++it)
            {
                if ((*it).get() == object)
                {
                    _objects.erase(it);
                    break;
                }
            }
        }


        void Location::destroyObject(Game::Object* object)
        {
            object->destroy_p_proc();
            removeObjectFromMap(object);
        }

        void Location::centerCameraAtHexagon(Hexagon* hexagon)
        {
            _camera->setCenter(hexagon->position());
        }

        void Location::centerCameraAtHexagon(int tileNum)
        {
            try
            {
                centerCameraAtHexagon(_hexagonGrid->at((unsigned int)tileNum));
            }
            catch (std::out_of_range ex)
            {
                throw Exception(std::string("Tile number out of range: ") + std::to_string(tileNum));
            }
        }

        void Location::handleAction(Game::Object* object, Input::Mouse::Icon action)
        {
            switch (action)
            {
                case Input::Mouse::Icon::LOOK:
                {
                    object->description_p_proc();
                    break;
                }
                case Input::Mouse::Icon::USE:
                {
                    auto player = Game::getInstance()->player();
                    auto animation = player->setActionAnimation("al");
                    animation->actionFrameHandler().add([object, player](Event::Event* event){ object->onUseAnimationActionFrame(event, player); });
                    break;
                }
                case Input::Mouse::Icon::ROTATE:
                {
                    auto dude = dynamic_cast<Game::DudeObject*>(object);
                    if (!dude) throw Exception("Location::handleAction() - only Dude can be rotated");

                    auto orientation = dude->orientation() + 1;
                    if (orientation > 5) orientation = 0;
                    dude->setOrientation(orientation);

                    break;
                }
                case Input::Mouse::Icon::TALK:
                {
                    if (auto critter = dynamic_cast<Game::CritterObject*>(object))
                    {
                        critter->talk_p_proc();
                    }
                    else
                    {
                        throw Exception("Location::handleAction() - can talk only with critters!");
                    }
                }
                default: {}
            }
        }

        void Location::displayMessage(const std::string& message)
        {
            _playerPanel->displayMessage(message);
            Logger::info("MESSAGE") << message << std::endl;
        }

        HexagonGrid* Location::hexagonGrid()
        {
            return _hexagonGrid.get();
        }

        UI::PlayerPanel* Location::playerPanel()
        {
            return _playerPanel;
        }


        void Location::addTimerEvent(Game::Object* obj, int delay, int fixedParam)
        {
            Game::GameTimer timer((unsigned)delay);
            timer.start();
            timer.tickHandler().add([this, obj, fixedParam](Event::Event*)
                {
                    if (obj)
                    if (auto vm = obj->script())
                    {
                        vm->setFixedParam(fixedParam);
                        vm->call("timed_event_p_proc");
                    }
                });
            _timerEvents.emplace_back(TimerEvent {obj, std::move(timer), fixedParam});
        }

        void Location::removeTimerEvent(Game::Object* obj)
        {
            _timerEvents.remove_if([=](Location::TimerEvent& item) { return item.object == obj; });
        }

        void Location::removeTimerEvent(Game::Object* obj, int fixedParam)
        {
            _timerEvents.remove_if([=](Location::TimerEvent& item) { return item.object == obj && item.fixedParam == fixedParam; });
        }

        unsigned int Location::lightLevel()
        {
            return _lightLevel;
        }

        void Location::setLightLevel(unsigned int level)
        {
            // TODO: check night vision perk and increase light by 20% (20% of what, maximum or current?)
            if (level>0x10000) level=0x10000;
            if (level<0x4000) level=0x4000;
            _lightLevel = level;
            initLight();
        }

        void Location::initLight()
        {
            for (auto hex: _hexagonGrid->hexagons())
            {
                hex->setLight(655);
            }

            for (auto hex: _hexagonGrid->hexagons())
            {
                _hexagonGrid->initLight(hex);
            }

            std::vector<float> lights;
            for (auto hex: _hexagonGrid->hexagons())
            {
                int lightLevel = 100;

                unsigned int light = hex->light();
                if (light<=_lightLevel) light=655;
                lightLevel = light / ((65536-655)/100);

                float l = lightLevel/100.0;
                lights.push_back(l);
            }
            _lightmap->update(lights);

        }

        Game::Object *Location::addObject(unsigned int PID, unsigned int position, unsigned int elevation)
        {
            auto object = Game::ObjectFactory::getInstance()->createObject(PID);
            _objects.emplace_back(object);
            moveObjectToHexagon(object, hexagonGrid()->at(position));
            object->setElevation(elevation);
            return object;
        }

        unsigned int Location::currentMapIndex()
        {
            return _currentMap;
        }
    }
}
