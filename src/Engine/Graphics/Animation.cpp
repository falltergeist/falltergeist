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

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../../Engine/Graphics/Animation.h"
#include "../../Engine/Graphics/AnimationFrame.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/Game.h"
#include "../../Engine/Graphics/Renderer.h"
#include "../../Engine/ResourceManager.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Animation::Animation() : ActiveUI()
{
}

Animation::Animation(std::string frmName, unsigned int direction) : ActiveUI()
{
    auto frm = ResourceManager::frmFileType(frmName);
    setTexture(ResourceManager::texture(frmName));


    int xOffset = frm->shiftX(direction);
    int yOffset = frm->shiftY(direction);


    // Смещение кадра в текстуре анимации
    unsigned int x = 0;
    unsigned int y = 0;

    for (unsigned int d = 0; d != direction; ++d)
    {
        y += frm->height(d); //? может i - 1
    }


    for (auto f = 0; f != frm->framesPerDirection(); ++f)
    {
        xOffset += frm->offsetX(direction, f);
        yOffset += frm->offsetY(direction, f);

        auto frame = new AnimationFrame();
        frame->setWidth(frm->width(direction, f));
        frame->setHeight(frm->height(direction, f));
        frame->setXOffset(xOffset);
        frame->setYOffset(yOffset);
        frame->setY(y);
        frame->setX(x);

        auto fps = frm->framesPerSecond();
        if (fps == 0)
        {
            frame->setDuration(1000);
        }
        else
        {
            frame->setDuration(std::round(1000.0/static_cast<double>(frm->framesPerSecond())));
        }

        x += frm->width(direction);
        frames()->push_back(frame);
    }
}


Animation::~Animation()
{
    while (!_animationFrames.empty())
    {
        delete _animationFrames.back();
        _animationFrames.pop_back();
    }
}

std::vector<AnimationFrame*>* Animation::frames()
{
    return &_animationFrames;
}

int Animation::xOffset()
{
    return frames()->at(_currentFrame)->xOffset();
}

int Animation::yOffset()
{
    return frames()->at(_currentFrame)->yOffset();
}

void Animation::think()
{
    if (SDL_GetTicks() - _frameTicks >= frames()->at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        if (_currentFrame < frames()->size() - 1)
        {
            _currentFrame += 1;
        }
        else
        {
            _currentFrame = 0;
        }
       auto frame = frames()->at(_currentFrame);
       setXOffset(frame->xOffset() - (int)std::floor(frame->width()*0.5));
       setYOffset(frame->yOffset() - frame->height());

    }
}

void Animation::render()
{
    auto frame = frames()->at(_currentFrame);
    Game::getInstance()->renderer()->drawTexture(_texture, x(),y(), frame->x(), frame->y(), frame->width(), frame->height());
}

unsigned int Animation::height()
{
    return frames()->at(_currentFrame)->height();
}

unsigned int Animation::width()
{
    return frames()->at(_currentFrame)->width();
}

unsigned int Animation::pixel(unsigned int x, unsigned int y)
{
    auto frame = frames()->at(_currentFrame);

    if (x < 0 || x > frame->width()) return 0;
    if (y < 0 || y > frame->height()) return 0;

    return ActiveUI::pixel(x + frame->x(), y + frame->y());
}

}
