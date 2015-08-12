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

#ifndef FALLTERGEIST_RENDERER_H
#define FALLTERGEIST_RENDERER_H

// C++ standard includes
#include <vector>
#include <memory>
#include <string>

// Falltergeist includes
#include "../Graphics/Texture.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{

class Renderer
{
protected:
    unsigned int _width;
    unsigned int _height;

    short _fadeStep = 0;
    unsigned int _fadeTimer = 0;
    unsigned int _fadeDelay = 0;
    unsigned int _fadeAlpha = 0;
    bool _fadeDone = true;
    SDL_Color _fadeColor = {0, 0, 0, 0};

    bool _inmovie = false;

    float _scaleX = 1.0;
    float _scaleY = 1.0;

    std::string _name;
    SDL_Window* _sdlWindow;
    SDL_Renderer* _sdlRenderer;

public:
    Renderer(unsigned int width, unsigned int height);
    virtual ~Renderer();

    virtual void init();

    virtual void beginFrame();
    virtual void endFrame();
    virtual void think();

    unsigned int width();
    unsigned int height();
    float scaleX();
    float scaleY();

    bool fadeDone();
    bool fading();

    virtual void fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);
    virtual void fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);

    void setCaption(const std::string& caption);
    SDL_Window* sdlWindow();
    SDL_Renderer* sdlRenderer();

    virtual std::string name();

    virtual void drawTexture(Texture* texture, int x, int y, int sourceX = 0, int sourceY = 0, int unsigned sourceWidth = 0, unsigned int sourceHeight = 0);

    virtual Texture* screenshot();
};

}
#endif // FALLTERGEIST_RENDERER_H
