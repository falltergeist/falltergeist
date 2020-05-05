#include "../../Game/Component/Lockable.h"

namespace Falltergeist
{
    namespace Game
    {
        namespace Component
        {
            bool Lockable::isLocked() const
            {
                return _isLocked;
            }

            bool Lockable::isOpened() const
            {
                return _isOpened;
            }

            void Lockable::open()
            {
                _isOpened = true;
            }

            void Lockable::close()
            {
                _isOpened = false;
            }

            void Lockable::lock()
            {
                _isLocked = true;
            }

            void Lockable::unlock()
            {
                _isLocked = false;
            }
        }
    }
}
