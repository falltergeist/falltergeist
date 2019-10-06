#pragma once

#include <UI/Image.h>
#include "../Game/Object.h"

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Item. Can be placed inside other object inventories (critters and containers)
         */
        class ItemObject : public Object
        {
            public:
                enum class Subtype
                {
                    ARMOR = 0,
                    CONTAINER,
                    DRUG,
                    WEAPON,
                    AMMO,
                    MISC,
                    KEY
                };

                ItemObject();
                ~ItemObject() override;

                Subtype subtype() const;

                // item stack size in inventory or on the ground
                unsigned int amount() const;
                void setAmount(unsigned int value);

                // item weight, in pounds
                unsigned int weight() const;
                void setWeight(unsigned int value);

                // item price without any modifiers
                unsigned int price() const;
                void setPrice(unsigned price);

                // item volume
                unsigned int volume() const;
                void setVolume(unsigned int volume);

                // item inventory frame ID
                int inventoryFID() const;
                void setInventoryFID(int value);

                UI::Image* inventoryUi() const;
                UI::Image* inventorySlotUi() const;
                UI::Image* inventoryDragUi() const;
                std::unique_ptr<UI::TextArea>& inventoryAmountUi();

            protected:
                Subtype _subtype;
                unsigned int _amount = 1;
                unsigned int _weight = 0;
                unsigned int _price = 0;
                unsigned int _volume = 0;
                int _inventoryFID = -1;
                std::unique_ptr<UI::TextArea> _inventoryAmountUi;
                std::unique_ptr<UI::Image> _inventoryUi, _inventorySlotUi, _inventoryDragUi;
                void _generateUi() override;
        };
    }
}
