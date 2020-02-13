#include "../Graphics/CritterAnimationFactory.h"
#include "../Helpers/CritterAnimationHelper.h"
#include "../Game/Defines.h"

namespace Falltergeist
{
    namespace Graphics
    {
        std::unique_ptr<UI::Animation> CritterAnimationFactory::buildActionAnimation(uint32_t armorFID, uint32_t weaponId, const std::string &action, Game::Orientation orientation)
        {
            Helpers::CritterAnimationHelper critterAnimationHelper;
            std::string animName = critterAnimationHelper.getPrefix(armorFID);

            if (action == "aa") {
                animName += critterAnimationHelper.getSuffix(ANIM_STAND, weaponId);
            } else {
                animName += action;
            }

            auto animation = std::make_unique<UI::Animation>("art/critters/" + animName + ".frm", orientation);
            // TODO move it elsewhere
            //animation->animationEndedHandler().add([&animation](Event::Event* event) {
            //    animation->setCurrentFrame(0);
            //});
            return animation;
        }

        std::unique_ptr<UI::Animation> CritterAnimationFactory::buildActionAnimation(uint32_t armorFID, uint32_t weaponId, uint32_t action, Game::Orientation orientation)
        {
            Helpers::CritterAnimationHelper critterAnimationHelper;
            return buildActionAnimation(armorFID, weaponId, critterAnimationHelper.getSuffix(action, weaponId), orientation);
        }

        std::unique_ptr<UI::Animation> CritterAnimationFactory::buildStandingAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation)
        {
            return buildActionAnimation(armorFID, weaponId, "aa", orientation);
        }

        std::unique_ptr<UI::Animation> CritterAnimationFactory::buildWalkingAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation)
        {
            Helpers::CritterAnimationHelper critterAnimationHelper;
            std::string action = critterAnimationHelper.getSuffix(ANIM_WALK, weaponId);
            return buildActionAnimation(armorFID, weaponId, action, orientation);
        }

        std::unique_ptr<UI::Animation> CritterAnimationFactory::buildRunningAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation)
        {
            Helpers::CritterAnimationHelper critterAnimationHelper;
            std::string action = critterAnimationHelper.getSuffix(ANIM_RUNNING, weaponId);
            return buildActionAnimation(armorFID, weaponId, action, orientation);
        }
    }
}
