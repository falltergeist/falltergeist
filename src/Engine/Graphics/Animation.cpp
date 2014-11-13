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
#include "../../Engine/Graphics/Animation.h"
#include "../../Engine/Graphics/AnimationFrame.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/Game.h"
#include "../../Engine/Graphics/Renderer.h"
#include "../../Engine/Graphics/AnimatedPalette.h"
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

    _actionFrame = frm->actionFrame();

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

    if (frm->animatedPalette())
    {
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
    if (!_playing) return;

    if (SDL_GetTicks() - _frameTicks >= frames()->at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        if (_progress < frames()->size() - 1)
        {
            _progress += 1;
            _currentFrame = _reverse ? frames()->size() - _progress - 1 : _progress;
            if (_actionFrame == _currentFrame)
            {
                auto event = new Event("actionFrame");
                emitEvent(event);
                delete event;
            }
        }
        else
        {
            _ended = true;
            _playing = false;
            auto event = new Event("animationEnded");
            emitEvent(event);
            delete event;
            return;
        }
        auto frame = frames()->at(_currentFrame);
        setXOffset(frame->xOffset());
        setYOffset(frame->yOffset());
    }
}

void Animation::render()
{
    auto frame = frames()->at(_currentFrame);
    Game::getInstance()->renderer()->drawTexture(_texture, x(),y(), frame->x(), frame->y(), frame->width(), frame->height());

    AnimatedPalette* pal = Game::getInstance()->animatedPalette();

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_FAST) < _fireFastTextures.size())
        Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_FAST)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_SLOW) < _fireSlowTextures.size())
        Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_FIRE_SLOW)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_SLIME) < _slimeTextures.size())
        Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_SLIME)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_SHORE) < _shoreTextures.size())
        Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_SHORE)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_MONITOR) < _monitorTextures.size())
        Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_MONITOR)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

    if (pal->getCounter(libfalltergeist::FrmFileType::MASK_REDDOT) < _reddotTextures.size())
        Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(libfalltergeist::FrmFileType::MASK_REDDOT)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());
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

void Animation::play()
{
    _playing = true;
}

void Animation::stop()
{
    _playing = false;
    _ended = false;
    _progress = 0;
    auto frame = frames()->at(_currentFrame);
    setXOffset(frame->xOffset());
    setYOffset(frame->yOffset());

}

void Animation::setReverse(bool value)
{
    _reverse = value;
}

bool Animation::ended()
{
    return _ended;
}

unsigned int Animation::currentFrame()
{
    return _currentFrame;
}

unsigned int Animation::actionFrame()
{
    return _actionFrame;
}

void Animation::setActionFrame(unsigned int value)
{
    _actionFrame = value;
}

}
