#pragma once

#include <vector>
#include "../Game/ItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Items able to hold other items in their inventory.
         */
        class ContainerItemObject : public ItemObject
        {
            public:
                ContainerItemObject();
                ~ContainerItemObject() override = default;

                std::vector<ItemObject*>* inventory();

                void use_p_proc(CritterObject* usedBy) override;

                bool locked() const;
                void setLocked(bool locked);

                bool opened() const;
                void setOpened(bool opened);

            protected:
                std::vector<ItemObject*> _inventory;
                bool _opened = false;
                bool _locked = false;
        };
    }
}
