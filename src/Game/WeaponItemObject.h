#pragma once

#include "../Game/ItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        /**
         * All items that can be used as a weapon.
         */
        class WeaponItemObject : public ItemObject
        {
            public:
                WeaponItemObject();
                ~WeaponItemObject() = default;

                unsigned int animationCode() const;
                void setAnimationCode(unsigned int value);

                unsigned int damageMin() const;
                void setDamageMin(unsigned int value);

                unsigned int damageMax() const;
                void setDamageMax(unsigned int value);

                unsigned int damageType() const;
                void setDamageType(unsigned int value);

                unsigned int rangePrimary() const;
                void setRangePrimary(unsigned int value);

                unsigned int rangeSecondary() const;
                void setRangeSecondary(unsigned int value);

                unsigned int minimumStrength() const;
                void setMinimumStrength(unsigned int value);

                unsigned int actionCostPrimary() const;
                void setActionCostPrimary(unsigned int value);

                unsigned int actionCostSecondary() const;
                void setActionCostSecondary(unsigned int value);

                unsigned int burstRounds() const;
                void setBurstRounds(unsigned int value);

                unsigned int ammoType() const;
                void setAmmoType(unsigned int value);

                unsigned int ammoPID() const;
                void setAmmoPID(unsigned int value);

                unsigned int ammoCapacity() const;
                void setAmmoCapacity(unsigned int value);

                int perk() const;
                void setPerk(int value);

            private:
                unsigned int _animationCode = 0;
                unsigned int _damageMin = 0;
                unsigned int _damageMax = 0;
                unsigned int _damageType = 0;
                unsigned int _rangePrimary = 0;
                unsigned int _rangeSecondary = 0;
                unsigned int _minimumStrength = 0;
                unsigned int _actionCostPrimary = 0;
                unsigned int _actionCostSecondary = 0;
                unsigned int _burstRounds = 0;
                unsigned int _ammoType = 0;
                unsigned int _ammoPID = 0;
                unsigned int _ammoCapacity = 0;
                int _perk = -1;
        };
    }
}
