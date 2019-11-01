#include "../Game/MiscItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        MiscItemObject::MiscItemObject() : ItemObject()
        {
            _subtype = Subtype::MISC;
        }
    }
}
