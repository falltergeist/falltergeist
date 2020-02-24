#include "../Game/DrugItemObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

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
