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

#ifndef FALLTERGEIST_ANIMATION_H
#define FALLTERGEIST_ANIMATION_H

// C++ standard includes
#include <vector>
#include <string>

// Falltergeist includes
#include "../../Engine/ActiveUI.h"

// Third party includes


namespace Falltergeist
{
class AnimationFrame;

class Animation : public ActiveUI
{
protected:
    std::vector<std::shared_ptr<AnimationFrame>> _animationFrames;
    std::shared_ptr<Texture> _animationTexture;
    unsigned int _currentFrame = 0;
    unsigned int _frameTicks = 0;
public:
    Animation();
    Animation(std::string frmName, unsigned int direction = 0);
    ~Animation();
    std::vector<std::shared_ptr<AnimationFrame>>* frames();
    virtual void think();
    virtual void render();
    virtual int xOffset();
    virtual int yOffset();
    virtual unsigned int width();
    virtual unsigned int height();
};

}
#endif // FALLTERGEIST_ANIMATION_H
