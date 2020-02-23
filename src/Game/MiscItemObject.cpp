#include "../Game/MiscItemObject.h"
#include "../UI/TextArea.h"

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
