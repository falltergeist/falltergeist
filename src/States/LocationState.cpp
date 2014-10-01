/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes
#include <cmath>
#include <list>
#include <algorithm>

// Falltergeist includes
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Graphics/Tile.h"
#include "../Engine/Graphics/TileMap.h"
#include "../Engine/PathFinding/Hexagon.h"
#include "../Engine/PathFinding/HexagonGrid.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/Logger.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Settings/Settings.h"
#include "../Game/GameDefines.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/CursorDropdownState.h"
#include "../States/ExitConfirmState.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../States/PlayerPanelState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
    auto renderer = Game::getInstance()->renderer();
    _camera = new LocationCamera(renderer->width(), renderer->height(), 0, 0);
    _floor = new TileMap();
    _roof = new TileMap();
    _hexagonGrid = new HexagonGrid();

    auto game = Game::getInstance();
    game->mouse()->setState(Mouse::ACTION);
}

LocationState::~LocationState()
{
    delete _hexagonGrid;
    delete _camera;
    delete _floor;
    delete _roof;
    delete _locationScript;
}

void LocationState::init()
{
    if (initialized()) return;
    State::init();


    auto game = Game::getInstance();

    setLocation("maps/" + Game::getInstance()->engineSettings()->initialLocation() + ".map");

    game->pushState(new PlayerPanelState());
}

void LocationState::setLocation(std::string name)
{    

    auto mapFile = ResourceManager::mapFileType(name);

    if (mapFile == nullptr)
    {
        Logger::warning() << "No such map: `" << name << "`; using default map" << std::endl;
        mapFile = ResourceManager::mapFileType("maps/" + EngineSettings::defaultInitLocation() + ".map");
    }

    _currentElevation = mapFile->defaultElevation();

    // Set camera position on default
    camera()->setXPosition(hexagonGrid()->at(mapFile->defaultPosition())->x());
    camera()->setYPosition(hexagonGrid()->at(mapFile->defaultPosition())->y());

    // Initialize MAP vars
    if (mapFile->MVARsize() > 0)
    {
        auto name = mapFile->name();
        auto gam = ResourceManager::gamFileType("maps/" + name.substr(0, name.find(".")) + ".gam");
        for (auto mvar : *gam->MVARS())
        {
            _MVARS.push_back(mvar.second);
        }
    }

    // @todo remove objects from hexagons

    auto mapObjects = mapFile->elevations()->at(_currentElevation)->objects();

    for (auto mapObject : *mapObjects)
    {
        auto object = GameObjectFactory::createObject(mapObject->PID());
        if (!object)
        {
            Logger::error() << "LocationState::setLocation() - cant create object with PID: " << mapObject->PID() << std::endl;
            continue;
        }


        object->setFID(mapObject->FID());
        object->setElevation(_currentElevation);
        object->setOrientation(mapObject->orientation());

        if (mapObject->scriptId() > 0)
        {
            auto intFile = ResourceManager::intFileType(mapObject->scriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile,object));
        }
        if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId())
        {
            auto intFile = ResourceManager::intFileType(mapObject->mapScriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile, object));
        }

        auto hexagon = hexagonGrid()->at(mapObject->hexPosition());
        LocationState::moveObjectToHexagon(object, hexagon, false);
    }

    // Adding dude
    {
        auto player = Game::getInstance()->player();
        player->setPID(0x01000001);
        player->setFID(FID_HERO_MALE);
        player->setOrientation(mapFile->defaultOrientation());

        // Player script
        auto script = new VM(ResourceManager::intFileType(0), player);
        player->scripts()->push_back(script);

        auto hexagon = hexagonGrid()->at(mapFile->defaultPosition());
        LocationState::moveObjectToHexagon(player, hexagon, true);
        Logger::critical() << "Player hexagon: " << hexagon->number() << std::endl;

        // Just for testing
        {
            auto armor = GameObjectFactory::createObject(0x00000003); // powered armor
            player->setArmorSlot(dynamic_cast<GameArmorItemObject*>(armor));
            auto leftHand = GameObjectFactory::createObject(0x0000000C); // minigun
            player->setLeftHandSlot(dynamic_cast<GameWeaponItemObject*>(leftHand));
            auto rightHand = GameObjectFactory::createObject(0x00000007); // spear
            player->setRightHandSlot(dynamic_cast<GameWeaponItemObject*>(rightHand));
        }
    }

    // Location script
    if (mapFile->scriptId() > 0)
    {
        _locationScript = new VM(ResourceManager::intFileType(mapFile->scriptId()-1), Game::getInstance()->locationState());
    }


    // Generates floor and roof images
    {

        for (unsigned int i = 0; i != 100*100; ++i)
        {
            unsigned int x = (100 - i%100 - 1)*48 + 32*ceil(i/100);
            unsigned int y = ceil(i/100)*24 +(i%100)*12;

            unsigned int tileNum = mapFile->elevations()->at(_currentElevation)->floorTiles()->at(i);
            if (tileNum > 1)
            {
                auto tile = new Tile(tileNum, x, y);
                _floor->tiles()->push_back(tile);
            }

            tileNum = mapFile->elevations()->at(_currentElevation)->roofTiles()->at(i);
            if (tileNum > 1)
            {
                auto tile = new Tile(tileNum, x, y);
                _roof->tiles()->push_back(tile);
            }
        }
        //_floor->addEventHandler("keyup", this, (EventRecieverMethod) &LocationState::onKeyboardUp);
    }
}

