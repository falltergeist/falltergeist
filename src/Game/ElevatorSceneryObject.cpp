#include "../Game/ElevatorSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        ElevatorSceneryObject::ElevatorSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::ELEVATOR;
        }
    }
}
