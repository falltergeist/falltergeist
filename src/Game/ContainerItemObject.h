#pragma once

// Project includes
#include "../Game/ItemObject.h"

// Third-party includes

// stdlib
#include <vector>

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
                ~ContainerItemObject() = default;

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
