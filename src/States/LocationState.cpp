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
#include <iostream>

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameDefines.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/CursorDropdownState.h"
#include "../States/ExitConfirmState.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../States/LocationState.h"
#include "../States/PipBoyState.h"
#include "../States/MainMenuState.h"
#include "../States/SkilldexState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"
#include "../Engine/Hexagon.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    if (initialized()) return;
    State::init();

    auto game = Game::getInstance();

    // Creating 200x200 hexagonal map
    unsigned int index = 0;
    for (unsigned int q = 0; q != 200; ++q)
    {
        for (unsigned int p = 0; p != 200; ++p, ++index)
        {
            auto hexagon = std::shared_ptr<Hexagon>(new Hexagon(index));
            int x = 48*100 + 16*(q+1) - 24*p;
            int y = (q+1)*12 + 6*p + 12;
            if (p&1)
            {
                x -= 8;
                y -= 6;
            }
            hexagon->setX(x);
            hexagon->setY(y);
            _hexagons.push_back(hexagon);
        }
    }

    // Creating links between hexagons
    for (index = 0; index != 200*200; ++index)
    {
        // @todo
    }

    _camera = std::shared_ptr<LocationCamera>(new LocationCamera(game->renderer()->width(), game->renderer()->height(), 0, 0));



    game->mouse()->setType(Mouse::ACTION);

    _initPanel();
    setLocation("maps/klamall.map");
}

// PLAYER PANEL
void LocationState::_initPanel()
{
    auto game = Game::getInstance();
    // player panel background
    _panelUIs.push_back(std::shared_ptr<Image>(new Image("art/intrface/iface.frm")));

    auto panelX = (game->renderer()->width() - 640)*0.5;   // 640 -- X size of panel
    auto panelY = game->renderer()->height() - 99;         //  99 -- Y size of panel

    _panelUIs.back()->setX(panelX);
    _panelUIs.back()->setY(panelY);
    _panelUIs.back()->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onPanelMouseDown);

    // change hand button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, panelX+218, panelY+5)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onChangeHandButtonClick);

    // inventory button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_INVENTORY, panelX+211, panelY+40)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onInventoryButtonClick);

    // options button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_OPTIONS, panelX+210, panelY+61)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onOptionsButtonClick);

    // attack button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_ATTACK, panelX+267, panelY+25)));

    // hit points
    auto hitPoints = std::shared_ptr<SmallCounter>(new SmallCounter(panelX+471, panelY+40));
    hitPoints->setNumber(Game::getInstance()->player()->hitPoints());
    hitPoints->setType(SmallCounter::SIGNED);
    _panelUIs.push_back(hitPoints);

    // armor class
    auto armorClass = std::shared_ptr<SmallCounter>(new SmallCounter(panelX+472, panelY+76));
    armorClass->setNumber(Game::getInstance()->player()->armorClass());
    armorClass->setType(SmallCounter::SIGNED);
    _panelUIs.push_back(armorClass);

    // skilldex button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, panelX+523, panelY+5)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onSkilldexButtonClick);

    // map button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_MAP, panelX+526, panelY+39)));

    // cha button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_CHA, panelX+526, panelY+58)));

    // pip button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_PIP, panelX+526, panelY+77)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onPipBoyButtonClick);
}

