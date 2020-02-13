#include "../Game/ElevatorSceneryObject.h"

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
