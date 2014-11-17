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
 */

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/AnimationQueue.h"
#include "../Engine/Game.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/PathFinding/Hexagon.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameObject.h"
#include "../Game/GameDefines.h"
#include "../States/LocationState.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

GameObject::GameObject() : EventReciever(), EventEmitter()
{
}

GameObject::~GameObject()
{
    delete _ui;
    delete _floatMessage;
}

int GameObject::type()
{
    return _type;
}

int GameObject::subtype()
{
    return _subtype;
}

int GameObject::PID()
{
    return _PID;
}

void GameObject::setPID(int value)
{
    _PID = value;
}

int GameObject::FID()
{
    return _FID;
}

void GameObject::setFID(int value)
{
    if (_FID == value) return;
    _FID = value;
    _generateUi();
}

int GameObject::elevation()
{
    return _elevation;
}

void GameObject::setElevation(int value)
{
    if (value < 0 || value > 3)
    {
        throw Exception("GameObject::setElevation() - value out of range: " + std::to_string(value));
    }
    _elevation = value;
}

int GameObject::orientation()
{
    return _orientation;
}

void GameObject::setOrientation(int value)
{
    if (value < 0 || value > 5)
    {
        throw Exception("GameObject::setOrientation() - value out of range: " + std::to_string(value));
    }

    if (_orientation == value) return;

    _orientation = value;
    _generateUi();
}

std::string GameObject::name()
{
    return _name;
}

void GameObject::setName(std::string value)
{
    _name = value;
}

std::string GameObject::description()
{
    return _description;
}

void GameObject::setDescription(std::string value)
{
    _description = value;
}

VM* GameObject::script()
{
    return _script;
}

void GameObject::setScript(VM* script)
{
    delete _script;
    _script = script;
}

ActiveUI* GameObject::ui()
{
    return _ui;
}

void GameObject::setUI(ActiveUI* ui)
{
    delete _ui;
    _ui = ui;
    _ui->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onMouseDown);
}

void GameObject::_generateUi()
{
    delete _ui; _ui = 0;
    auto frm = ResourceManager::frmFileType(FID());
    if (frm)
    {
        frm->rgba(ResourceManager::palFileType("color.pal")); // TODO: figure out, why not calling this brokes animated overlays
        if (frm->framesPerDirection() > 1)
        {
            auto queue = new AnimationQueue();
            queue->animations()->push_back(new Animation(ResourceManager::FIDtoFrmName(FID()), orientation()));
            _ui = queue;
        }
        else if (frm->animatedPalette())
        {
            _ui = new AnimatedImage(frm, orientation());
        }
        else
        {
            _ui = new Image(frm, orientation());
        }
    }

    if (_ui)
    {
        _ui->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onMouseDown);
    }
}

bool GameObject::canWalkThru()
{
    return _canWalkThru;
}

void GameObject::setCanWalkThru(bool value)
{
    _canWalkThru = value;
}

Hexagon* GameObject::hexagon()
{
    return _hexagon;
}

void GameObject::setHexagon(Hexagon* hexagon)
{
    _hexagon = hexagon;
}

TextArea* GameObject::floatMessage()
{
    return _floatMessage;
}

void GameObject::setFloatMessage(TextArea* floatMessage)
{
    _floatMessage = floatMessage;
}

void GameObject::render()
{
    if (!_ui) return;

    auto camera = Game::getInstance()->locationState()->camera();
    _ui->setX(hexagon()->x() - camera->x() - std::floor(static_cast<double>(_ui->width())/2));
    _ui->setY(hexagon()->y() - camera->y() - _ui->height());

    setInRender(false);

    if (_ui->x() + (int)_ui->width() < 0) return;
    if (_ui->x() > (int)camera->width()) return;
    if (_ui->y() + (int)_ui->height() < 0) return;
    if (_ui->y() > (int)camera->height()) return;

    setInRender(true);


    if (auto message = floatMessage())
    {
        if (SDL_GetTicks() - message->timestampCreated() >= 7000)
        {
            delete floatMessage();
            setFloatMessage(nullptr);
        }
        else
        {
            message->setX(_ui->x() + _ui->width()*0.5 - message->width()*0.5);
            message->setY(_ui->y() - 4 - message->height());
            message->render();
        }
    }

    _ui->render();
}

void GameObject::think()
{
    if (_ui) _ui->think();
}

void GameObject::handle(Event* event)
{
    if (_ui) _ui->handle(event);
}

bool GameObject::inRender()
{
    return _inRender;
}

void GameObject::setInRender(bool value)
{
    _inRender = value;
}

void GameObject::description_p_proc()
{
}

void GameObject::use_p_proc()
{
    script()->call("use_p_proc");
}

void GameObject::destroy_p_proc()
{
}

void GameObject::look_at_p_proc()
{
}

void GameObject::map_enter_p_proc()
{
}

void GameObject::map_exit_p_proc()
{
}

void GameObject::map_update_p_proc()
{
}

void GameObject::pickup_p_proc()
{
}

void GameObject::spatial_p_proc()
{
}

void GameObject::use_obj_on_p_proc()
{
}

void GameObject::onUseAnimationActionFrame(Event* event)
{
    auto object = (GameObject*)event->reciever();
    object->use_p_proc();
}

}
