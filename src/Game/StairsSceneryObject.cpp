#include "../Game/StairsSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        StairsSceneryObject::StairsSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::STAIRS;
        }
    }
}
