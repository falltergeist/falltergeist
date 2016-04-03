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
#include "../Game/Object.h"

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Exception.h"
#include "../Format/Frm/File.h"
#include "../Format/Msg/File.h"
#include "../Format/Msg/Message.h"
#include "../functions.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../Game/CritterObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
using Base::make_unique;

namespace Game
{

Object::Object() : Event::EventTarget(Game::getInstance()->eventDispatcher())
{
}

Object::~Object()
{
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

VM::Script* Object::script() const
{
    return _script.get();
}

void Object::setScript(VM::Script* script)
{
    _script.reset(script);
}

UI::Base* Object::ui() const
{
    return _ui.get();
}

void Object::setUI(UI::Base* ui)
{
    _ui.reset(ui);
    addUIEventHandlers();
}

void Object::addUIEventHandlers()
{
    if (_ui)
    {
        // TODO: these event handlers probably need to be set in State::Location
        _ui->mouseDownHandler().add(std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->mouseClickHandler().add(std::bind(&State::Location::onObjectMouseEvent, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->mouseInHandler().add(std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        // TODO: get rid of mousemove handler?
        _ui->mouseMoveHandler().add(std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
        _ui->mouseOutHandler().add(std::bind(&State::Location::onObjectHover, Game::getInstance()->locationState(), std::placeholders::_1, this));
    }
}


void Object::_generateUi()
{
    _ui.reset();
    auto frm = ResourceManager::getInstance()->frmFileType(FID());
    if (frm)
    {
        if (frm->framesPerDirection() > 1 || frm->directions()->size() > 1)
        {
            auto queue = make_unique<UI::AnimationQueue>();
            queue->animations().push_back(make_unique<UI::Animation>(ResourceManager::getInstance()->FIDtoFrmName(FID()), orientation()));
            _ui = std::move(queue);
        }
        else
        {
            _ui =  make_unique<UI::Image>(frm, orientation());

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
    return _floatMessage.get();
}

void Object::setFloatMessage(std::unique_ptr<UI::TextArea> message)
{
    _floatMessage = std::move(message);
}

static bool to_right_of(const Point& p1, const Point& p2)
{
    return (double)(p2.x() - p1.x()) <= ((double)(p2.y() - p1.y()) * (4.0/3.0));
}

static bool in_front_of(const Point& p1, const Point& p2)
{
  return (double)(p2.x() - p1.x()) <= ((double)(p2.y() - p1.y()) * -4.0);
}

void Object::renderText()
{
    if (auto message = floatMessage())
    {
        if (SDL_GetTicks() - message->timestampCreated() >= 7000)
        {
            setFloatMessage(nullptr);
        }
        else
        {
            message->setPosition(_ui->position() + Point(
                _ui->size().width() / 2 - message->size().width() / 2,
                -4 - message->textSize().height()
            ));
            message->render();
        }
    }
}

void Object::render()
{

    if (!_ui || !_hexagon) return;

    auto camera = Game::getInstance()->locationState()->camera();
    _ui->setPosition(
        hexagon()->position()
        - camera->topLeft()
        - Point(_ui->size().width() / 2, _ui->size().height())
    );

    // don't draw if outside of screen
    if (!Graphics::Rect::intersects(_ui->position(), _ui->size(), Point(0, 0), camera->size()))
    {
        setInRender(false);
        return;
    }

    setInRender(true);
    _ui->setLight(true);
    _ui->setLightLevel(hexagon()->light());
    _ui->render(_useEggTransparency() && _isIntersectsWithEgg());
}


bool Object::_isIntersectsWithEgg()
{
    //only walls and scenery are affected by egg
    if (_type != Type::WALL && _type !=Type::SCENERY)
    {
        return false;
    }
    auto dude = Game::getInstance()->player();
    Hexagon * dudeHex;

    if (dude->movementQueue()->size())
        dudeHex = dude->movementQueue()->back();
    else
        dudeHex = dude->hexagon();

    auto objPos = hexagon()->position();
    auto dudePos = dudeHex->position();

    bool noBlockTrans = false;
    bool transparent;

    switch (_lightOrientation)
    {
        case Orientation::EW:
        case Orientation::WC:
            transparent = in_front_of(objPos, dudePos);
            noBlockTrans = to_right_of(objPos, dudePos);
            break;
        case Orientation::NC:
            transparent = (to_right_of(dudePos, objPos) | in_front_of(objPos, dudePos));
            break;
        case Orientation::SC:
            transparent = (in_front_of(objPos, dudePos) && to_right_of(dudePos, objPos));
            break;
        default:
            transparent = to_right_of(dudePos, objPos);
            noBlockTrans = in_front_of(dudePos, objPos);
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
    if (_ui)
    {
        _ui->handle(event);
    }
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
        auto descr = description();
        if (descr.empty())
        {
            descr = _t(MSG_TYPE::MSG_PROTO, 493);
        }
        Game::getInstance()->locationState()->displayMessage(descr);
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
        animation->actionFrameHandler().clear();
        animation->animationEndedHandler().add([this, critter](Event::Event* event){
            this->onUseAnimationEnd(event, critter);
        });
    }
    else throw Exception("No animation for object!");
}

void Object::onUseAnimationEnd(Event::Event* event, CritterObject* critter)
{
    critter->setActionAnimation("aa")->stop();
}

void Object::setTrans(Graphics::TransFlags::Trans value)
{
    _trans = value;
    if (_ui)
    {
        _ui->setTrans(value);
    }
}

Graphics::TransFlags::Trans Object::trans() const
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
    setFlat((flags & 0x00000008));
    setCanWalkThru((flags & 0x00000010));
    setCanLightThru((flags & 0x20000000));
    setCanShootThru((flags & 0x80000000));

    if (flags & 0x00004000) setTrans(Graphics::TransFlags::Trans::RED);
    if (flags & 0x00008000) setTrans(Graphics::TransFlags::Trans::NONE);
    if (flags & 0x00010000) setTrans(Graphics::TransFlags::Trans::WALL);
    if (flags & 0x00020000) setTrans(Graphics::TransFlags::Trans::GLASS);
    if (flags & 0x00040000) setTrans(Graphics::TransFlags::Trans::STEAM);
    if (flags & 0x00080000) setTrans(Graphics::TransFlags::Trans::ENERGY);
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


unsigned int Object::defaultFrame()
{
    return _defaultFrame;
}

void Object::setDefaultFrame(unsigned int frame)
{
    _defaultFrame = frame;
    if (_ui)
    {
        if (auto anim = dynamic_cast<UI::AnimationQueue*>(_ui.get()))
        {
            anim->currentAnimation()->setCurrentFrame(_defaultFrame);
        }
    }
}

bool Object::_useEggTransparency()
{
    return false;
}

void Object::renderOutline(int type)
{
        if (!_ui || !_hexagon) return;

        auto camera = Game::getInstance()->locationState()->camera();
        _ui->setPosition(
                hexagon()->position()
                - camera->topLeft()
                - Point(_ui->size().width() / 2, _ui->size().height())
        );

        // don't draw if outside of screen
        if (!Graphics::Rect::intersects(_ui->position(), _ui->size(), Point(0, 0), camera->size()))
        {
            setInRender(false);
            return;
        }

        _ui->setOutline(type);
        _ui->render(false);
        _ui->setOutline(0);
}

}
}
