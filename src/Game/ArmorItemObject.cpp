#include "../Game/ArmorItemObject.h"
#include "../Exception.h"

namespace Falltergeist
{
    namespace Game
    {
        ArmorItemObject::ArmorItemObject() : ItemObject()
        {
            _subtype = Subtype::ARMOR;
        }

        int ArmorItemObject::damageResist(DAMAGE type) const
        {
            if (type > DAMAGE::POISON) {
                throw Exception("ArmorItemObject::damageResist(type) - type out of range:" + std::to_string((unsigned)type));
            }
            return _damageResist.at((unsigned)type);
        }

        void ArmorItemObject::setDamageResist(DAMAGE type, int value)
        {
            if (type > DAMAGE::POISON) {
                throw Exception("ArmorItemObject::setDamageResist(type, value) - type out of range:" + std::to_string((unsigned)type));
            }
            _damageResist.at((unsigned)type) = value;
        }

        int ArmorItemObject::damageThreshold(DAMAGE type) const
        {
            if ( type > DAMAGE::POISON) {
                throw Exception("ArmorItemObject::damageThreshold(type) - type out of range:" + std::to_string((unsigned)type));
            }
            return _damageThreshold.at((unsigned)type);
        }

        void ArmorItemObject::setDamageThreshold(DAMAGE type, int value)
        {
            if ( type > DAMAGE::POISON) {
                throw Exception("ArmorItemObject::setDamageThreshold(type, value) - type out of range:" + std::to_string((unsigned)type));
            }
            _damageThreshold.at((unsigned)type) = value;
        }

        int ArmorItemObject::perk() const
        {
            return _perk;
        }

        void ArmorItemObject::setPerk(int value)
        {
            _perk = value;
        }

        unsigned int ArmorItemObject::maleFID() const
        {
            return _maleFID;
        }

        void ArmorItemObject::setMaleFID(unsigned int value)
        {
            _maleFID = value;
        }

        unsigned int ArmorItemObject::femaleFID() const
        {
            return _femaleFID;
        }

        void ArmorItemObject::setFemaleFID(unsigned int value)
        {
            _femaleFID = value;
        }

        unsigned int ArmorItemObject::armorClass() const
        {
            return _armorClass;
        }

        void ArmorItemObject::setArmorClass(unsigned int value)
        {
            _armorClass = value;
        }
    }
}
