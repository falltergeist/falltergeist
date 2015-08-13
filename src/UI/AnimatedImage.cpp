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

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/AnimatedImage.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Game/DudeObject.h"
#include "../State/Location.h"
#include "../LocationCamera.h"

// Third party includes

namespace Falltergeist
{

AnimatedImage::AnimatedImage(libfalltergeist::Frm::File* frm, unsigned int direction)
{

    setTexture(new Texture(frm->width(), frm->height()));
    _texture->loadFromRGBA(frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")));
    setXOffset(frm->offsetX(direction) + frm->directions()->at(direction)->shiftX());
    setYOffset(frm->offsetY(direction) + frm->directions()->at(direction)->shiftY());

    AnimatedPalette*  palette=Game::getInstance()->animatedPalette();
    auto masks = frm->animatedMasks();

    if ((*masks)[MASK::MONITOR] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();
        for (auto i = 0; i < 5; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color((*masks)[MASK::MONITOR][j],i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _monitorTextures.push_back(texture);
        }
        delete[] mask;
    }

    if ((*masks)[MASK::SLIME] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

        for (auto i = 0; i < 4; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[MASK::SLIME][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _slimeTextures.push_back(texture);
        }
        delete[] mask;
    }

    if ((*masks)[MASK::SHORE] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

        for (auto i = 0; i < 6; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[MASK::SHORE][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _shoreTextures.push_back(texture);
        }
        delete[] mask;
    }


    if ((*masks)[MASK::FIRE_SLOW] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

        for (auto i = 0; i < 5; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[MASK::FIRE_SLOW][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _fireSlowTextures.push_back(texture);
        }
        delete[] mask;
    }


    if ((*masks)[MASK::FIRE_FAST] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

        for (auto i = 0; i < 5; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[MASK::FIRE_FAST][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _fireFastTextures.push_back(texture);
        }
        delete[] mask;
    }


    if ((*masks)[MASK::REDDOT] != NULL)
    {
        unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

        for (auto i = 0; i < 16; i++)
        {
            //modify
            for (auto j = 0; j < frm->width() * frm->height(); j++)
            {
                mask[j] = palette->color(((*masks)[MASK::REDDOT][j]),i);
            }
            //set
            auto texture = new Texture(frm->width(), frm->height());
            texture->loadFromRGBA(mask);
            _reddotTextures.push_back(texture);
        }
        delete[] mask;
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

void AnimatedImage::render(bool eggTransparency)
{
    AnimatedPalette* pal = Game::getInstance()->animatedPalette();

    if (eggTransparency)
    {
        auto dude = Game::getInstance()->player();

        if (!dude || !Game::getInstance()->locationState())
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x(), y());

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x(), y());

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x(), y());

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x(), y());

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x(), y());

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x(), y());
            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();

        int egg_x = dude->hexagon()->x() - camera->x() - 63 + dude->ui()->xOffset();
        int egg_y = dude->hexagon()->y() - camera->y() - 78 + dude->ui()->yOffset();

        int egg_dx = x() - egg_x;
        int egg_dy = y() - egg_y;

        auto egg = ResourceManager::getInstance()->texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { egg_x, egg_y, (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { x(), y(), (int)texture()->width(), (int)texture()->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x(), y());

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x(), y());

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x(), y());

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x(), y());

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x(), y());

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x(), y());
            return;
        }

        if (!_tmptex) _tmptex = new Texture(texture()->width(),texture()->height());
        texture()->copyTo(_tmptex);

        if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
            _fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST))->copyTo(_tmptex);

        if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
            _fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW))->copyTo(_tmptex);

        if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
            _slimeTextures.at(pal->getCounter(MASK::SLIME))->copyTo(_tmptex);

        if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
            _shoreTextures.at(pal->getCounter(MASK::SHORE))->copyTo(_tmptex);

        if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
            _monitorTextures.at(pal->getCounter(MASK::MONITOR))->copyTo(_tmptex);

        if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
            _reddotTextures.at(pal->getCounter(MASK::REDDOT))->copyTo(_tmptex);

        _tmptex->blitWithAlpha(egg, egg_dx, egg_dy);
        Game::getInstance()->renderer()->drawTexture(_tmptex, x(), y());
    }
    else
    {
        Game::getInstance()->renderer()->drawTexture(texture(), x(), y());

        if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x(), y());

        if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x(), y());

        if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
            Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x(), y());

        if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
            Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x(), y());

        if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
            Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x(), y());

        if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
            Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x(), y());
    }

}

}
