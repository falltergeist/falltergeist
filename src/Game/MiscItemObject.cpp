#include "../Game/MiscItemObject.h"
#include "../UI/TextArea.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
