#include "../Game/DrugItemObject.h"

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
