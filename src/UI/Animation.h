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

#ifndef FALLTERGEIST_UI_ANIMATION_H
#define FALLTERGEIST_UI_ANIMATION_H

// C++ standard includes
#include <vector>
#include <string>

// Falltergeist includes
#include "../Graphics/Animation.h"
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
class AnimationFrame;

class Animation : public Falltergeist::UI::Base
{
public:
    Animation();
    Animation(const std::string& frmName, unsigned int direction = 0);
    ~Animation() override;

    std::vector<std::unique_ptr<AnimationFrame>>& frames();

    void think() override;
    void render(bool eggTransparency = false) override;


    virtual bool opaque(const Point &pos) override;

/**
     * Additional offset, specific to current direction and taken from source FRM file.
     */
    const Point& shift() const;
    void setShift(const Point& value);

    Size size() const override;

    void play();
    void stop();
    void setReverse(bool value);

    unsigned int currentFrame() const;
    void setCurrentFrame(unsigned int value);
    AnimationFrame* currentFramePtr() const;

    /**
     * Offset of the current frame.
     */
    Point frameOffset() const;

    unsigned int actionFrame() const;
    void setActionFrame(unsigned int value);
    AnimationFrame* actionFramePtr() const;

    bool ended() const;
    bool playing() const;

    /**
     * Invoked when animation has ended.
     */
    Event::Handler& animationEndedHandler();
    /**
     * Invoked when animation "action" frame is reached
     */
    Event::Handler& actionFrameHandler();
    /**
     * Invoked on every frame of animation
     */
    Event::Handler& frameHandler();

protected:
    bool _playing = false;
    bool _ended = false;
    bool _reverse = false;
    std::vector<std::unique_ptr<AnimationFrame>> _animationFrames;
    Point _shift;
    unsigned int _currentFrame = 0;
    unsigned int _actionFrame = 0;
    unsigned int _progress = 0;
    unsigned int _frameTicks = 0;

    Event::Handler _frameHandler, _actionFrameHandler, _animationEndedHandler;
    std::unique_ptr<Graphics::Animation> _animation;
    unsigned int _direction;
};

}
}
#endif // FALLTERGEIST_UI_ANIMATION_H