void LocationState::setLocation(std::string name)
{    

    auto mapFile = ResourceManager::mapFileType(name);
    _currentElevation = mapFile->defaultElevation();

    // Set camera position on default
    camera()->setXPosition(hexagons()->at(mapFile->defaultPosition())->x());
    camera()->setYPosition(hexagons()->at(mapFile->defaultPosition())->y());

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
            CrossPlatform::debug("LocationState::setLocation() - cant create object with PID: " + std::to_string(mapObject->PID()), DEBUG_ERROR);
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

        auto hexagon = hexagons()->at(mapObject->hexPosition());
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

        auto hexagon = hexagons()->at(mapFile->defaultPosition());
        LocationState::moveObjectToHexagon(player, hexagon, true);

        // Just for testing
        {
            auto armor = GameObjectFactory::createObject(0x00000003); // powered armor
            player->setArmorSlot(std::dynamic_pointer_cast<GameArmorItemObject>(armor));
            auto leftHand = GameObjectFactory::createObject(0x0000000C); // minigun
            player->setLeftHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(leftHand));
            auto rightHand = GameObjectFactory::createObject(0x00000007); // spear
            player->setRightHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(rightHand));
        }
    }

    // Location script
    if (mapFile->scriptId() > 0)
    {
        _locationScript = std::shared_ptr<VM>(new VM(ResourceManager::intFileType(mapFile->scriptId()-1), Game::getInstance()->locationState()));
    }


    // Generates floor and roof images
    {
        auto tilesLst = ResourceManager::lstFileType("art/tiles/tiles.lst");

        unsigned int tilesWidth = 80*100;
        unsigned int tilesHeight = 36*100;

        _floor = std::shared_ptr<Image>(new Image(tilesWidth, tilesHeight));
        _roof  = std::shared_ptr<Image>(new Image(tilesWidth, tilesHeight));
        _floor->texture()->fill(0x000000FF);
        _roof->texture()->fill(0x000000FF);

        for (unsigned int i = 0; i != 100*100; ++i)
        {
            unsigned int x = (100 - i%100 - 1)*48 + 32*ceil(i/100);
            unsigned int y = ceil(i/100)*24 +(i%100)*12;

            auto floorTile = ResourceManager::texture("art/tiles/" + tilesLst->strings()->at(mapFile->elevations()->at(_currentElevation)->floorTiles()->at(i)));
            auto roofTile = ResourceManager::texture("art/tiles/" + tilesLst->strings()->at(mapFile->elevations()->at(_currentElevation)->roofTiles()->at(i)));
            floorTile->blitTo(_floor->texture(), x, y);
            roofTile->blitTo(_roof->texture(), x, y);
        }
        _floor->addEventHandler("keyup", this, (EventRecieverMethod) &LocationState::onKeyboardUp);
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

    auto state = std::shared_ptr<CursorDropdownState>(new CursorDropdownState(icons));
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

void LocationState::generateUi()
{
    _ui.clear();
    _floatMessages.clear();
    add(_floor);

    for (auto object : _objectsToRender)
    {
        object->ui()->removeEventHandlers("mouseleftdown");
        object->ui()->addEventHandler("mouseleftdown", object.get(), (EventRecieverMethod) &LocationState::onMouseDown);
        add(object->ui());

        if (auto message = object->floatMessage())
        {
            if (SDL_GetTicks() - message->timestampCreated() >= 7000)
            {
                object->floatMessage().reset();
            }
            else
            {
                message->setX(object->hexagon()->x() - camera()->x() - message->width()*0.5);
                message->setY(object->hexagon()->y() - camera()->y() - 70 - message->height());
                _floatMessages.push_back(message);
            }
        }
    }

     //add(_roof);

    _floor->setX(-camera()->x());
    _floor->setY(-camera()->y());
    //_roof->setX(-_location->camera()->x());
    //_roof->setY(-_location->camera()->y() - 100);

    for (auto message : _floatMessages)
    {
        add(message);
    }

    for (auto ui : _panelUIs)
    {
        add(ui);
    }

    auto item = Game::getInstance()->player()->currentHandSlot();
    if (item)
    {
        auto itemUi = item->inventoryDragUi();
        itemUi->setX(_panelUIs.at(0)->x() + 360 - itemUi->width()*0.5);
        itemUi->setY(_panelUIs.at(0)->y() + 60 - itemUi->height()*0.5);
        add(itemUi);
    }
}

void LocationState::think()
{
    State::think();

    // location scrolling
    if (_scrollTicks + 10 < SDL_GetTicks())
    {
        _scrollTicks = SDL_GetTicks();
        unsigned int scrollDelta = 5;
        Game::getInstance()->mouse()->setType(Mouse::ACTION);
        if (_scrollLeft)
        {
            camera()->setXPosition(camera()->xPosition() - scrollDelta);
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_W);
        }
        if (_scrollRight)
        {
            camera()->setXPosition(camera()->xPosition() + scrollDelta);
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_E);
        }
        if (_scrollTop)
        {
            camera()->setYPosition(camera()->yPosition() - scrollDelta);
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_N);
        }
        if (_scrollBottom)
        {
            camera()->setYPosition(camera()->yPosition() + scrollDelta);
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_S);
        }

        if (_scrollLeft && _scrollTop)
        {
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_NW);
        }
        if (_scrollLeft && _scrollBottom)
        {
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_SW);
        }
        if (_scrollRight && _scrollTop)
        {
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_NE);
        }
        if (_scrollRight && _scrollBottom)
        {
            Game::getInstance()->mouse()->setType(Mouse::SCROLL_SE);
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
        if (_locationScript) _locationScript->call("map_enter_p_proc");

        for (auto hexagon : *hexagons())
        {
            for (auto object : *hexagon->objects())
            {
                // initialize scripts
                for (auto script : *object->scripts()) script->initialize();

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
            for (auto hexagon : *hexagons())
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

    generateUi();
}

void LocationState::handle(std::shared_ptr<Event> event)
{
    if (auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(event))
    {
        auto game = Game::getInstance();
        unsigned int scrollArea = 8;
        if (mouseEvent->name() == "mousemove")
        {
            _scrollLeft = mouseEvent->x() < scrollArea ? true : false;
            _scrollRight = mouseEvent->x() > game->renderer()->width()- scrollArea ? true : false;
            _scrollTop = mouseEvent->y() < scrollArea ? true : false;
            _scrollBottom = mouseEvent->y() > game->renderer()->height() - scrollArea ? true : false;
        }
    }
    State::handle(event);
}

void LocationState::onChangeHandButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto player = Game::getInstance()->player();
    player->setCurrentHand(player->currentHand() == GameCritterObject::HAND_LEFT ? GameCritterObject::HAND_RIGHT : GameCritterObject::HAND_LEFT);
}

void LocationState::onPanelMouseDown(std::shared_ptr<MouseEvent> event)
{
    event->setHandled(true);
}

void LocationState::onInventoryButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<InventoryState>(new InventoryState()));
}

