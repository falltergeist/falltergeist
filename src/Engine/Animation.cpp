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
 */

#include "../Engine/Animation.h"
#include "../Engine/ResourceManager.h"
#include <iostream>

namespace Falltergeist
{

Animation::Animation(libfalltergeist::FrmFileType * frm, int x, int y)
{
    _surfaceSets = new std::vector<std::vector<Surface *> *>;
    _currentFrame = 0;
    _currentSurfaceSet = 0;
    _frameRate = 400;
    _lastTicks = SDL_GetTicks();
    loadFromFrmFile(frm);
}

Animation::Animation(const char * filename, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _surfaceSets = new std::vector<std::vector<Surface *> *>;
    _currentFrame = 0;
    _currentSurfaceSet = 0;
    _frameRate = 400;
    _lastTicks = SDL_GetTicks();
    loadFromFrmFile(filename);
}

Animation::~Animation()
{
    while (!_surfaceSets->empty())
    {
        while (!_surfaceSets->back()->empty())
        {
            delete _surfaceSets->back()->back();
            _surfaceSets->back()->pop_back();
        }
        delete _surfaceSets->back();
        _surfaceSets->pop_back();
    }
    delete _surfaceSets;
}

void Animation::think()
{
    if(_lastTicks + _frameRate > SDL_GetTicks()) return;
    _lastTicks = SDL_GetTicks();
    _currentFrame++;
    if (_currentFrame >= _surfaceSets->at(_currentSurfaceSet)->size())
    {
        _currentFrame = 0;
    }
}

Animation * Animation::loadFromFrmFile(libfalltergeist::FrmFileType * frm)
{
    libfalltergeist::PalFileType * pal = ResourceManager::palFileType("color.pal");

    _frameRate = 1000 / frm->framesPerSecond();

    // for each direction
    for (unsigned int i = 0; i != 6; ++i)
    {
        if (i > 0 && frm->directions()->at(i)->dataOffset() == frm->directions()->at(0)->dataOffset()) break;
        std::vector<Surface *> * frameset = new std::vector<Surface *>;
        // for each frame
        for (unsigned int j = 0; j != frm->framesPerDirection(); ++j)
        {
            Surface * surface = new Surface(frm, i, j);
            /*
            int width = frm->directions()->at(i)->frames()->at(j)->width();
            int height = frm->directions()->at(i)->frames()->at(j)->height();
            Surface * surface = new Surface(width,height);
            int z = 0;
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    // 12 - frame data offset
                    unsigned int colorIndex = frm->directions()->at(i)->frames()->at(j)->colorIndexes()->at(z);
                    unsigned int color = *pal->color(colorIndex);
                    if (colorIndex == 0) color = 0;
                    surface->pixel(x,y,color);
                    z++;
                }
            }
            */
            frameset->push_back(surface);
        }
        _surfaceSets->push_back(frameset);
    }
    return this;
}

Animation * Animation::loadFromFrmFile(const char * filename)
{
    libfalltergeist::FrmFileType * frm = ResourceManager::frmFileType(filename);
    if (!frm)
    {
        std::cout << "can't find FRM file " << filename << std::endl;
    }
    return loadFromFrmFile(frm);
}

Surface * Animation::surface()
{
    if (needRedraw())
    {
        draw();
        needRedraw(false);
    }
    return _surfaceSets->at(_currentSurfaceSet)->at(_currentFrame);
}

SDL_Surface * Animation::sdl_surface()
{
    return surface()->sdl_surface();
}


}
