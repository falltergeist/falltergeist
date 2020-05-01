#include "../Exception.h"
#include "../Format/Lst/File.h"
#include "../Game/Defines.h"
#include "../Helpers/CritterAnimationHelper.h"
#include "../Logger.h"
#include "../ResourceManager.h"

namespace Falltergeist
{
    namespace Helpers
    {
        std::string CritterAnimationHelper::getPrefix(unsigned int FID) const
        {
            const auto baseId = FID & 0x00000FFF;
            auto lst = ResourceManager::getInstance()->lstFileType("art/critters/critters.lst");
            if (baseId >= lst->strings()->size()) {
                Logger::error() << "CritterAnimationHelper::getPrefix - LST size: " << lst->strings()->size() << " <= baseId: " << baseId << " frmType: " << std::endl;
                return "";
            }
            return lst->strings()->at(baseId).erase(6);
        }


        std::string CritterAnimationHelper::getSuffix(unsigned int animationId, unsigned int weaponId) const
        {
            const char weaponCode = 'c' + weaponId;
            if (animationId >= ANIM_TAKE_OUT && animationId <= ANIM_FIRE_CONTINUOUS) {
                if (weaponId > WEAPON_ROCKET_LAUNCHER || weaponId == 0) {
                    throw Exception("Critter weaponId unsupported value");
                }
                //[d-m][c-l]
                return { weaponCode, static_cast<char>(animationId + 0x3D) };
            }

            if (animationId == ANIM_PRONE_TO_STANDING) {
                return "ch";
            }

            if (animationId == ANIM_BACK_TO_STANDING) {
                return "cj";
            }

            // TODO: figure out what is 0x40
            if (animationId == 0x40) {
                return "na";
            }

            // single-frame death animations (the last frame of knockdown and death animations)
            if (animationId >= ANIM_FALL_BACK_SF) {
                // r[a-z]
                return { 'r', static_cast<char>(animationId + 0x31) };
            }

            if (animationId >= ANIM_FALL_BACK) {
                // b[a-p]
                return { 'b', static_cast<char>(animationId + 0x4d) };
            }

            if (animationId == ANIM_THROW_ANIM) {
                if (weaponId == WEAPON_KNIFE) {
                    return "dm";
                }

                if (weaponId == WEAPON_SPEAR) {
                    return "gm";
                }

                return "as";
            }

            if (animationId == ANIM_DODGE_ANIM) {
                if (weaponId > 0) {
                    // [d-m]e
                    return { weaponCode, 'e' };
                }

                return "an";
            }

            if (animationId <= ANIM_WALK && weaponId > 0) {
                return { weaponCode, static_cast<char>('a' + animationId) };
            }

            return { 'a', static_cast<char>('a' + animationId) };
        }
    }
}
