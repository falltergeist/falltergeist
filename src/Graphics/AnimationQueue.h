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

#ifndef FALLTERGEIST_ANIMATIONQUEUE_H
#define FALLTERGEIST_ANIMATIONQUEUE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Event/EventEmitter.h"
#include "../Graphics/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
class Animation;

class AnimationQueue : public ActiveUI
{
protected:
    bool _playing = false;
    bool _repeat = false;
    unsigned int _currentAnimation = 0;
    std::vector<Animation*> _animations;
public:
    AnimationQueue();
    virtual ~AnimationQueue();

    std::vector<Animation*>* animations();
    Animation* currentAnimation();

    void clear();
    void stop();
    void start();
    void setRepeat(bool value);


    virtual Texture* texture();
    virtual void render(bool eggTransparency = false, bool grayscale = false);
    virtual void think();
    virtual unsigned int pixel(unsigned int x, unsigned int y);


    virtual unsigned int width();
    virtual unsigned int height();
    virtual int xOffset();
    virtual int yOffset();

};

}
#endif // FALLTERGEIST_ANIMATIONQUEUE_H
