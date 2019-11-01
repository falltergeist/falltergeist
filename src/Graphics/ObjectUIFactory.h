#pragma once

#include "../Game/Orientation.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class ObjectUIFactory
        {
            public:
                std::unique_ptr<UI::Base> buildByFID(uint32_t fid, Game::Orientation orientation);
                std::unique_ptr<UI::Base> buildActionAnimation(uint32_t armorFID, uint32_t weaponId, const std::string &action, Game::Orientation orientation);
        };
    }
}
