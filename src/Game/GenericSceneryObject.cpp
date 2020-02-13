#include "../Game/GenericSceneryObject.h"

namespace Falltergeist
{
    namespace Game
    {
        GenericSceneryObject::GenericSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::GENERIC;
        }

        bool GenericSceneryObject::_useEggTransparency()
        {
            return (_trans == Graphics::TransFlags::Trans::DEFAULT);
        }
    }
}
