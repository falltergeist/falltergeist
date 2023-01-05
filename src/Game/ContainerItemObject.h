#pragma once

// Project includes
#include "../Game/IClosable.h"
#include "../Game/ILockable.h"
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
        class ContainerItemObject : public ItemObject, public IClosable, public ILockable {
            public:
                ContainerItemObject();
                ~ContainerItemObject() = default;

                std::vector<ItemObject*>* inventory();

                void use_p_proc(CritterObject* usedBy) override;

                bool locked() const override;
                void lock() override;
                void unlock() override;

                bool closed() const override;
                void close() override;
                void open() override;

            protected:
                std::vector<ItemObject*> _inventory;
                bool _closed = true;
                bool _locked = false;
        };
    }
}
