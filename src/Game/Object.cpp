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

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Exception.h"
#include "../Event/EventSender.h"
#include "../Game/CritterObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/Object.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationQueue.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

using namespace std::placeholders;

namespace Falltergeist
{
namespace Game
{

GameObject::GameObject() : EventSender()
{
}

GameObject::~GameObject()
{
    delete _ui;
    delete _floatMessage;        
}

int GameObject::type() const
{
    return _type;
}

int GameObject::subtype() const
{
    return _subtype;
}

int GameObject::PID() const
{
    return _PID;
}

void GameObject::setPID(int value)
{
    _PID = value;
}

int GameObject::FID() const
{
    return _FID;
}

void GameObject::setFID(int value)
{
    if (_FID == value) return;
    _FID = value;
    _generateUi();
}

int GameObject::elevation() const
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

int GameObject::orientation() const
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

std::string GameObject::name() const
{
    return _name;
}

void GameObject::setName(std::string value)
{
    _name = value;
}

std::string GameObject::description() const
{
    return _description;
}

void GameObject::setDescription(std::string value)
{
    _description = value;
}

VM* GameObject::script() const
{
    return _script;
}

void GameObject::setScript(VM* script)
{
    delete _script;
    _script = script;
}

ActiveUI* GameObject::ui() const
{
    return _ui;
}

void GameObject::setUI(ActiveUI* ui)
{
    delete _ui;
    _ui = ui;
    addUIEventHandlers();
}

void GameObject::addUIEventHandlers()
{
    if (_ui)
    {
        auto state = Game::getInstance()->locationState();

        _ui->addEventHandler("mouseleftdown",  std::bind(&State::Location::onObjectMouseEvent, state, _1, this));
        _ui->addEventHandler("mouseleftclick", std::bind(&State::Location::onObjectMouseEvent, state, _1, this));
        _ui->addEventHandler("mousein",        std::bind(&State::Location::onObjectHover,      state, _1, this));
        _ui->addEventHandler("mousemove",      std::bind(&State::Location::onObjectHover,      state, _1, this));
        _ui->addEventHandler("mouseout",       std::bind(&State::Location::onObjectHover,      state, _1, this));
    }
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

    addUIEventHandlers();
}

bool GameObject::canWalkThru() const
{
    return _canWalkThru;
}

void GameObject::setCanWalkThru(bool value)
{
    _canWalkThru = value;
}

bool GameObject::canLightThru() const
{
    return _canLightThru;
}

void GameObject::setCanLightThru(bool value)
{
    _canLightThru = value;
}

bool GameObject::canShootThru() const
{
    return _canShootThru;
}

void GameObject::setCanShootThru(bool value)
{
    _canShootThru = value;
}

bool GameObject::wallTransEnd() const
{
    return _wallTransEnd;
}

void GameObject::setWallTransEnd(bool value)
{
    _wallTransEnd = value;
}

Hexagon* GameObject::hexagon() const
{
    return _hexagon;
}

void GameObject::setHexagon(Hexagon* hexagon)
{
    _hexagon = hexagon;
}

TextArea* GameObject::floatMessage() const
{
    return _floatMessage;
}

void GameObject::setFloatMessage(TextArea* floatMessage)
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

void GameObject::renderText()
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

void GameObject::render()
{
    if (!_ui) return;

    auto camera = Game::getInstance()->locationState()->camera();
    _ui->setX(hexagon()->x() - camera->x() - std::floor((double)_ui->width()/2));
    _ui->setY(hexagon()->y() - camera->y() - _ui->height());

    setInRender(false);

    if (_ui->x() + (int)_ui->width() < 0) return;
    if (_ui->x() > (int)camera->width()) return;
    if (_ui->y() + (int)_ui->height() < 0) return;
    if (_ui->y() > (int)camera->height()) return;

    setInRender(true);

    if ((trans() != TRANS_DEFAULT) || ((_type != TYPE_WALL) && !(_type == TYPE_SCENERY && _subtype == TYPE_SCENERY_GENERIC)))
    {
        _ui->render(false);
        return;
    }

/*    if ((_type == TYPE_SCENERY && _subtype == TYPE_SCENERY_GENERIC) && !canWalkThru())
    {
        _ui->render();
        return;
    }
*/
    auto dude = Game::getInstance()->player();

    Hexagon* hex;

    if (dude->movementQueue()->size())
        hex = dude->movementQueue()->back();
    else
        hex = dude->hexagon();

    auto obj_x = hexagon()->x();
    auto obj_y = hexagon()->y();

    auto dude_x = hex->x();
    auto dude_y = hex->y();

    _transparent = false;

    bool noBlockTrans = false;

    switch (_lightOrientation)
    {
        case ORIENTATION_EW:
        case ORIENTATION_WC:
            _transparent = in_front_of(obj_x, obj_y, dude_x, dude_y);
            noBlockTrans = to_right_of(obj_x, obj_y, dude_x, dude_y);
            break;
        case ORIENTATION_NC:
            _transparent = (to_right_of(dude_x, dude_y, obj_x, obj_y) | in_front_of(obj_x, obj_y, dude_x, dude_y));
            break;
        case ORIENTATION_SC:
            _transparent = (in_front_of(obj_x, obj_y, dude_x, dude_y) && to_right_of(dude_x, dude_y, obj_x, obj_y));
            break;
        default:
            _transparent = to_right_of(dude_x, dude_y, obj_x, obj_y);
            noBlockTrans = in_front_of(dude_x, dude_y, obj_x, obj_y);
            break;
    }

    if (noBlockTrans && wallTransEnd())
        _transparent = false;


    _ui->render(_transparent);

}

void GameObject::think()
{
    if (_ui) _ui->think();
}

void GameObject::handle(Event* event)
{
    if (_ui) _ui->handle(event);
}

bool GameObject::inRender() const
{
    return _inRender;
}

void GameObject::setInRender(bool value)
{
    _inRender = value;
}

void GameObject::description_p_proc()
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

void GameObject::use_p_proc(GameCritterObject* usedBy)
{
    if (script() && script()->hasFunction("use_p_proc"))
    {
        script()
            ->setSourceObject(usedBy)
            ->call("use_p_proc");
    }
}

void GameObject::destroy_p_proc()
{
    if (script() && script()->hasFunction("destroy_p_proc"))
    {
        script()
            ->setSourceObject(Game::getInstance()->player())
            ->call("destroy_p_proc");
    }
}

void GameObject::look_at_p_proc()
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
        auto protoMsg = ResourceManager::msgFileType("text/english/game/proto.msg");
        char buf[512];
        sprintf(buf, protoMsg->message(490)->text().c_str(), name().c_str());
        Game::getInstance()->locationState()->displayMessage(std::string(buf));
    }
}

