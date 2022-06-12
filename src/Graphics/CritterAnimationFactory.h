#pragma once

// Project includes
#include "../Game/Orientation.h"
#include "../UI/Animation.h"

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist
{
    namespace Graphics
    {
        class CritterAnimationFactory
        {
            public:
                CritterAnimationFactory() = default;

                std::shared_ptr<UI::Animation> buildActionAnimation(uint32_t armorFID, uint32_t weaponId, const std::string &action, Game::Orientation orientation);

                std::shared_ptr<UI::Animation> buildActionAnimation(uint32_t armorFID, uint32_t weaponId, uint32_t action, Game::Orientation orientation);

                std::shared_ptr<UI::Animation> buildStandingAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation);

                std::shared_ptr<UI::Animation> buildWalkingAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation);

                std::shared_ptr<UI::Animation> buildRunningAnimation(uint32_t armorFID, uint32_t weaponId, Game::Orientation orientation);
        };
    }
}
