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

#ifndef FALLTERGEIST_UI_ANIMATIONQUEUE_H
#define FALLTERGEIST_UI_ANIMATIONQUEUE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

class Animation;

class AnimationQueue : public Falltergeist::UI::Base
{
public:
    AnimationQueue();
    ~AnimationQueue() override;

    std::vector<std::unique_ptr<Animation>>& animations();
    Animation* currentAnimation() const;

    void clear();
    void stop();
    void start();
    void setRepeat(bool value);

    Graphics::Texture* texture() const override;
    void render(bool eggTransparency = false) override;
    void think() override;
    unsigned int pixel(const Point& pos) override;

    Size size() const override;
    Point offset() const override;

    Event::Handler& animationEndedHandler();

protected:
    bool _playing = false;
    bool _repeat = false;
    unsigned int _currentAnimation = 0;
    std::vector<std::unique_ptr<Animation>> _animations;

    Event::Handler _animationEndedHandler;
};

}
}
#endif // FALLTERGEIST_UI_ANIMATIONQUEUE_H
