/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <memory>

// Falltergeist includes
#include "../Format/Frm/File.h"
#include "../Format/Frm/Direction.h"
#include "../Format/Frm/Frame.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../PathFinding/Hexagon.h"
#include "../LocationCamera.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimationFrame.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

using Graphics::Rect;

Animation::Animation() : Falltergeist::UI::Base()
{
}

Animation::Animation(const std::string& frmName, unsigned int direction) : Falltergeist::UI::Base()
{
    _direction = direction;
    auto frm = ResourceManager::getInstance()->frmFileType(frmName);
    _animation = std::make_unique<Graphics::Animation>(frmName);

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

    int xOffset = 1;
    int yOffset = 1;
    for (unsigned int f = 0; f != frm->framesPerDirection(); ++f)
    {
        xOffset += frm->offsetX(direction, f);
        yOffset += frm->offsetY(direction, f);

        auto frame = std::make_unique<AnimationFrame>();
        auto srcFrame = frm->directions()->at(direction)->frames()->at(f);
        frame->setSize(Size(srcFrame->width(), srcFrame->height()));
        frame->setOffset({xOffset, yOffset});
        frame->setPosition(Point(x, y));

        auto fps = frm->framesPerSecond();
        if (fps == 0)
        {
            frame->setDuration(100);
        }
        else
        {
            frame->setDuration((unsigned)std::round(1000.0 / static_cast<double>(frm->framesPerSecond())));
        }

        x += frame->width()+2;
        _animationFrames.push_back(std::move(frame));
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

    // TODO: handle cases when main loop FPS is lower than animation FPS
    if (SDL_GetTicks() - _frameTicks >= _animationFrames.at(_currentFrame)->duration())
    {
        _frameTicks = SDL_GetTicks();

        _progress += 1;
        
        if (_progress < _animationFrames.size())
        {
            _currentFrame = _reverse ? _animationFrames.size() - _progress - 1 : _progress;
            emitEvent(std::make_unique<Event::Event>("frame"), frameHandler());
            if (_actionFrame == _currentFrame)
            {
                emitEvent(std::make_unique<Event::Event>("actionFrame"), actionFrameHandler());
            }
        }
        else
        {
            _ended = true;
            _playing = false;
            emitEvent(std::make_unique<Event::Event>("animationEnded"), animationEndedHandler());
        }
    }
}

void Animation::render(bool eggTransparency)
{
    auto& frame = _animationFrames.at(_currentFrame);
    Point offsetPosition = position() + shift() + frame->offset();
    _animation->trans(_trans);
    _animation->render(offsetPosition.x(), offsetPosition.y(), _direction, _currentFrame, eggTransparency, light(),
                       _outline, _lightLevel);
}

Size Animation::size() const
{
    return _animationFrames.at(_currentFrame)->size();
}

const Point& Animation::shift() const
{
    return _shift;
}

void Animation::setShift(const Point& value)
{
    _shift = value;
}

void Animation::play()
{
    if (!_playing)
    {
        _playing = true;
        _ended = false;
        _frameTicks = SDL_GetTicks();
    }
}

void Animation::stop()
{
    _playing = false;
    _ended = false;
    _progress = 0;
    _currentFrame = 0;
}

void Animation::setReverse(bool value)
{
    _reverse = value;
    setCurrentFrame(value ? _animationFrames.size()-1 : 0);
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

AnimationFrame* Animation::currentFramePtr() const
{
    return _animationFrames.at(_currentFrame).get();
}

Point Animation::frameOffset() const
{
    return offset() + currentFramePtr()->offset();
}

unsigned int Animation::actionFrame() const
{
    return _actionFrame;
}

void Animation::setActionFrame(unsigned int value)
{
    _actionFrame = value;
}

AnimationFrame* Animation::actionFramePtr() const
{
    return _animationFrames.at(_actionFrame).get();
}

Event::Handler& Animation::frameHandler()
{
    return _frameHandler;
}

Event::Handler& Animation::actionFrameHandler()
{
    return _actionFrameHandler;
}

Event::Handler& Animation::animationEndedHandler()
{
    return _animationEndedHandler;
}

bool Animation::opaque(const Point &pos) {
    const auto& frame = _animationFrames.at(_currentFrame);

    Point offsetPos = pos - offset();
    if (!Rect::inRect(offsetPos, frame->size()))
    {
        return 0;
    }
    offsetPos +=frame->position();
    return _animation->opaque(offsetPos.x(),offsetPos.y());
}

}
}
