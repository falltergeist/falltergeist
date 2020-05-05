#include "../../Game/Component/Component.h"

namespace Falltergeist
{
    namespace Game
    {
        namespace Component
        {
            Entity* Component::getEntity() const
            {
                return _entity;
            }

            void Component::setEntity(Entity* entity)
            {
                _entity = entity;
            }
        }
    }
}
