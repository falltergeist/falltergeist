#pragma once

// Project includes
#include "../UI/Base.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace UI
    {
        class Animation;

        class AnimationQueue : public Base
        {
            public:
                AnimationQueue();

                ~AnimationQueue() override = default;

                std::vector<std::unique_ptr<Animation>>& animations();

                Animation* currentAnimation() const;

                void clear();

                void stop();

                void start();

                void setRepeat(bool value);

                void render(bool eggTransparency = false) override;

                void think(const float &deltaTime) override;

                virtual bool opaque(const Graphics::Point &pos) override;

                const Graphics::Size& size() const override;

                const Graphics::Point& offset() const override;

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
