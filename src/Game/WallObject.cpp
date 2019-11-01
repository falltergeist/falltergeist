#include "../Game/WallObject.h"

namespace Falltergeist
{
    namespace Game
    {
        WallObject::WallObject() : Object()
        {
            _type = Type::WALL;
        }

        bool WallObject::_useEggTransparency()
        {
            return (_trans == Graphics::TransFlags::Trans::DEFAULT);
        }
    }
}
