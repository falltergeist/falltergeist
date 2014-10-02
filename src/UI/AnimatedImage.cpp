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
    setXOffset(frm->offsetX(direction) + frm->shiftX(direction));
    setYOffset(frm->offsetY(direction) + frm->shiftY(direction));

    AnimatedPalette*  palette=Game::getInstance()->animatedPalette();
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
    AnimatedPalette* pal = Game::getInstance()->animatedPalette();

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_FAST) < _fireFastTextures.size())
        Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_FAST)), x(), y());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_SLOW) < _fireSlowTextures.size())
        Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_SLOW)), x(), y());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_SLIME) < _slimeTextures.size())
        Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_SLIME)), x(), y());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_SHORE) < _shoreTextures.size())
        Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_SHORE)), x(), y());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_MONITOR) < _monitorTextures.size())
        Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_MONITOR)), x(), y());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_REDDOT) < _reddotTextures.size())
        Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_REDDOT)), x(), y());
}

}
