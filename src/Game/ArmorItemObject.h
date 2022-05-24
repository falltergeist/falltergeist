#pragma once

// Project includes
#include "../Format/Enums.h"
#include "../Game/ItemObject.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        /*
         * Items wearable in "armor" slot.
         */
        class ArmorItemObject : public ItemObject
        {
            public:

                ArmorItemObject();
                ~ArmorItemObject() = default;

                int damageResist(DAMAGE type) const; // damage resistance bonus of the armor
                void setDamageResist(DAMAGE type, int value);

                int damageThreshold(DAMAGE type) const; // damage threshold bonus of the armor
                void setDamageThreshold(DAMAGE type, int value);

                int perk() const; // special perk given to player when wearing armor
                void setPerk(int value);

                unsigned int maleFID() const; // base frame ID used when wearing this type of armor by male critter
                void setMaleFID(unsigned int value);

                unsigned int femaleFID() const; // base frame ID used when wearing this type of armor by female critter
                void setFemaleFID(unsigned int value);

                unsigned int armorClass() const; // armor class (%)
                void setArmorClass(unsigned int value);

            protected:
                std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                int _perk = -1;
                unsigned int _maleFID = 0;
                unsigned int _femaleFID = 0;
                unsigned int _armorClass = 0;
        };
    }
}
