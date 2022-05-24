// Project includes
#include "../Game/WallObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        WallObject::WallObject() : Object()
        {
            _type = Type::WALL;
        }
    }
}
