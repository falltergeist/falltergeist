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

#ifndef FALLTERGEIST_RENDERER_H
#define FALLTERGEIST_RENDERER_H

// C++ standard includes
#include <vector>
#include <memory>
#include <string>

// Falltergeist includes
#include "../../Engine/Graphics/Texture.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{

class Renderer
{
protected:
    unsigned int _width;
    unsigned int _height;
    std::string _name;
    SDL_Window* _window;
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    virtual void init();

    virtual void beginFrame();
    virtual void endFrame();

    unsigned int width();
    unsigned int height();
    void setCaption(std::string caption);
    SDL_Window* window();

    virtual std::string name();

    virtual void registerTexture(Texture* texture);
    virtual void registerTexture(std::shared_ptr<Texture> texture);
    virtual void unregisterTexture(Texture* texture);
    virtual void drawTexture( std::shared_ptr<Texture> texture, int x, int y, int sourceX = 0, int sourceY = 0, int unsigned sourceWidth = 0, unsigned int sourceHeight = 0);
    virtual void drawTexture( Texture* texture, int x, int y, int sourceX = 0, int sourceY = 0, int unsigned sourceWidth = 0, unsigned int sourceHeight = 0);

    virtual std::shared_ptr<Texture> screenshot();

};

}
#endif // FALLTERGEIST_RENDERER_H
