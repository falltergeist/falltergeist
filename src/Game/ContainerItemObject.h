#pragma once

#include <vector>
#include <memory>
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
                ~ContainerItemObject() = default;

                std::vector<std::shared_ptr<ItemObject>>* inventory();

                void use_p_proc(const std::shared_ptr<CritterObject> &usedBy) override;

                bool locked() const;
                void setLocked(bool locked);

                bool opened() const;
                void setOpened(bool opened);

            protected:
                std::vector<std::shared_ptr<ItemObject>> _inventory;
                bool _opened = false;
                bool _locked = false;
        };
    }
}
