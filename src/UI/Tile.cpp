// Project includes
#include "../UI/Tile.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        Tile::Tile(unsigned int number, const Graphics::Point &pos)
        {
            _number = number;
            _position = pos;
        }

        unsigned int Tile::number() const
        {
            return _number;
        }

        const Graphics::Point& Tile::position() const
        {
            return _position;
        }

        unsigned int Tile::index() const
        {
            return _index;
        }

        void Tile::setIndex(unsigned int value)
        {
            _index = value;
        }

        void Tile::enable()
        {
            _enabled = true;
        }

        void Tile::disable()
        {
            _enabled = false;
        }

        bool Tile::enabled()
        {
            return _enabled;
        }
    }
}
