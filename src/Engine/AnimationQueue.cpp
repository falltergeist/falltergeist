/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// Falltergeist includes
#include "../Engine/AnimationQueue.h"
#include "../Engine/Animation.h"

// Third party includes

namespace Falltergeist
{

AnimationQueue::AnimationQueue()
{
}

AnimationQueue::~AnimationQueue()
{
}

bool AnimationQueue::enabled()
{
    return _enabled;
}

void AnimationQueue::setEnabled(bool value)
{
    _enabled = value;
}

std::map<Animation*, int>* AnimationQueue::queue()
{
    return &_queue;
}

void AnimationQueue::add(Animation* animation, int delay)
{
    _queue.insert(std::make_pair(animation, delay));
}

void AnimationQueue::clear()
{
    _queue.clear();
}

void AnimationQueue::think()
{

}

Surface* AnimationQueue::surface()
{
    if (this->animation())
    {
        return this->animation()->surface();
    }
    return 0;
}

Animation* AnimationQueue::animation()
{
    int i = 0;
    for (auto animation : _queue)
    {
        if (i == _currentAnimation) return animation.first;
        i++;
    }
    return 0;
}


int AnimationQueue::currentAnimation()
{
    return _currentAnimation;
}

void AnimationQueue::setCurrentAnimation(int value)
{
    _currentAnimation = value;
}

}
