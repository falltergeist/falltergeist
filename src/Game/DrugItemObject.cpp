#include "../Game/DrugItemObject.h"
#include "../UI/TextArea.h"

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