void LocationState::onMouseDown(std::shared_ptr<MouseEvent> event)
{
    auto object = dynamic_cast<GameObject*>(event->reciever());
    if (!object) return;

    std::vector<int> icons;

    switch(object->type())
    {
        case GameObject::TYPE_DUDE:
            icons.push_back(Mouse::ICON_ROTATE);
            break;
        case GameObject::TYPE_SCENERY:
            icons.push_back(Mouse::ICON_LOOK);
            break;
        case GameObject::TYPE_CRITTER:
            icons.push_back(Mouse::ICON_TALK);
            break;
        default:
            return;
    }
    icons.push_back(Mouse::ICON_INVENTORY);
    icons.push_back(Mouse::ICON_SKILL);
    icons.push_back(Mouse::ICON_CANCEL);

    auto state = new CursorDropdownState(icons);
    state->setObject(object);
    auto game = Game::getInstance();
    game->pushState(state);
    event->setHandled(true);
}

void LocationState::onBackgroundClick(std::shared_ptr<MouseEvent> event)
{
}

void LocationState::onObjectClick(std::shared_ptr<MouseEvent> event)
{
}

void LocationState::onKeyUp(std::shared_ptr<KeyboardEvent> event)
{
}

void LocationState::render()
{
    _floor->render();
    //_roof->render();
    for (auto ui : *uiToRender())
    {
        ui->render();
    }
    _uiToRender.clear();
}

