// Project includes
#include "../Game/ElevatorSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        ElevatorSceneryObject::ElevatorSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::ELEVATOR;
        }

        int ElevatorSceneryObject::elevatorType()
        {
            return _elevatorType;
        }

        void ElevatorSceneryObject::setElevatorType(int type)
        {
            _elevatorType = type;
        }

        int ElevatorSceneryObject::elevatorLevel()
        {
            return _elevatorLevel;
        }

        void ElevatorSceneryObject::setElevatorLevel(int level)
        {
            _elevatorLevel = level;
        }
    }
}
