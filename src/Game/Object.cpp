/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../Game/Object.h"

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Exception.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Game/CritterObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

Object::Object() : Event::EventTarget(Game::getInstance()->eventDispatcher())
{
}

Object::~Object()
{
    delete _ui;
    delete _floatMessage;
}

Object::Type Object::type() const
{
    return _type;
}

int Object::PID() const
{
    return _PID;
}

void Object::setPID(int value)
{
    _PID = value;
}

int Object::FID() const
{
    return _FID;
}

void Object::setFID(int value)
{
    if (_FID == value) return;
    _FID = value;
    _generateUi();
}

int Object::elevation() const
{
    return _elevation;
}

void Object::setElevation(int value)
{
    if (value < 0 || value > 3)
    {
        throw Exception("Object::setElevation() - value out of range: " + std::to_string(value));
    }
    _elevation = value;
}

Orientation Object::orientation() const
{
    return _orientation;
}

void Object::setOrientation(Orientation value)
{
    if (_orientation == value) return;

    _orientation = value;
    _generateUi();
}

std::string Object::name() const
{
    return _name;
}

void Object::setName(const std::string& value)
{
    _name = value;
}

std::string Object::description() const
{
    return _description;
}

void Object::setDescription(const std::string& value)
{
    _description = value;
}

VM* Object::script() const
{
    return _script;
}

void Object::setScript(VM* script)
{
    delete _script;
    _script = script;
}

UI::Base* Object::ui() const
{
    return _ui;
}

void Object::setUI(UI::Base* ui)
{
    delete _ui;
    _ui = ui;
    addUIEventHandlers();
}