void LocationState::think()
{
    //State::think();

    /*
    auto game = Game::getInstance();
    auto hexagon = hexagons()->at(game->player()->hexagon()->number() + 6);
    findPath(game->player()->hexagon(), hexagon);
    */

    // UI thinking
    for (auto hexagon : *hexagonGrid()->hexagons())
    {
        for (auto it = hexagon->objects()->rbegin(); it != hexagon->objects()->rend(); ++it)
        {
            if ((*it)->ui()) (*it)->ui()->think();
        }
    }

    // location scrolling
    if (_scrollTicks + 10 < SDL_GetTicks())
    {
        _scrollTicks = SDL_GetTicks();
        unsigned int scrollDelta = 5;

        //Game::getInstance()->mouse()->setType(Mouse::ACTION);

        camera()->setXPosition(camera()->xPosition() + (_scrollLeft ? -scrollDelta : (_scrollRight ? scrollDelta : 0)));
        camera()->setYPosition(camera()->yPosition() + (_scrollTop ? -scrollDelta : (_scrollBottom ? scrollDelta : 0)));

        auto mouse = Game::getInstance()->mouse();

        // if scrolling is active
        if (_scrollLeft || _scrollRight || _scrollTop || _scrollBottom)
        {
            if (mouse->scrollState()) mouse->popState();

            unsigned int state;
            if (_scrollLeft)   state = Mouse::SCROLL_W;
            if (_scrollRight)  state = Mouse::SCROLL_E;
            if (_scrollTop)    state = Mouse::SCROLL_N;
            if (_scrollBottom) state = Mouse::SCROLL_S;
            if (_scrollLeft && _scrollTop)     state = Mouse::SCROLL_NW;
            if (_scrollLeft && _scrollBottom)  state = Mouse::SCROLL_SW;
            if (_scrollRight && _scrollTop)    state = Mouse::SCROLL_NE;
            if (_scrollRight && _scrollBottom) state = Mouse::SCROLL_SE;
            mouse->pushState(state);
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

    // Checking objects to render
    if (SDL_GetTicks() - _lastObjectsToRenderCheck >= 10)
    {
        _lastObjectsToRenderCheck = SDL_GetTicks();
        checkObjectsToRender();
    }

    if (_locationEnter)
    {
        _locationEnter = false;

        if (_locationScript) _locationScript->initialize();

        for (auto hexagon : *hexagonGrid()->hexagons())
        {
            for (auto object : *hexagon->objects())
            {
                // initialize scripts
                for (auto script : *object->scripts()) script->initialize();
            }
        }

        if (_locationScript) _locationScript->call("map_enter_p_proc");

        for (auto hexagon : *hexagonGrid()->hexagons())
        {
            for (auto object : *hexagon->objects())
            {
                // map_enter_p_proc
                for (auto script : *object->scripts()) script->call("map_enter_p_proc");
            }
        }
    }
    else
    {
        if (_scriptsTicks + 500 < SDL_GetTicks())
        {
            _scriptsTicks = SDL_GetTicks();
            if (_locationScript) _locationScript->call("map_update_p_proc");
            for (auto hexagon : *hexagonGrid()->hexagons())
            {
                for (auto object : *hexagon->objects())
                {
                    for (auto script : *object->scripts())
                    {
                        script->call("map_update_p_proc");
                        //script->call("look_at_p_proc");
                        //script->call("description_p_proc");
                        //script->call("critter_p_proc");
                        //script->call("timed_event_p_proc");
                    }
                 }
            }
        }
    }
}

void LocationState::handle(std::shared_ptr<Event> event)
{
    auto game = Game::getInstance();

    if (auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(event))
    {
        auto mouse = Game::getInstance()->mouse();

        // Right button pressed
        if (mouseEvent->name() == "mouseup" && mouseEvent->rightButton())
        {
            switch (mouse->state())
            {
                case Mouse::ACTION:
                {
                    auto hexagon = hexagonGrid()->hexagonAt(mouse->x() + camera()->x(), mouse->y() + camera()->y());
                    mouse->pushState(Mouse::HEXAGON_RED);
                    mouse->ui()->setX(hexagon->x() - camera()->x());
                    mouse->ui()->setY(hexagon->y() - camera()->y());
                    break;
                }
                case Mouse::HEXAGON_RED:
                {
                    mouse->popState();
                    break;
                }
            }
            event->setHandled(true);
        }

        // Left button down
        if (mouseEvent->name() == "mousedown" && mouseEvent->leftButton())
        {
            switch (mouse->state())
            {
                case Mouse::HEXAGON_RED:
                    // Preventing dropdown state
                    event->setHandled(true);
                    break;
            }
        }
        if (mouseEvent->name() == "mouseup" && mouseEvent->leftButton())
        {
            switch (mouse->state())
            {
                case Mouse::HEXAGON_RED:
                {
                    // Here goes the movement
                    auto hexagon = hexagonGrid()->hexagonAt(mouse->x() + camera()->x(), mouse->y() + camera()->y());
                    auto path = hexagonGrid()->findPath(game->player()->hexagon(), hexagon);
                    if (path.size())
                    {
                        moveObjectToHexagon(game->player(), hexagon);
                    }
                    event->setHandled(true);
                    break;
                }
            }
        }

        if (mouseEvent->name() == "mousemove")
        {
            switch (mouse->state())
            {
                case Mouse::HEXAGON_RED:
                {
                    auto hexagon = hexagonGrid()->hexagonAt(mouse->x() + camera()->x(), mouse->y() + camera()->y());
                    mouse->ui()->setX(hexagon->x() - camera()->x());
                    mouse->ui()->setY(hexagon->y() - camera()->y());
                    break;
                }
            }

            unsigned int scrollArea = 8;
            _scrollLeft = mouseEvent->x() < scrollArea ? true : false;
            _scrollRight = mouseEvent->x() > game->renderer()->width()- scrollArea ? true : false;
            _scrollTop = mouseEvent->y() < scrollArea ? true : false;
            _scrollBottom = mouseEvent->y() > game->renderer()->height() - scrollArea ? true : false;


            /*
            auto hexagon = hexagonAt(camera()->x() + mouseEvent->x(), camera()->y() + mouseEvent->y());
            _cursorNeigbors.clear();
            for (auto neighbor : *hexagon->neighbors())
            {
                auto ui = std::shared_ptr<Image>(new Image("art/intrface/msef001.frm"));
                ui->setX(neighbor->x() - camera()->x() - ui->width()*0.5);
                ui->setY(neighbor->y() - camera()->y() - ui->height());
                _cursorNeigbors.push_back(ui);
            }
            moveObjectToHexagon(game->player(), hexagon);
            Logger::critical() << "Pos: " << hexagon->number() << std::endl;
            */
        }
    }

    for (auto ui : *uiToRender())
    {
        if (event->handled()) return;
        if (auto activeUI = dynamic_cast<ActiveUI*>(ui)) activeUI->handle(event);
    }
}

void LocationState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    if (event->keyCode() == SDLK_F10)
    {
        Game::getInstance()->pushState(new ExitConfirmState());
        //event->setHandled(true);
    }
}

LocationCamera* LocationState::camera()
{
    return _camera;
}

void LocationState::checkObjectsToRender()
{
    _objectsToRender.clear();

    for (auto hexagon : *hexagonGrid()->hexagons())
    {
        for (auto it = hexagon->objects()->rbegin(); it != hexagon->objects()->rend(); ++it)
        {
            auto ui = dynamic_cast<ActiveUI*>((*it)->ui());
            if (!ui) continue;

            unsigned int x, y, width, height;

            width = ui->width();
            height = ui->height();

            auto animation = dynamic_cast<Animation*>((*it)->ui());
            if (animation)
            {
                x = hexagon->x() + ui->xOffset() - std::floor(width*0.5);
                y = hexagon->y() + ui->yOffset() - height;
            }
            else
            {
                x = hexagon->x() + ui->xOffset();
                y = hexagon->y() + ui->yOffset();
            }

            // check if object is out of camera borders
            if (x + width < camera()->x()) continue; // right
            if (y + height < camera()->y()) continue; // bottom
            if (x > camera()->x() + camera()->width()) continue; // left
            if (y > camera()->y() + camera()->height()) continue; // top

            ui->setX(hexagon->x() - camera()->x());
            ui->setY(hexagon->y() - camera()->y());


            _objectsToRender.push_back((*it));
        }
    }
}

void LocationState::setMVAR(unsigned int number, int value)
{
    if (number >= _MVARS.size())
    {
        throw Exception("LocationState::setMVAR(num, value) - num out of range: " + std::to_string((int)number));
    }
    _MVARS.at(number) = value;
}

int LocationState::MVAR(unsigned int number)
{
    if (number >= _MVARS.size())
    {
        throw Exception("LocationState::MVAR(num) - num out of range: " + std::to_string((int)number));
    }
    return _MVARS.at(number);
}

std::map<std::string, VMStackValue*>* LocationState::EVARS()
{
    return &_EVARS;
}

void LocationState::moveObjectToHexagon(GameObject* object, Hexagon* hexagon, bool calculateHexagons)
{
    auto oldHexagon = object->hexagon();
    if (oldHexagon)
    {
        for (auto it = oldHexagon->objects()->begin(); it != oldHexagon->objects()->end(); ++it)
        {
            if (*it == object)
            {
                oldHexagon->objects()->erase(it);
                break;
            }
        }
    }

    object->setHexagon(hexagon);
    hexagon->objects()->push_back(object);

    if (calculateHexagons)
    {
        //Game::getInstance()->locationState()->checkHexagonsWidthObjects();
    }
}

void LocationState::handleAction(GameObject* object, int action)
{
    switch (action)
    {

        case Mouse::ICON_ROTATE:
        {
            auto dude = dynamic_cast<GameDudeObject*>(object);
            if (!dude) throw Exception("LocationState::handleAction() - only Dude can be rotated");

            int orientation = dude->orientation() + 1;
            if (orientation > 5) orientation = 0;
            dude->setOrientation(orientation);

            break;
        }
        case Mouse::ICON_TALK:
        {
            for(auto script : *object->scripts())
            {
                script->call("talk_p_proc");
            }
        }

    }
}

std::vector<UI*>* LocationState::uiToRender()
{
    if (_uiToRender.size()) return &_uiToRender;

    _floatMessages.clear();
    for (auto object : _objectsToRender)
    {

        object->ui()->removeEventHandlers("mouseleftdown");
        object->ui()->addEventHandler("mouseleftdown", object, (EventRecieverMethod) &LocationState::onMouseDown);
        _uiToRender.push_back(object->ui());

        if (auto message = object->floatMessage())
        {
            if (SDL_GetTicks() - message->timestampCreated() >= 7000)
            {
                delete object->floatMessage();
                object->setFloatMessage(nullptr);
            }
            else
            {
                message->setX(object->hexagon()->x() - camera()->x() - message->width()*0.5);
                message->setY(object->hexagon()->y() - camera()->y() - 70 - message->height());
                _floatMessages.push_back(message);
            }
        }
    }

    for (auto message : _floatMessages)
    {
        _uiToRender.push_back(message);
    }

    return &_uiToRender;
}

HexagonGrid* LocationState::hexagonGrid()
{
    return _hexagonGrid;
}

}

