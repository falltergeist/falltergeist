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

// Falltergeist includes
#include "../Engine/Graphics/Texture.h"
#include "../Engine/ResourceManager.h"
#include "../UI/AnimatedImage.h"
#include "../Engine/Graphics/AnimatedPalette.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"

// Third party includes

namespace Falltergeist
{

AnimatedImage::AnimatedImage(std::shared_ptr<libfalltergeist::FrmFileType> frm, unsigned int direction)
{

    setTexture(new Texture(frm->width(), frm->height()));
    _texture->loadFromRGBA(frm->rgba(ResourceManager::palFileType("color.pal")));
    setXOffset(frm->offsetX(direction) + frm->shiftX(direction) - width()/2);
    setYOffset(frm->offsetY(direction) + frm->shiftY(direction) - height());

    AnimatedPalette*  palette=new AnimatedPalette();
    auto masks = frm->animatedMasks();

    if ((*masks)[libfalltergeist::FrmFileType::MASK_MONITOR] != NULL)
    {
        for (auto i=0; i<5; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color((*masks)[libfalltergeist::FrmFileType::MASK_MONITOR][j],i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _monitorTextures.push_back(texture);
        }
    }

    if ((*masks)[libfalltergeist::FrmFileType::MASK_SLIME] != NULL)
    {
        for (auto i=0; i<4; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[libfalltergeist::FrmFileType::MASK_SLIME][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _slimeTextures.push_back(texture);
        }
    }

    if ((*masks)[libfalltergeist::FrmFileType::MASK_SHORE] != NULL)
    {
        for (auto i=0; i<6; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[libfalltergeist::FrmFileType::MASK_SHORE][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _shoreTextures.push_back(texture);
        }
    }


    if ((*masks)[libfalltergeist::FrmFileType::MASK_FIRE_SLOW] != NULL)
    {
        for (auto i=0; i<5; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[libfalltergeist::FrmFileType::MASK_FIRE_SLOW][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _fireSlowTextures.push_back(texture);
        }
    }


    if ((*masks)[libfalltergeist::FrmFileType::MASK_FIRE_FAST] != NULL)
    {
        for (auto i=0; i<5; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();
            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[libfalltergeist::FrmFileType::MASK_FIRE_FAST][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _fireFastTextures.push_back(texture);
        }
    }


    if ((*masks)[libfalltergeist::FrmFileType::MASK_REDDOT] != NULL)
    {
        for (auto i=0; i<16; i++)
        {
            unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

            //modify
            for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[libfalltergeist::FrmFileType::MASK_REDDOT][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _reddotTextures.push_back(texture);
        }
    }
    _blinkingRed = -1;
}

AnimatedImage::~AnimatedImage()
{
}

unsigned int AnimatedImage::width()
{
    return texture()->width();
}

unsigned int AnimatedImage::height()
{
    return texture()->height();
}

void AnimatedImage::render()
{
    Game::getInstance()->renderer()->drawTexture(texture(), x(), y());

    if (_fireFastCounter < _fireFastTextures.size()) Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(_fireFastCounter), x(), y());
    if (_fireSlowCounter < _fireSlowTextures.size()) Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(_fireSlowCounter), x(), y());
    if (_monitorsCounter < _monitorTextures.size()) Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(_monitorsCounter), x(), y());
    if (_slimeCounter < _slimeTextures.size()) Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(_slimeCounter), x(), y());
    if (_shoreCounter < _shoreTextures.size()) Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(_shoreCounter), x(), y());
    if (_blinkingRedCounter < _reddotTextures.size()) Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(_blinkingRedCounter), x(), y());
}

void AnimatedImage::think()
{
    if (_monitorsTicks + 100 < SDL_GetTicks())
    {
        _monitorsTicks = SDL_GetTicks();

        _monitorsCounter++;
        if (_monitorsCounter >= 4) _monitorsCounter = 0;
    }

    if (_slimeTicks + 200 < SDL_GetTicks())
    {
        _slimeTicks = SDL_GetTicks();

        _slimeCounter++;
        if (_slimeCounter >= 3) _slimeCounter = 0;
    }

    if (_shoreTicks + 200 < SDL_GetTicks())
    {
        _shoreTicks = SDL_GetTicks();

        _shoreCounter++;
        if (_shoreCounter >= 5) _slimeCounter = 0;
    }

    if (_fireSlowTicks + 200 < SDL_GetTicks())
    {
        _fireSlowTicks = SDL_GetTicks();

        _fireSlowCounter++;
        if (_fireSlowCounter >= 4) _fireSlowCounter = 0;
    }

    if (_fireFastTicks + 142 < SDL_GetTicks())
    {
        _fireFastTicks = SDL_GetTicks();

        _fireFastCounter++;
        if (_fireFastCounter >= 4) _fireFastCounter = 0;
    }

    if (_blinkingRedTicks + 33 < SDL_GetTicks())
    {
        _blinkingRedTicks = SDL_GetTicks();

        if ((_blinkingRedCounter == 0) || (_blinkingRedCounter == 15))
        {
            _blinkingRed = -_blinkingRed;
        }

        _blinkingRedCounter = _blinkingRed + _blinkingRedCounter;
    }
}

}
