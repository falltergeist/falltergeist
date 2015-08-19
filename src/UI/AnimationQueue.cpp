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
#include "../UI/AnimationQueue.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"
#include "../UI/Animation.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

AnimationQueue::AnimationQueue() : Falltergeist::UI::Base()
{
}

AnimationQueue::~AnimationQueue()
{
    clear();
}

std::vector<Animation*>* AnimationQueue::animations()
{
    return &_animations;
}

void AnimationQueue::clear()
{
    _currentAnimation = 0;
    _playing = false;
    _repeat = false;
    while (!_animations.empty())
    {
        delete _animations.back();
        _animations.pop_back();
    }
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
    currentAnimation()->setX(this->x());
    currentAnimation()->setY(this->y());
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
                    auto event = new Event::Event("animationEnded");
                    emitEvent(event);
                    delete event;
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
        else
        {
            currentAnimation()->play();
        }

        currentAnimation()->think();
    }
}

Graphics::Texture* AnimationQueue::texture() const
{
    return currentAnimation()->texture();
}

unsigned int AnimationQueue::pixel(unsigned int x, unsigned int y)
{
    currentAnimation()->setX(this->x());
    currentAnimation()->setY(this->y());
    return currentAnimation()->pixel(x, y);
}

Animation* AnimationQueue::currentAnimation() const
{
    return _animations.at(_currentAnimation);
}

unsigned int AnimationQueue::width() const
{
    return currentAnimation()->width();
}

unsigned int AnimationQueue::height() const
{
    return currentAnimation()->height();
}

int AnimationQueue::xOffset() const
{
    return currentAnimation()->xOffset();
}

int AnimationQueue::yOffset() const
{
    return currentAnimation()->yOffset();
}

}
}