void Object::addUIEventHandlers()
{
    if (_ui)
    {
        _ui->addEventHandler("mouseleftdown", std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mouseleftclick", std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mousein", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mousemove", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mouseout", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
    }
}


void Object::_generateUi()
{
    delete _ui; _ui = 0;
    auto frm = ResourceManager::getInstance()->frmFileType(FID());
    if (frm)
    {
        frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")); // TODO: figure out, why not calling this brokes animated overlays
        if (frm->framesPerDirection() > 1)
        {
            auto queue = new UI::AnimationQueue();
            queue->animations()->push_back(new UI::Animation(ResourceManager::getInstance()->FIDtoFrmName(FID()), orientation()));
            _ui = queue;
        }
        else if (frm->animatedPalette())
        {
            _ui = new UI::AnimatedImage(frm, orientation());
        }
        else
        {
            _ui = new UI::Image(frm, orientation());
        }
    }

    addUIEventHandlers();
}

bool Object::canWalkThru() const
{
    return _canWalkThru;
}

void Object::setCanWalkThru(bool value)
{
    _canWalkThru = value;
}

bool Object::canLightThru() const
{
    return _canLightThru;
}

void Object::setCanLightThru(bool value)
{
    _canLightThru = value;
}

bool Object::canShootThru() const
{
    return _canShootThru;
}

void Object::setCanShootThru(bool value)
{
    _canShootThru = value;
}

bool Object::wallTransEnd() const
{
    return _wallTransEnd;
}

void Object::setWallTransEnd(bool value)
{
    _wallTransEnd = value;
}

Hexagon* Object::hexagon() const
{
    return _hexagon;
}

void Object::setHexagon(Hexagon* hexagon)
{
    _hexagon = hexagon;
}

UI::TextArea* Object::floatMessage() const
{
    return _floatMessage;
}

void Object::setFloatMessage(UI::TextArea* floatMessage)
{
    _floatMessage = floatMessage;
}

static bool to_right_of(int x1, int y1, int x2, int y2)
{
    return (double)(x2 - x1) <= ((double)(y2 - y1) * (double)(4.0/3.0));
}

static bool in_front_of(int x1, int y1, int x2, int y2)
{
  return (double)(x2 - x1) <= ((double)(y2 - y1) * -4.0);
}

void Object::renderText()
{
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
}

void Object::render()
{
    if (!_ui) return;

    auto camera = Game::getInstance()->locationState()->camera();
    _ui->setX(hexagon()->x() - camera->x() - std::floor((double)_ui->width() / 2));
    _ui->setY(hexagon()->y() - camera->y() - _ui->height());

    setInRender(false);

    if (_ui->x() + (int)_ui->width() < 0) return;
    if (_ui->x() > camera->width()) return;
    if (_ui->y() + (int)_ui->height() < 0) return;
    if (_ui->y() > camera->height()) return;

    setInRender(true);

    _ui->render(_useEggTransparency() && _getEggTransparency());
}


bool Object::_getEggTransparency()
{
    auto dude = Game::getInstance()->player();
    Hexagon *hex;

    if (dude->movementQueue()->size())
        hex = dude->movementQueue()->back();
    else
        hex = dude->hexagon();

    auto obj_x = hexagon()->x();
    auto obj_y = hexagon()->y();

    auto dude_x = hex->x();
    auto dude_y = hex->y();

    bool noBlockTrans = false;
    bool transparent;

    switch (_lightOrientation)
    {
        case Orientation::EW:
        case Orientation::WC:
            transparent = in_front_of(obj_x, obj_y, dude_x, dude_y);
            noBlockTrans = to_right_of(obj_x, obj_y, dude_x, dude_y);
            break;
        case Orientation::NC:
            transparent = (to_right_of(dude_x, dude_y, obj_x, obj_y) | in_front_of(obj_x, obj_y, dude_x, dude_y));
            break;
        case Orientation::SC:
            transparent = (in_front_of(obj_x, obj_y, dude_x, dude_y) && to_right_of(dude_x, dude_y, obj_x, obj_y));
            break;
        default:
            transparent = to_right_of(dude_x, dude_y, obj_x, obj_y);
            noBlockTrans = in_front_of(dude_x, dude_y, obj_x, obj_y);
            break;
    }

    return (noBlockTrans && wallTransEnd())
        ? false
        : transparent;
}

void Object::think()
{
    if (_ui) _ui->think();
}

void Object::handle(Event::Event* event)
{
    if (_ui) _ui->handle(event);
}

bool Object::inRender() const
{
    return _inRender;
}

void Object::setInRender(bool value)
{
    _inRender = value;
}

void Object::description_p_proc()
{
    Logger::info("SCRIPT") << "description_p_proc() - 0x" << std::hex << PID() << " " << name() << " " << (script() ? script()->filename() : "") << std::endl;
    bool useDefault = true;
    if (script() && script()->hasFunction("description_p_proc"))
    {
        script()
            ->setSourceObject(Game::getInstance()->player())
            ->call("description_p_proc");
        if (script()->overrides())
            useDefault = false;
    }
    if (useDefault)
    {
        Game::getInstance()->locationState()->displayMessage(description());
    }
}

void Object::use_p_proc(CritterObject* usedBy)
{
    if (script() && script()->hasFunction("use_p_proc"))
    {
        script()
            ->setSourceObject(usedBy)
            ->call("use_p_proc");
    }
}

void Object::destroy_p_proc()
{
    if (script() && script()->hasFunction("destroy_p_proc"))
    {
        script()
            ->setSourceObject(Game::getInstance()->player())
            ->call("destroy_p_proc");
    }
}

void Object::look_at_p_proc()
{
    bool useDefault = true;
    if (script() && script()->hasFunction("look_at_p_proc"))
    {
        script()
            ->setSourceObject(Game::getInstance()->player())
            ->call("look_at_p_proc");
        if (script()->overrides())
            useDefault = false;
    }
    if (useDefault)
    {
        auto protoMsg = ResourceManager::getInstance()->msgFileType("text/english/game/proto.msg");
        char buf[512];
        sprintf(buf, protoMsg->message(490)->text().c_str(), name().c_str());
        Game::getInstance()->locationState()->displayMessage(std::string(buf));
    }
}

void Object::map_enter_p_proc()
{
    if (script())
    {
        script()->call("map_enter_p_proc");
    }
}

void Object::map_exit_p_proc()
{
    if (script())
    {
        script()->call("map_exit_p_proc");
    }
}

void Object::map_update_p_proc()
{
    if (script())
    {
        script()->call("map_update_p_proc");
    }
}

void Object::pickup_p_proc(CritterObject* pickedUpBy)
{
    if (script() && script()->hasFunction("pickup_p_proc"))
    {
        script()
            ->setSourceObject(pickedUpBy)
            ->call("pickup_p_proc");
    }
    // @TODO: standard handler
}

void Object::spatial_p_proc()
{
}

void Object::use_obj_on_p_proc(Object* objectUsed, CritterObject* usedBy)
{
    if (script() && script()->hasFunction("use_obj_on_p_proc"))
    {
        script()
            ->setSourceObject(usedBy)
            ->setTargetObject(objectUsed)
            ->call("use_obj_on_p_proc");
    }
    // @TODO: standard handlers for drugs, etc.
}

void Object::onUseAnimationActionFrame(Event::Event* event, CritterObject* critter)
{
    use_p_proc(critter);
    UI::Animation* animation = dynamic_cast<UI::Animation*>(critter->ui());
    if (animation)
    {
        animation->removeEventHandlers("actionFrame");
        animation->addEventHandler("animationEnded", [this, critter](Event::Event* event){
            this->onUseAnimationEnd(event, critter);
        });
    }
    else throw Exception("No animation for object!");
}

void Object::onUseAnimationEnd(Event::Event* event, CritterObject* critter)
{
    critter->setActionAnimation("aa")->stop();
}

void Object::setTrans(Trans value)
{
    _trans = value;
    if (_ui)
    {
        SDL_Color modifier = _ui->texture()->colorModifier();
        switch (_trans)
        {
            case Trans::GLASS:
                modifier.a = 128;
                break;
            case Trans::ENERGY:
                modifier = {200, 200, 0, 128};
                break;
            case Trans::RED:
                modifier = {255, 0, 0, 128};
                break;
            case Trans::NONE:
            default:
                modifier = {255, 255, 255, 255};
                break;
        }
        _ui->texture()->setColorModifier(modifier);
    }
}

Object::Trans Object::trans() const
{
    return _trans;
}

void Object::setLightOrientation(Orientation orientation)
{
    _lightOrientation = orientation;
}

unsigned short Object::lightOrientation() const
{
    return _lightOrientation;
}

void Object::setLightIntensity(unsigned int intensity)
{
    _lightIntensity = intensity;
}

unsigned int Object::lightIntensity() const
{
    return _lightIntensity;
}

void Object::setLightRadius(unsigned int radius)
{
    _lightRadius = radius;
}

unsigned int Object::lightRadius() const
{
    return _lightRadius;
}

void Object::setFlags(unsigned int flags)
{
    setFlat((flags & 0x00000008) != 0);
    setCanWalkThru((flags & 0x00000010) != 0);
    setCanLightThru((flags & 0x20000000) != 0);
    setCanShootThru((flags & 0x80000000) != 0);

    if (flags & 0x00004000) setTrans(Object::Trans::RED);
    if (flags & 0x00008000) setTrans(Object::Trans::NONE);
    if (flags & 0x00010000) setTrans(Object::Trans::WALL);
    if (flags & 0x00020000) setTrans(Object::Trans::GLASS);
    if (flags & 0x00040000) setTrans(Object::Trans::STEAM);
    if (flags & 0x00080000) setTrans(Object::Trans::ENERGY);
    if (flags & 0x10000000) setWallTransEnd(true);
}

bool Object::flat() const
{
    return _flat;
}

void Object::setFlat(bool value)
{
    _flat = value;
}

bool Object::_useEggTransparency()
{
    return false;
}

}
}
