#pragma once

#include <memory>
#include "../Graphics/Point.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture;
    }

    namespace UI
    {
        using Graphics::Point;

        class Tile
        {
        public:
            Tile(unsigned int number, const Point &pos);

            unsigned int number() const;

            Point position() const;

            unsigned int index() const;

            void setIndex(unsigned int value);

            void enable();

            void disable();

            bool enabled();

        private:
            unsigned int _index = 0;

            unsigned int _number = 0;

            Point _position;

            bool _enabled = true;
        };
    }
}
