// Project includes
#include "../Game/DrugItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        DrugItemObject::DrugItemObject() : ItemObject()
        {
            _subtype = Subtype::DRUG;
        }
    }
}
