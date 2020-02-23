#include "../Game/AmmoItemObject.h"
#include "../UI/TextArea.h"

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
