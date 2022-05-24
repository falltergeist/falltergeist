// Project includes
#include "../Game/StairsSceneryObject.h"
#include "../Game/LadderSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

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
