#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist
{
    namespace UI
    {
        using Graphics::Point;
        using Graphics::Size;

        class AnimationFrame
        {
            public:
                AnimationFrame();
                ~AnimationFrame();

                Point position() const;
                void setPosition(const Point&);

                unsigned int x() const;
                unsigned int y() const;


                Size size() const;
                void setSize(const Size&);

                unsigned int width() const;
                unsigned int height() const;

                Point offset() const;
                void setOffset(const Point&);

                int xOffset() const;
                int yOffset() const;

                unsigned int duration() const;
                void setDuration(unsigned int duration);

            protected:
                // Offset of animation frame position relative to sprite position
                Point _position;

                // Animation frame width and height
                Size _size;

                // Offset of animation frame on screen relative to first animation frame
                Point _offset;

                // Duration of animation frame in milliseconds
                unsigned int _duration = 0;
        };
    }
}
