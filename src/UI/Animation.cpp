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

// Related headers
#include "../UI/Animation.h"

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../LocationCamera.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimationFrame.h"

// Third party includes
#include <libfalltergeist/Frm/Direction.h>
#include <libfalltergeist/Frm/File.h>
#include <libfalltergeist/Frm/Frame.h>
#include <SDL.h>

namespace Falltergeist
{

using Base::make_unique;

namespace UI
{

Animation::Animation() : Falltergeist::UI::Base()
{
}

Animation::Animation(const std::string& frmName, unsigned int direction) : Falltergeist::UI::Base()
{
    auto frm = ResourceManager::getInstance()->frmFileType(frmName);
    setTexture(ResourceManager::getInstance()->texture(frmName));

    _actionFrame = frm->actionFrame();
    auto dir = frm->directions()->at(direction);
    _shift = Point(dir->shiftX(), dir->shiftY());

    // Frame offset in texture's animation
    unsigned int x = 0;
    unsigned int y = 0;

    for (unsigned int d = 0; d != direction; ++d)
    {
        y += frm->directions()->at(d)->height(); //? может i - 1
    }

    int xOffset = 0;
    int yOffset = 0;
    for (unsigned int f = 0; f != frm->framesPerDirection(); ++f)
    {
        xOffset += frm->offsetX(direction, f);
        yOffset += frm->offsetY(direction, f);

        auto frame = make_unique<AnimationFrame>();
        frame->setWidth(frm->directions()->at(direction)->frames()->at(f)->width());
        frame->setHeight(frm->directions()->at(direction)->frames()->at(f)->height());
        frame->setXOffset((unsigned)xOffset);
        frame->setYOffset((unsigned)yOffset);
        frame->setY(y);
        frame->setX(x);

        auto fps = frm->framesPerSecond();
        if (fps == 0)
        {
            frame->setDuration(1000);
        }
        else
        {
            frame->setDuration((unsigned)std::round(1000.0/static_cast<double>(frm->framesPerSecond())));
        }

        x += frame->width();
        _animationFrames.push_back(std::move(frame));
    }

    if (frm->animatedPalette())
    {
        Graphics::AnimatedPalette*  palette=Game::getInstance()->animatedPalette();
        auto masks = frm->animatedMasks();

        if ((*masks)[MASK::MONITOR] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int mask[frm->width() * frm->height()];

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color((*masks)[MASK::MONITOR][j], i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _monitorTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::SLIME] != NULL)
        {
            for (auto i=0; i<4; i++)
            {
                unsigned int mask[frm->width() * frm->height()];

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::SLIME][j]), i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _slimeTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::SHORE] != NULL)
        {
            for (auto i=0; i<6; i++)
            {
                unsigned int mask[frm->width() * frm->height()];

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::SHORE][j]), i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _shoreTextures.push_back(texture);
            }
        }


        if ((*masks)[MASK::FIRE_SLOW] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int mask[frm->width() * frm->height()];

                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::FIRE_SLOW][j]), i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _fireSlowTextures.push_back(texture);
            }
        }


        if ((*masks)[MASK::FIRE_FAST] != NULL)
        {
            for (auto i=0; i<5; i++)
            {
                unsigned int mask[frm->width() * frm->height()];
                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::FIRE_FAST][j]), i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _fireFastTextures.push_back(texture);
            }
        }

        if ((*masks)[MASK::REDDOT] != NULL)
        {
            for (auto i=0; i<16; i++)
            {
                unsigned int mask[frm->width() * frm->height()];
                //modify
                for (unsigned int j = 0; j< frm->width() * frm->height(); j++)
                {
                    mask[j] = palette->color(((*masks)[MASK::REDDOT][j]), i);
                }
                //set
                auto texture = new Graphics::Texture(frm->width(), frm->height());
                texture->loadFromRGBA(mask);
                _reddotTextures.push_back(texture);
            }
        }
    }
}

Animation::~Animation()
{
}

std::vector<std::unique_ptr<AnimationFrame>>& Animation::frames()
{
    return _animationFrames;
}

void Animation::think()
{
    if (!_playing) return;

    if (SDL_GetTicks() - _frameTicks >= _animationFrames.at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        _progress += 1;
        if (_progress < _animationFrames.size())
        {
            _currentFrame = _reverse ? _animationFrames.size() - _progress - 1 : _progress;
            if (_actionFrame == _currentFrame)
            {
                emitEvent(make_unique<Event::Event>("actionFrame"), actionFrameHandler());
            }
        }
        else
        {
            _ended = true;
            _playing = false;
            emitEvent(make_unique<Event::Event>("animationEnded"), animationEndedHandler());
        }
    }
}

