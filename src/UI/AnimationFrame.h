#pragma once

// Project includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        class AnimationFrame
        {
            public:
                AnimationFrame();

                ~AnimationFrame();

                Graphics::Point position() const;

                void setPosition(const Graphics::Point&);

                unsigned int x() const;

                unsigned int y() const;

                const Graphics::Size& size() const;

                void setSize(const Graphics::Size&);

                Graphics::Point offset() const;

                void setOffset(const Graphics::Point&);

                int xOffset() const;

                int yOffset() const;

                unsigned int duration() const;

                void setDuration(unsigned int duration);

            protected:
                // Offset of animation frame position relative to sprite position
                Graphics::Point _position;

                // Animation frame width and height
                Graphics::Size _size;

                // Offset of animation frame on screen relative to first animation frame
                Graphics::Point _offset;

                // Duration of animation frame in milliseconds
                unsigned int _duration = 0;
        };
    }
}
