#include "../Game/KeyItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        KeyItemObject::KeyItemObject() : ItemObject()
        {
            _subtype = Subtype::KEY;
        }
    }
}
