#include "../Game/AmmoItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
