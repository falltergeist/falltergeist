#pragma once

// Project includes
#include "../Game/ISkillCollection.h"
#include "../Game/IStatCollection.h"
#include "../Game/ITraitCollection.h"

// Third-party includes

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist::Game {
    class SkillCollection final : public ISkillCollection{
    public:
        SkillCollection(
            std::shared_ptr<IStatCollection> statCollection,
            std::shared_ptr<ITraitCollection> traitCollection
        );

        int skillTagged(SKILL skill) const override;
        void setSkillTagged(SKILL skill, int value) override;

        int skillBaseValue(SKILL skill) const override;

        int skillGainedValue(SKILL skill) const override;
        void setSkillGainedValue(SKILL skill, int value) override;

        int skillValue(SKILL skill) const override;

    private:
        std::shared_ptr<IStatCollection> _statCollection;
        std::shared_ptr<ITraitCollection> _traitCollection;

        std::vector<int> _skillsTagged = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::vector<int> _skillsGainedValue = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    };
}
