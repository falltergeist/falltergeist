// Project includes
#include "../Game/MiscItemObject.h"
#include "../UI/TextArea.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

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
