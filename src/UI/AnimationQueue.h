#pragma once

#include <vector>
#include "../UI/Base.h"

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

                void render(bool eggTransparency = false) override;
                void think(const float &deltaTime) override;

                virtual bool opaque(const Point &pos) override;

                const Size& size() const override;

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
