#pragma once

// Project includes
#include "../Format/Enums.h"

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class ISkillCollection {
    public:
        virtual int skillTagged(SKILL skill) const = 0;

        // TODO split in two methods: tagSkill and untagSkill
        virtual void setSkillTagged(SKILL skill, int value) = 0;

        virtual int skillBaseValue(SKILL skill) const = 0;

        virtual int skillGainedValue(SKILL skill) const = 0;
        virtual void setSkillGainedValue(SKILL skill, int value) = 0;

        virtual int skillValue(SKILL skill) const = 0;
    };
}
