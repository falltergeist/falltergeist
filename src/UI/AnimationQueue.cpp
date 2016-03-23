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
#include "../UI/AnimationQueue.h"

// C++ standard includes

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Event/Event.h"
#include "../UI/Animation.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
using namespace Base;

AnimationQueue::AnimationQueue() : Falltergeist::UI::Base()
{
}

AnimationQueue::~AnimationQueue()
{
    clear();
}

std::vector<std::unique_ptr<Animation>>& AnimationQueue::animations()
{
    return _animations;
}

void AnimationQueue::clear()
{
    _currentAnimation = 0;
    _playing = false;
    _repeat = false;
    _animations.clear();
}

void AnimationQueue::stop()
{
    _playing = false;
    _currentAnimation = 0;
    currentAnimation()->stop();
}

void AnimationQueue::start()
{
    _playing = true;
}

void AnimationQueue::setRepeat(bool value)
{
    _repeat = value;
}

void AnimationQueue::render(bool eggTransparency)
{
    currentAnimation()->setLightLevel(_lightLevel);
    currentAnimation()->setLight(light());
    currentAnimation()->setTrans(_trans);
    currentAnimation()->setPosition(this->position());
    currentAnimation()->render(eggTransparency);
}

void AnimationQueue::think()
{
    if (_playing)
    {
        if (currentAnimation()->ended())
        {
            // not last animation in queue
            if (_currentAnimation < _animations.size() - 1)
            {
                _currentAnimation++;
                currentAnimation()->stop(); // rewind
                currentAnimation()->play();
            }
            else
            {
                if (!_repeat)
                {
                    emitEvent(make_unique<Event::Event>("animationEnded"), animationEndedHandler());
                    _playing = false;
                    return;
                }
                else
                {
                    _currentAnimation = 0;
                    currentAnimation()->stop();
                    currentAnimation()->play();
                }
            }
        }
        else if (!currentAnimation()->playing())
        {
            currentAnimation()->play();
        }

        currentAnimation()->think();
    }
}

Animation* AnimationQueue::currentAnimation() const
{
    return _animations.at(_currentAnimation).get();
}

Size AnimationQueue::size() const
{
    return currentAnimation()->size();
}

Point AnimationQueue::offset() const
{
    return currentAnimation()->offset();
}

Event::Handler& AnimationQueue::animationEndedHandler()
{
    return _animationEndedHandler;
}

bool AnimationQueue::opaque(const Point &pos) {
    currentAnimation()->setPosition(this->position());
    return currentAnimation()->opaque(pos);
}
}
}
