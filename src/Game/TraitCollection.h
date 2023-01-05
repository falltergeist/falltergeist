#pragma once

// Project includes
#include "../Game/ITraitCollection.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist::Game {
    class TraitCollection final : public ITraitCollection{
    public:
        bool hasTrait(TRAIT trait) const override;
        void addTrait(TRAIT trait) override;
        void removeTrait(TRAIT trait) override;
        uint8_t traitsCount() const override;
    private:
        std::vector<bool> _traitsTagged = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    };
}
