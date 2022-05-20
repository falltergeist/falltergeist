#include "../Game/StairsSceneryObject.h"
#include "../Game/LadderSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        StairsSceneryObject::StairsSceneryObject() : LadderSceneryObject()
        {
            _subtype = Subtype::STAIRS;
        }
    }
}
