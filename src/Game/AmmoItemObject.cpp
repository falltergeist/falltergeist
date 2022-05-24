// Project includes
#include "../Game/AmmoItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

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
