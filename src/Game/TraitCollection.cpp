// Project includes
#include "../Exception.h"
#include "../Game/TraitCollection.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist::Game {
    bool TraitCollection::hasTrait(TRAIT trait) const {
        if (trait > TRAIT::GIFTED) {
            throw Exception("Trait out of range:" + std::to_string((unsigned)trait));
        }
        return _traitsTagged.at((unsigned) trait);
    }

    void TraitCollection::addTrait(TRAIT trait) {
        if (trait > TRAIT::GIFTED) {
            throw Exception("Trait out of range:" + std::to_string((unsigned)trait));
        }
        _traitsTagged.at((unsigned)trait) = true;
    }

    void TraitCollection::removeTrait(TRAIT trait) {
        if (trait > TRAIT::GIFTED) {
            throw Exception("Trait out of range:" + std::to_string((unsigned)trait));
        }
        _traitsTagged.at((unsigned)trait) = false;
    }

    uint8_t TraitCollection::traitsCount() const {
        uint8_t selectedTraits = 0;
        for (unsigned i = (unsigned)TRAIT::FAST_METABOLISM; i <= (unsigned)TRAIT::GIFTED; i++)
        {
            if (hasTrait((TRAIT)i)) {
                selectedTraits++;
            }
        }
        return selectedTraits;
    }
}
