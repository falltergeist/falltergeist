#include "../Helpers/CritterHelper.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/Defines.h"
#include "../Game/WeaponItemObject.h"

namespace Falltergeist
{
    namespace Helpers
    {
        uint32_t CritterHelper::armorFID(Game::CritterObject* critter) const
        {
            if (auto armor = critter->armorSlot()) {
                if (critter->gender() == GENDER::FEMALE) {
                    return armor->femaleFID();
                }
                return armor->maleFID();
            }
            return critter->FID();
        }

        uint32_t CritterHelper::weaponId(Falltergeist::Game::CritterObject *critter) const
        {
            if (auto weapon = dynamic_cast<Game::WeaponItemObject*>(critter->currentHandSlot())) {
                return weapon->animationCode();
            }

            return WEAPON_NONE;
        }
    }
}
