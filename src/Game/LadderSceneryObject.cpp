#include "../Game/LadderSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        LadderSceneryObject::LadderSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::LADDER;
        }
    }
}
