// Project includes
#include "../Game/KeyItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

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
