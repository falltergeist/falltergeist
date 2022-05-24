// Project includes
#include "../Game/ExitMiscObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        ExitMiscObject::ExitMiscObject() : MiscObject()
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
