#include "../Game/AmmoItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        AmmoItemObject::AmmoItemObject() : ItemObject()
        {
            _subtype = Subtype::AMMO;
        }
    }
}
