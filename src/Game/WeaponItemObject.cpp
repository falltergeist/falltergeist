#include "../Game/WeaponItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        WeaponItemObject::WeaponItemObject() : ItemObject()
        {
            _subtype = Subtype::WEAPON;
        }

        unsigned int WeaponItemObject::animationCode() const
        {
            return _animationCode;
        }

        void WeaponItemObject::setAnimationCode(unsigned int value)
        {
            _animationCode = value;
        }

        unsigned int WeaponItemObject::damageMin() const
        {
            return _damageMin;
        }

        void WeaponItemObject::setDamageMin(unsigned int value)
        {
            _damageMin = value;
        }

        unsigned int WeaponItemObject::damageMax() const
        {
            return _damageMax;
        }

        void WeaponItemObject::setDamageMax(unsigned int value)
        {
            _damageMax = value;
        }

        unsigned int WeaponItemObject::damageType() const
        {
            return _damageType;
        }

        void WeaponItemObject::setDamageType(unsigned int value)
        {
            _damageType = value;
        }

        unsigned int WeaponItemObject::rangePrimary() const
        {
            return _rangePrimary;
        }

        void WeaponItemObject::setRangePrimary(unsigned int value)
        {
            _rangePrimary = value;
        }

        unsigned int WeaponItemObject::rangeSecondary() const
        {
            return _rangeSecondary;
        }

        void WeaponItemObject::setRangeSecondary(unsigned int value)
        {
            _rangeSecondary = value;
        }

        unsigned int WeaponItemObject::minimumStrength() const
        {
            return _minimumStrength;
        }

        void WeaponItemObject::setMinimumStrength(unsigned int value)
        {
            _minimumStrength = value;
        }

        unsigned int WeaponItemObject::actionCostPrimary() const
        {
            return _actionCostPrimary;
        }

        void WeaponItemObject::setActionCostPrimary(unsigned int value)
        {
            _actionCostPrimary = value;
        }

        unsigned int WeaponItemObject::actionCostSecondary() const
        {
            return _actionCostSecondary;
        }

        void WeaponItemObject::setActionCostSecondary(unsigned int value)
        {
            _actionCostSecondary = value;
        }

        unsigned int WeaponItemObject::burstRounds() const
        {
            return _burstRounds;
        }

        void WeaponItemObject::setBurstRounds(unsigned int value)
        {
            _burstRounds = value;
        }

        unsigned int WeaponItemObject::ammoType() const
        {
            return _ammoType;
        }

        void WeaponItemObject::setAmmoType(unsigned int value)
        {
            _ammoType = value;
        }

        unsigned int WeaponItemObject::ammoPID() const
        {
            return _ammoPID;
        }

        void WeaponItemObject::setAmmoPID(unsigned int value)
        {
            _ammoPID = value;
        }

        unsigned int WeaponItemObject::ammoCapacity() const
        {
            return _ammoCapacity;
        }

        void WeaponItemObject::setAmmoCapacity(unsigned int value)
        {
            _ammoCapacity = value;
        }

        int WeaponItemObject::perk() const
        {
            return _perk;
        }

        void WeaponItemObject::setPerk(int value)
        {
            _perk = value;
        }
    }
}
