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

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Engine/Animation.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

Animation::Animation(libfalltergeist::FrmFileType * frm, int x, int y)
{
    _surfaceSets = new std::vector<std::vector<Surface *> *>;
    _currentFrame = 0;
    _currentSurfaceSet = 0;
    _frameRate = 200;
    _lastTicks = SDL_GetTicks();
    loadFromFrmFile(frm);
}

Animation::Animation(const char * filename, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _surfaceSets = new std::vector<std::vector<Surface *> *>;
    _currentFrame = 0;
    _currentSurfaceSet = 0;
    _frameRate = 200;
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

int Animation::xOffset()
{
    int offset = 0;
    offset += InteractiveSurface::xOffset();
    offset += surfaces()->at(0)->width()/2;
    offset -= surface()->width()/2;

    for (unsigned int i = 0; i <= _currentFrame; i++)
    {
        offset += surfaces()->at(i)->xOffset();
    }
    return offset;
}

int Animation::yOffset()
{
    int offset = 0;
    offset += InteractiveSurface::yOffset();
    offset += surfaces()->at(0)->height();
    offset -= surface()->height();

    for (unsigned int i = 0; i <= _currentFrame; i++)
    {
        offset += surfaces()->at(i)->yOffset();
    }
    return offset;
}

std::vector<Surface *> * Animation::surfaces()
{
    return _surfaceSets->at(_currentSurfaceSet);
}

void Animation::loadFromFrmFile(libfalltergeist::FrmFileType * frm)
{
    if (frm->framesPerSecond() > 0)
    {
        _frameRate = ceil(1000 / frm->framesPerSecond());
    }

    // for each direction
    for (unsigned int i = 0; i != 6; ++i)
    {
        if (i > 0 && frm->directions()->at(i)->dataOffset() == frm->directions()->at(0)->dataOffset()) break;
        std::vector<Surface *> * frameset = new std::vector<Surface *>;
        // for each frame
        for (unsigned int j = 0; j != frm->framesPerDirection(); ++j)
        {
            Surface * surface = new Surface(frm, i, j);
            if (j == 0)
            {
                surface->setXOffset(frm->directions()->at(i)->shiftX());
                surface->setYOffset(frm->directions()->at(i)->shiftY());
            }
            else
            {
                surface->setXOffset(frm->directions()->at(i)->frames()->at(j)->offsetX());
                surface->setYOffset(frm->directions()->at(i)->frames()->at(j)->offsetY());
            }
            frameset->push_back(surface);
        }
        _surfaceSets->push_back(frameset);
    }
}

int Animation::xOffsetMin()
{
    int offsetMin = 0;

    for (unsigned int j = 0; j != surfaces()->size(); ++j)
    {
        int offset = 0;
        offset += InteractiveSurface::xOffset();
        offset += surfaces()->at(0)->width()/2;
        offset -= surfaces()->at(j)->width()/2;

        for (unsigned int i = 0; i <= j; i++)
        {
            offset += surfaces()->at(i)->xOffset();
        }

        if (offset < offsetMin) offsetMin = offset;
    }
    return offsetMin;
}

void Animation::loadFromFrmFile(std::string filename)
{
    libfalltergeist::FrmFileType * frm = ResourceManager::frmFileType(filename);
    if (!frm)
    {
        debug("Can't find FRM file "+ filename + "\n", DEBUG_ERROR);
    }
    return loadFromFrmFile(frm);
}

Surface * Animation::surface()
{
    if (needRedraw())
    {
        draw();
        setNeedRedraw(false);
    }
    return _surfaceSets->at(_currentSurfaceSet)->at(_currentFrame);
}

SDL_Surface * Animation::sdl_surface()
{
    return surface()->sdl_surface();
}


}
