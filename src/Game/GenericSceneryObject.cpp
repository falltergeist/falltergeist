// Project includes
#include "../Game/GenericSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        GenericSceneryObject::GenericSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::GENERIC;
        }
    }
}
