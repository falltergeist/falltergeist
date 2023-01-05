#pragma once

// Project includes
#include "../Format/Enums.h"

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class IStatCollection {
    public:
        virtual int stat(STAT stat) const = 0;
        virtual void setStat(STAT stat, int value) = 0;

        virtual int statBonus(STAT stat) const = 0;
        virtual void setStatBonus(STAT stat, int value) = 0;

        // returns total stat value (with bonuses)
        virtual int statTotal(STAT num) const = 0;
    };
}
