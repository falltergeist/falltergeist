#include "../Game/WallObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
