#pragma once

// Project includes
#include "../Game/IStatCollection.h"
#include "../Game/ITraitCollection.h"

// Third-party includes

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist::Game {
    class StatCollection final : public IStatCollection{
    public:
        StatCollection(
            std::shared_ptr<ITraitCollection> traitCollection
        );

        int stat(STAT stat) const override;
        void setStat(STAT stat, int value) override;

        int statBonus(STAT stat) const override;
        void setStatBonus(STAT stat, int value) override;

        // returns total stat value (with bonuses)
        int statTotal(STAT num) const override;
    private:
        std::shared_ptr<ITraitCollection> _traitCollection;
        std::vector<int> _statsBonus = {0, 0, 0, 0, 0, 0, 0};
        std::vector<int> _stats = {0, 0, 0, 0, 0, 0, 0};
    };
}
