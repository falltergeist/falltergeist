#include "../Game/ExitMiscObject.h"

namespace Falltergeist
{
    namespace Game
    {
        ExitMiscObject::ExitMiscObject()
        {
        }

        int ExitMiscObject::exitMapNumber() const
        {
            return _exitMapNumber;
        }

        void ExitMiscObject::setExitMapNumber(int value)
        {
            _exitMapNumber = value;
        }

        int ExitMiscObject::exitElevationNumber() const
        {
            return _exitElevationNumber;
        }

        void ExitMiscObject::setExitElevationNumber(int value)
        {
            _exitElevationNumber = value;
        }

        int ExitMiscObject::exitHexagonNumber() const
        {
            return _exitHexagonNumber;
        }

        void ExitMiscObject::setExitHexagonNumber(int value)
        {
            _exitHexagonNumber = value;
        }

        int ExitMiscObject::exitDirection() const
        {
            return _exitDirection;
        }

        void ExitMiscObject::setExitDirection(int value)
        {
            _exitDirection = value;
        }
    }
}