void Animation::render(bool eggTransparency)
{
    auto& frame = _animationFrames.at(_currentFrame);
    Point framePos = Point(frame->x(), frame->y());
    Size frameSize = Size(frame->width(), frame->height());
    Point offsetPosition = position() + offset();
    Point offsetFramePos = framePos + offset();
    Graphics::AnimatedPalette* pal = Game::getInstance()->animatedPalette();

    if (eggTransparency)
    {
        auto dude = Game::getInstance()->player();

        if (!dude || !Game::getInstance()->locationState())
        {
            Game::getInstance()->renderer()->drawTexture(_texture, offsetPosition, framePos, frameSize);

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), position(), framePos, frameSize);

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), position(), framePos, frameSize);

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), position(), framePos, frameSize);

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), position(), framePos, frameSize);

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), position(), framePos, frameSize);

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), position(), framePos, frameSize);

            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();
        Point eggPos = dude->hexagon()->position() - camera->topLeft() - Point(63, 78) + dude->ui()->offset();

        Point eggDelta = position() - eggPos;

        auto egg = ResourceManager::getInstance()->texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { eggPos.x(), eggPos.y(), (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { offsetPosition.x(), offsetPosition.y(), (int)frame->width(), (int)frame->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(_texture, offsetPosition, framePos, frameSize);

            if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), offsetPosition, framePos, frameSize);

            if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
                Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), offsetPosition, framePos, frameSize);

            if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
                Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), position(), offsetFramePos, frameSize);

            if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
                Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), position(), offsetFramePos, frameSize);

            if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
                Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), position(), offsetFramePos, frameSize);

            if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
                Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), position(), offsetFramePos, frameSize);

            return;
        }

        if (!_tmptex)
        {
            _tmptex = make_unique<Graphics::Texture>(texture()->width(),texture()->height());
        }
        texture()->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
            _fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST))->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
           _fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW))->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
            _slimeTextures.at(pal->getCounter(MASK::SLIME))->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
            _shoreTextures.at(pal->getCounter(MASK::SHORE))->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
            _monitorTextures.at(pal->getCounter(MASK::MONITOR))->copyTo(_tmptex.get());

        if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
            _reddotTextures.at(pal->getCounter(MASK::REDDOT))->copyTo(_tmptex.get());

        _tmptex->blitWithAlpha(egg, eggDelta.x(), eggDelta.y());
        Game::getInstance()->renderer()->drawTexture(_tmptex.get(), offsetPosition, framePos, frameSize);
    }
    else
    {
        Game::getInstance()->renderer()->drawTexture(_texture, offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::FIRE_FAST) < _fireFastTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireFastTextures.at(pal->getCounter(MASK::FIRE_FAST)), offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::FIRE_SLOW) < _fireSlowTextures.size())
            Game::getInstance()->renderer()->drawTexture(_fireSlowTextures.at(pal->getCounter(MASK::FIRE_SLOW)), offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::SLIME) < _slimeTextures.size())
            Game::getInstance()->renderer()->drawTexture(_slimeTextures.at(pal->getCounter(MASK::SLIME)), offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::SHORE) < _shoreTextures.size())
            Game::getInstance()->renderer()->drawTexture(_shoreTextures.at(pal->getCounter(MASK::SHORE)), offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::MONITOR) < _monitorTextures.size())
            Game::getInstance()->renderer()->drawTexture(_monitorTextures.at(pal->getCounter(MASK::MONITOR)), offsetPosition, framePos, frameSize);

        if (pal->getCounter(MASK::REDDOT) < _reddotTextures.size())
            Game::getInstance()->renderer()->drawTexture(_reddotTextures.at(pal->getCounter(MASK::REDDOT)), offsetPosition, framePos, frameSize);
    }
}

Size Animation::size() const
{
    auto& frame = _animationFrames.at(_currentFrame);
    return Size(frame->width(), frame->height());
}

Point Animation::offset() const
{
    auto& frame = _animationFrames.at(_currentFrame);
    return Point(frame->xOffset(), frame->yOffset()) + shift();
}

const Point& Animation::shift() const
{
    return _shift;
}

void Animation::setShift(const Point& value)
{
    _shift = value;
}

unsigned int Animation::pixel(const Point& pos)
{
    const auto& frame = _animationFrames.at(_currentFrame);

    Point offsetPos = pos - offset();
    if (!Rect::inRect(offsetPos, Size(frame->width(), frame->height())))
    {
        return 0;
    }
    return Base::pixel(offsetPos + Point(frame->x(), frame->y()));
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
    _progress = _reverse ? _animationFrames.size() - _currentFrame - 1 : _currentFrame;
}

unsigned int Animation::actionFrame() const
{
    return _actionFrame;
}

void Animation::setActionFrame(unsigned int value)
{
    _actionFrame = value;
}

Event::Handler& Animation::actionFrameHandler()
{
    return _actionFrameHandler;
}

Event::Handler& Animation::animationEndedHandler()
{
    return _animationEndedHandler;
}
}
}
