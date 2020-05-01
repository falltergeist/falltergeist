#include "../Game/MiscObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
