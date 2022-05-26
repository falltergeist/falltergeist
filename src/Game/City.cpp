// Project includes
#include "City.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        City::City(Format::Txt::City city)
        {
            _city = city;
            _state = _city.startState;
            _worldPos = Graphics::Point(_city.worldX, _city.worldY);
        }

        const Graphics::Point& City::worldPos() const
        {
            return _worldPos;
        }

        bool City::state() const
        {
            return _state;
        }
    }
}
