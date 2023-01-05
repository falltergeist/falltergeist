// Project includes
#include "../Exception.h"
#include "../Game/StatCollection.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist::Game {
    StatCollection::StatCollection(std::shared_ptr<ITraitCollection> traitCollection): _traitCollection(traitCollection) {
    }

    int StatCollection::stat(STAT stat) const {
        if (stat > STAT::LUCK) {
            throw Exception("Stat out of range:" + std::to_string((unsigned)stat));
        }
        return _stats.at((unsigned)stat);
    }

    void StatCollection::setStat(STAT stat, int value) {
        if (stat > STAT::LUCK) {
            throw Exception("Stat num out of range:" + std::to_string((unsigned)stat));
        }
        _stats.at((unsigned)stat) = value;
    }

    int StatCollection::statTotal(STAT stat) const {
        if (stat > STAT::LUCK) {
            throw Exception("Stat out of range:" + std::to_string((unsigned)stat));
        }
        return this->stat(stat) + statBonus(stat);
    }

    int StatCollection::statBonus(STAT stat) const {
        if (stat > STAT::LUCK) {
            throw Exception("Stat out of range:" + std::to_string((unsigned)stat));
        }
        int bonus = 0;
        if (_traitCollection->hasTrait(TRAIT::GIFTED)) {
            bonus += 1;
        }
        switch(stat)
        {
            case STAT::STRENGTH:
                if (_traitCollection->hasTrait(TRAIT::BRUISER)) {
                    bonus += 2;
                }
                break;
            case STAT::AGILITY:
                if (_traitCollection->hasTrait(TRAIT::SMALL_FRAME)) {
                    bonus += 1;
                }
                break;
            default:
                break;
        }
        return _statsBonus.at((unsigned)stat) + bonus;
    }

    void StatCollection::setStatBonus(STAT stat, int value) {
        if (stat > STAT::LUCK) {
            throw Exception("Stat out of range:" + std::to_string((unsigned)stat));
        }
        _statsBonus.at((unsigned)stat) = value;
    }
}
