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
 */

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../../Engine/Graphics/Renderer.h"
#include "../../Engine/Graphics/UI.h"
#include "../../Engine/Game.h"
#include "../../Engine/State.h"
#include "../../Engine/Input/Mouse.h"

// Third party includes

namespace Falltergeist
{

Renderer::Renderer(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
}

void Renderer::think()
{
    if (_fadeDone) return;
    unsigned int _nt = SDL_GetTicks();
    if (_nt-_lt>_delay)
    {
        _alpha+=_step;
        if (_alpha<=0 || _alpha>255)
        {
            _alpha=0;
            _fadeDone=true;
            return;
        }
        _lt=_nt;
    }
    _fadeColor.a=_alpha;
}

bool Renderer::fadeDone()
{
    return _fadeDone;
}

void Renderer::_fade(unsigned int r, unsigned int g, unsigned int b, unsigned int time, short dir)
{
    _fadeColor.r=r;
    _fadeColor.g=g;
    _fadeColor.b=b;
    if (dir<0)
    {
      _fadeColor.a=255;
      _alpha=255;
    }
    else
    {
      _fadeColor.a=0;
      _alpha=0;
    }
    _step=dir;
    _fadeDone=false;
    _delay=round(time/256);
}

void Renderer::fadeIn(unsigned int r, unsigned int g, unsigned int b, unsigned int time)
{
    _fade(r,g,b,time, -1);
}

void Renderer::fadeOut(unsigned int r, unsigned int g, unsigned int b, unsigned int time)
{
    _fade(r,g,b,time, 1);
}


void Renderer::beginFrame()
{
    think();
}

void Renderer::endFrame()
{
}

unsigned int Renderer::width()
{
    return _width;
}

unsigned int Renderer::height()
{
    return _height;
}

void Renderer::registerTexture(Texture* texture)
{
}

void Renderer::unregisterTexture(Texture* texture)
{
}

void Renderer::drawTexture(Texture* texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
}

Texture* Renderer::screenshot()
{
    return 0;
}

std::string Renderer::name()
{
    return _name;
}

void Renderer::setCaption(std::string caption)
{
    SDL_SetWindowTitle(_window, caption.c_str());
}

SDL_Window* Renderer::window()
{
    return _window;
}

}