void LocationState::onOptionsButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<GameMenuState>(new GameMenuState()));
}

void LocationState::onSkilldexButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<SkilldexState>(new SkilldexState()));
}

void LocationState::onPipBoyButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<PipBoyState>(new PipBoyState()));
}

void LocationState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    if (event->keyCode() == SDLK_F10)
    {
        Game::getInstance()->pushState(std::shared_ptr<ExitConfirmState>(new ExitConfirmState()));
        //event->setHandled(true);
    }
}

std::vector<std::shared_ptr<Hexagon>>* LocationState::hexagons()
{
    return &_hexagons;
}

std::shared_ptr<LocationCamera> LocationState::camera()
{
    return _camera;
}

void LocationState::checkObjectsToRender()
{
    _objectsToRender.clear();

    for (auto hexagon : _hexagonsWithObjects)
    {
        for (auto it = hexagon->objects()->rbegin(); it != hexagon->objects()->rend(); ++it)
        {
            auto object = *it;
            auto ui = std::dynamic_pointer_cast<ActiveUI>(object->ui());
            if (!ui) continue;

            unsigned int x, y, width, height;

            width = ui->width();
            height = ui->height();

            auto animation = std::dynamic_pointer_cast<Animation>(object->ui());
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


            _objectsToRender.push_back(object);
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

std::map<std::string, std::shared_ptr<VMStackValue>>* LocationState::EVARS()
{
    return &_EVARS;
}

void LocationState::moveObjectToHexagon(std::shared_ptr<GameObject> object, std::shared_ptr<Hexagon> hexagon, bool calculateHexagons)
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
        Game::getInstance()->locationState()->checkHexagonsWidthObjects();
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

void LocationState::checkHexagonsWidthObjects()
{
    _hexagonsWithObjects.clear();
    for (auto hexagon : *hexagons())
    {
        if (hexagon->objects()->size() > 0)
        {
            _hexagonsWithObjects.push_back(hexagon);
        }
    }
}


}
