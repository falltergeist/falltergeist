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
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationQueue.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Renderer.h"
#include "Game.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "CritterObject.h"
#include "Defines.h"
#include "Object.h"
#include "DudeObject.h"
#include "../State/Location.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameObject::GameObject() : EventEmitter()
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
        _ui->addEventHandler("mouseleftdown", std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mouseleftclick", std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mousein", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mousemove", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->addEventHandler("mouseout", std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
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

    if ((trans() != TRANS_DEFAULT) || ((_type != TYPE_WALL) && !(_type == TYPE_SCENERY && _subtype == TYPE_SCENERY_GENERIC)))
    {
        _ui->render();
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


    if (_transparent)
    {
        int egg_x = dude->hexagon()->x() - camera->x() - 63 + dude->ui()->xOffset();
        int egg_y = dude->hexagon()->y() - camera->y() - 78 + dude->ui()->yOffset();

        int egg_dx = _ui->x() - egg_x;
        int egg_dy = _ui->y() - egg_y;

        auto egg = ResourceManager::texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { egg_x, egg_y, (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { _ui->x(), _ui->y(), (int)_ui->texture()->width(), (int)_ui->texture()->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            _ui->render();
            return;
        }

        if (!_tmptex) _tmptex = new Texture(_ui->texture()->width(),_ui->texture()->height());
        _ui->texture()->copyTo(_tmptex);

        //This is sloooow. But unfortunately sdl doesnt allow to blit over only alpha =/
        for (unsigned int x = 0; x < _ui->texture()->width(); x++)
        {
            for (unsigned int y = 0; y < _ui->texture()->height(); y++)
            {
                if (x+egg_dx >= egg->width()) continue;
                if (y+egg_dy >= egg->height()) continue;
                if (x+egg_dx < 0) continue;
                if (y+egg_dy < 0) continue;
                _tmptex->setPixel(x, y, _tmptex->pixel(x,y) & egg->pixel(x+egg_dx, y+egg_dy));
            }
        }
        Game::getInstance()->renderer()->drawTexture(_tmptex, _ui->x(),_ui->y());
    }
    else
    {
        _ui->render();
    }
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

void GameObject::use_p_proc()
{
    if (script() && script()->hasFunction("use_p_proc"))
    {
        script()
            ->setSourceObject(Game::getInstance()->player())
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

void GameObject::onUseAnimationActionFrame(Event* event, GameCritterObject* critter)
{
    use_p_proc();
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

}
}
