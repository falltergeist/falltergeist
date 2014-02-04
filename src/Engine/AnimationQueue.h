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

#ifndef FALLTERGEIST_ANIMATIONQUEUE_H
#define FALLTERGEIST_ANIMATIONQUEUE_H

// C++ standard includes
#include <map>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Animation;
class Surface;

class AnimationQueue
{
protected:
    int _currentAnimation = 0;
    int _repeat = -1; // forever
    bool _enabled = false;
    std::map<Animation*, int> _queue; // Animation and delay before start
public:
    AnimationQueue();
    virtual ~AnimationQueue();

    bool enabled();
    void start();
    void stop();

    int repeat();
    void setRepeat(int value);

    int currentAnimation();
    void setCurrentAnimation(int value);

    std::map<Animation*, int>* queue();

    void add(Animation* animation, int delay = -1);
    void clear();

    void think();
    Animation* animation();
};

}
#endif // FALLTERGEIST_ANIMATIONQUEUE_H