void GameObject::map_enter_p_proc()
{
    if (script())
    {
        script()->call("map_enter_p_proc");
    }
}

void GameObject::map_exit_p_proc()
{
    if (script())
    {
        script()->call("map_exit_p_proc");
    }
}

void GameObject::map_update_p_proc()
{
    if (script())
    {
        script()->call("map_update_p_proc");
    }
}

void GameObject::pickup_p_proc(GameCritterObject* pickedUpBy)
{
    if (script() && script()->hasFunction("pickup_p_proc"))
    {
        script()
            ->setSourceObject(pickedUpBy)
            ->call("pickup_p_proc");
    }
    // @TODO: standard handler
}

void GameObject::spatial_p_proc()
{
}

void GameObject::use_obj_on_p_proc(GameObject* objectUsed, GameCritterObject* usedBy)
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

void GameObject::onUseAnimationActionFrame(Event* event, GameCritterObject* critter)
{
    use_p_proc(critter);
    Animation* animation = dynamic_cast<Animation*>(critter->ui());
    if (animation)
    {
        animation->removeEventHandlers("actionFrame");
        animation->addEventHandler("animationEnded", [this, critter](Event* event){
            this->onUseAnimationEnd(event, critter);
        });
    }
    else throw Exception("No animation for object!");
}

void GameObject::onUseAnimationEnd(Event* event, GameCritterObject* critter)
{
    critter->setActionAnimation("aa")->stop();
}

void GameObject::setTrans(unsigned int value)
{
    _trans = value;
    if (_ui)
    {
        SDL_Color modifier = _ui->texture()->colorModifier();
        switch (_trans)
        {
            case TRANS_GLASS:
                modifier.a = 128;
                break;
            case TRANS_ENERGY:
                modifier = {200, 200, 0, 128};
                break;
            case TRANS_RED:
                modifier = {255, 0, 0, 128};
                break;
            case TRANS_NONE:
            default:
                modifier = {255, 255, 255, 255};
                break;
        }
        _ui->texture()->setColorModifier(modifier);
    }
}

unsigned int GameObject::trans() const
{
    return _trans;
}

void GameObject::setLightOrientation(unsigned short orientation)
{
    _lightOrientation = orientation;
}

unsigned short GameObject::lightOrientation() const
{
    return _lightOrientation;
}

void GameObject::setLightIntensity(unsigned int intensity)
{
    _lightIntensity = intensity;
}

unsigned int GameObject::lightIntensity() const
{
    return _lightIntensity;
}

void GameObject::setLightRadius(unsigned int radius)
{
    _lightRadius = radius;
}

unsigned int GameObject::lightRadius() const
{
    return _lightRadius;
}

void GameObject::setFlags(unsigned int flags)
{
    setFlat(flags & 0x00000008);
    setCanWalkThru(flags & 0x00000010);
    setCanLightThru(flags & 0x20000000);
    setCanShootThru(flags & 0x80000000);

    if (flags & 0x00004000) setTrans(GameObject::TRANS_RED);
    if (flags & 0x00008000) setTrans(GameObject::TRANS_NONE);
    if (flags & 0x00010000) setTrans(GameObject::TRANS_WALL);
    if (flags & 0x00020000) setTrans(GameObject::TRANS_GLASS);
    if (flags & 0x00040000) setTrans(GameObject::TRANS_STEAM);
    if (flags & 0x00080000) setTrans(GameObject::TRANS_ENERGY);
    if (flags & 0x10000000) setWallTransEnd(true);

}

bool GameObject::flat() const
{
    return _flat;
}

void GameObject::setFlat(bool value)
{
    _flat = value;
}

}
}
