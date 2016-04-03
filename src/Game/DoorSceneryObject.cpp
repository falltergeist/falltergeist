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
#include "../Game/DoorSceneryObject.h"

// C++ standard includes

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

DoorSceneryObject::DoorSceneryObject() : SceneryObject()
{
    _subtype = Subtype::DOOR;
}

DoorSceneryObject::~DoorSceneryObject()
{
}

bool DoorSceneryObject::opened() const
{
    return _opened;
}

void DoorSceneryObject::setOpened(bool value)
{
    _opened = value;
    setCanLightThru(_opened);
}

bool DoorSceneryObject::locked() const
{
    return _locked;
}

void DoorSceneryObject::setLocked(bool value)
{
    _locked = value;
}

void DoorSceneryObject::use_p_proc(CritterObject* usedBy)
{
    Object::use_p_proc(usedBy);
    if (script() && script()->overrides()) return;

    if (!opened())
    {
        if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui()))
        {
            queue->start();
            // TODO:  i'm not sure. maybe we just need to reset animation progress on reverse change
            queue->currentAnimation()->stop();
            queue->currentAnimation()->setReverse(false);
            queue->animationEndedHandler().add(std::bind(&DoorSceneryObject::onOpeningAnimationEnded, this, std::placeholders::_1));
            if (_soundId) Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/sodoors") + _soundId + ".acm");
        }
    }
    else
    {
        if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui()))
        {
            queue->start();
            queue->currentAnimation()->stop();
            queue->currentAnimation()->setReverse(true);
            queue->animationEndedHandler().add(std::bind(&DoorSceneryObject::onClosingAnimationEnded, this, std::placeholders::_1));
            if (_soundId) Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/scdoors") + _soundId + ".acm");
        }
    }
}

bool DoorSceneryObject::canWalkThru() const
{
    return opened();
}

void DoorSceneryObject::onOpeningAnimationEnded(Event::Event* event)
{
    auto queue = (UI::AnimationQueue*)event->target();
    setOpened(true);
    queue->animationEndedHandler().clear();
    queue->stop();
    Game::getInstance()->locationState()->initLight();
    Logger::info() << "Door opened: " << opened() << std::endl;
}

void DoorSceneryObject::onClosingAnimationEnded(Event::Event* event)
{
    auto queue = (UI::AnimationQueue*)event->target();
    setOpened(false);
    queue->animationEndedHandler().clear();
    queue->stop();
    Game::getInstance()->locationState()->initLight();
    Logger::info() << "Door opened: " << opened() << std::endl;
}

}
}
