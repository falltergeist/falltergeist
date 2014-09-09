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
#include <iostream>
#include <cmath>

// Falltergeist includes
#include "../../Engine/Graphics/Animation.h"
#include "../../Engine/Graphics/AnimationFrame.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/ResourceManager.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Animation::Animation() : ActiveUI()
{
    _animationFrames = new std::vector<AnimationFrame*>;
}

Animation::Animation(std::string frmName, unsigned int direction) : ActiveUI()
{
    _animationFrames = new std::vector<AnimationFrame*>;
    auto frm = ResourceManager::frmFileType(frmName);

    _animationTexture = ResourceManager::texture(frmName);

    int xOffset = frm->shiftX(direction);
    int yOffset = frm->shiftY(direction);


    // Смещение кадра в текстуре анимации
    unsigned int x = 0;
    unsigned int y = 0;

    for (auto d = 0; d != direction; ++d)
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
            frame->setDuration(1000/frm->framesPerSecond());
        }

        x += frm->width(direction);
        _animationFrames->push_back(frame);


    }
}


Animation::~Animation()
{
    // Не удаляем текстуру, т.к. она загружена из ResourceManager
    _animationTexture = 0;
    while(!_animationFrames->empty())
    {
        delete _animationFrames->back();
        _animationFrames->pop_back();
    }
    delete _animationFrames;
}

std::vector<AnimationFrame*>* Animation::frames()
{
    return _animationFrames;
}

Texture* Animation::texture()
{
    if (_texture) return _texture;

    AnimationFrame* frame = _animationFrames->at(_currentFrame);

    _texture = new Texture(frame->width(), frame->height());
    _animationTexture->copyTo(_texture, 0, 0, frame->x(), frame->y(), frame->width(), frame->height());

    setXOffset(frame->xOffset() - (int)std::ceil(frame->width()*0.5));
    setYOffset(frame->yOffset() - frame->height());

    return _texture;
}

int Animation::xOffset()
{
    return _animationFrames->at(_currentFrame)->xOffset();
}

int Animation::yOffset()
{
    return _animationFrames->at(_currentFrame)->yOffset();
}

void Animation::think()
{
    if (SDL_GetTicks() - _frameTicks >= _animationFrames->at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        if (_currentFrame < _animationFrames->size() - 1)
        {
            _currentFrame += 1;
        }
        else
        {
            _currentFrame = 0;
        }
        delete _texture;
        _texture = 0;
    }
}

unsigned int Animation::height()
{
    return _animationFrames->at(_currentFrame)->height();
}

unsigned int Animation::width()
{
    return _animationFrames->at(_currentFrame)->width();
}

}
