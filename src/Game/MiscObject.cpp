// Project includes
#include "../Game/MiscObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        MiscObject::MiscObject() : Object()
        {
            _type = Type::MISC;
        }
    }
}
