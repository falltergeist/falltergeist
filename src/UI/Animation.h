#pragma once

#include <string>
#include <vector>
#include "../Graphics/Animation.h"
#include "../UI/Base.h"

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

                void think(const float &deltaTime) override;
                void render(bool eggTransparency = false) override;


                virtual bool opaque(const Point &pos) override;

                /**
                 * Additional offset, specific to current direction and taken from source FRM file.
                 */
                const Point& shift() const;
                void setShift(const Point& value);

                const Size& size() const override;

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
