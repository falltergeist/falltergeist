#include "../Game/KeyItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
