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
#include <cmath>

// Falltergeist includes
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationFrame.h"
#include "../Graphics/Texture.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/AnimatedPalette.h"
#include "../ResourceManager.h"
#include "../Game/DudeObject.h"
#include "../State/Location.h"
#include "../LocationCamera.h"

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

    _xShift = frm->directions()->at(direction)->shiftX();
    _yShift = frm->directions()->at(direction)->shiftY();

    // Смещение кадра в текстуре анимации
    unsigned int x = 0;
    unsigned int y = 0;

    for (unsigned int d = 0; d != direction; ++d)
    {
        y += frm->directions()->at(d)->height(); //? может i - 1
    }

    int xOffset = 0;
    int yOffset = 0;
    for (auto f = 0; f != frm->framesPerDirection(); ++f)
    {
        xOffset += frm->offsetX(direction, f);
        yOffset += frm->offsetY(direction, f);

        auto frame = new AnimationFrame();
        frame->setWidth(frm->directions()->at(direction)->frames()->at(f)->width());
        frame->setHeight(frm->directions()->at(direction)->frames()->at(f)->height());
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

        x += frame->width();
        frames()->push_back(frame);
    }

    if (frm->animatedPalette())
    {
        AnimatedPalette*  palette=Game::getInstance()->animatedPalette();
        auto masks = frm->animatedMasks();

        if ((*masks)[MASK::MONITOR] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color((*masks)[MASK::MONITOR][j],i);
                }
                //set
                auto texture = new Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _monitorTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::SLIME] != NULL)
        {
            for (auto i=0; i<4; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::SLIME][j]),i);
                }
                //set
                auto texture = new Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _slimeTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::SHORE] != NULL)
        {
            for (auto i=0; i<6; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::SHORE][j]),i);
                }
                //set
                auto texture = new Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _shoreTextures.push_back(texture);
            }
        }


        if ((*masks)[MASK::FIRE_SLOW] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::FIRE_SLOW][j]),i);
                }
                //set
                auto texture = new Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _fireSlowTextures.push_back(texture);
            }
        }


        if ((*masks)[MASK::FIRE_FAST] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();
                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::FIRE_FAST][j]),i);
                }
                //set
                auto texture = new Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _fireFastTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::REDDOT] != NULL)
        {
            for (auto i=0; i<16; i++)
            {
                unsigned int* mask = new unsigned int[frm->width() * frm->height()]();
                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::REDDOT][j]),i);
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
    return _animationFrames.at(_currentFrame)->xOffset() + xShift();
}

int Animation::yOffset()
{
    return _animationFrames.at(_currentFrame)->yOffset() + yShift();
}

void Animation::think()
{
    if (!_playing) return;

    if (SDL_GetTicks() - _frameTicks >= frames()->at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        _progress += 1;
        if (_progress < frames()->size())
        {
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
        }
    }
}

void Animation::render(bool eggTransparency, bool grayscale)
{
    auto frame = frames()->at(_currentFrame);
    AnimatedPalette* pal = Game::getInstance()->animatedPalette();

    if (eggTransparency)
    {
        auto dude = Game::getInstance()->player();

        if (!dude || !Game::getInstance()->locationState())
        {
            Game::getInstance()->renderer()->drawTexture(_texture, x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x(), y(), frame->x(), frame->y(), frame->width(), frame->height());

            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();

        int egg_x = dude->hexagon()->x() - camera->x() - 63 + dude->ui()->xOffset();
        int egg_y = dude->hexagon()->y() - camera->y() - 78 + dude->ui()->yOffset();

        int egg_dx = x() - egg_x;
        int egg_dy = y() - egg_y;

        auto egg = ResourceManager::texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { egg_x, egg_y, (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { x() + xOffset(), y() + yOffset(), (int)frame->width(), (int)frame->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(_texture, x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x(), y(), frame->x() + xOffset(), frame->y() + yOffset(), frame->width(), frame->height());

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x(), y(), frame->x() + xOffset(), frame->y() + yOffset(), frame->width(), frame->height());

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x(), y(), frame->x() + xOffset(), frame->y() + yOffset(), frame->width(), frame->height());

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x(), y(), frame->x() + xOffset(), frame->y() + yOffset(), frame->width(), frame->height());

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

        //This is sloooow. But unfortunately sdl doesnt allow to blit over only alpha =/
        for (unsigned int x = 0; x < texture()->width(); x++)
        {
            for (unsigned int y = 0; y < texture()->height(); y++)
            {
                if (x+egg_dx >= egg->width()) continue;
                if (y+egg_dy >= egg->height()) continue;
                if (x+egg_dx < 0) continue;
                if (y+egg_dy < 0) continue;
                _tmptex->setPixel(x, y, _tmptex->pixel(x,y) & egg->pixel(x+egg_dx, y+egg_dy));
            }
        }
        Game::getInstance()->renderer()->drawTexture(_tmptex, x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());
    }
    else
    {
        if (grayscale)
        {
            if (!_graytex)
            {
                _graytex = new Texture(texture()->width(),texture()->height());
                texture()->copyTo(_graytex);
                _graytex->grayscale();
                _graytex->setColorModifier({255,255,255,128});
            }

            Game::getInstance()->renderer()->drawTexture(_graytex, x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());
        }
        else
        {
            Game::getInstance()->renderer()->drawTexture(_texture, x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());
        }

        if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

        if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

        if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
            Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

        if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
            Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

        if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
            Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());

        if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
            Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), x() + xOffset(), y() + yOffset(), frame->x(), frame->y(), frame->width(), frame->height());
    }
}

unsigned int Animation::height()
{
    return _animationFrames.at(_currentFrame)->height();
}

unsigned int Animation::width()
{
    return _animationFrames.at(_currentFrame)->width();
}

unsigned int Animation::pixel(unsigned int x, unsigned int y)
{
    auto frame = frames()->at(_currentFrame);

    x -= xOffset();
    y -= yOffset();

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
}

void Animation::setReverse(bool value)
{
    _reverse = value;
}

bool Animation::ended() const
{
    return _ended;
}

bool Animation::playing() const
{
    return _playing;
}

unsigned int Animation::currentFrame() const
{
    return _currentFrame;
}

void Animation::setCurrentFrame(unsigned int value)
{
    _currentFrame = value;
    _progress = _reverse ? frames()->size() - _currentFrame - 1 : _currentFrame;
}

unsigned int Animation::actionFrame() const
{
    return _actionFrame;
}

void Animation::setActionFrame(unsigned int value)
{
    _actionFrame = value;
}

int Animation::xShift()
{
    return _xShift;
}

void Animation::setXShift(int value)
{
    _xShift = value;
}

int Animation::yShift()
{
    return _yShift;
}

void Animation::setYShift(int value)
{
    _yShift = value;
}

}
