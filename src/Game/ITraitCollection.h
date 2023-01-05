#pragma once

// Project includes
#include "../Format/Enums.h"

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class ITraitCollection {
    public:
        virtual bool hasTrait(TRAIT trait) const = 0;
        virtual void addTrait(TRAIT trait) = 0;
        virtual void removeTrait(TRAIT trait) = 0;
        virtual uint8_t traitsCount() const = 0;
    };
}
