#include "../Game/Orientation.h"

namespace Falltergeist
{
    namespace Game
    {
        Orientation::Orientation(unsigned char value)
        {
            *this = value;
        }

        Orientation& Orientation::operator=(unsigned char value)
        {
            _dir = (unsigned char) (value % 6);
            return *this;
        }

        Orientation::operator unsigned char() const
        {
            return _dir;
        }
    }
}
