// Project includes
#include "../Exception.h"
#include "../Game/SkillCollection.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist::Game {
    SkillCollection::SkillCollection(
        std::shared_ptr<IStatCollection> statCollection,
        std::shared_ptr<ITraitCollection> traitCollection
    ): _statCollection(statCollection), _traitCollection(traitCollection) {
    }

    int SkillCollection::skillTagged(SKILL skill) const {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::skillTagged(num) - num out of range:" + std::to_string((unsigned)skill));
        }
        return _skillsTagged.at((unsigned) skill);
    }

    void SkillCollection::setSkillTagged(SKILL skill, int value) {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::setSkillTagged(num, value) - num out of range:" + std::to_string((unsigned)skill));
        }
        _skillsTagged.at((unsigned)skill) = value;
    }

    int SkillCollection::skillBaseValue(SKILL skill) const {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::skillBaseValue(num) - num out of range:" + std::to_string((unsigned)skill));
        }
        int value = 0;
        switch(skill)
        {
            case SKILL::SMALL_GUNS:
                value += 5 + 4 * _statCollection->statTotal(STAT::AGILITY);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::BIG_GUNS:
                value += 2 * _statCollection->statTotal(STAT::AGILITY);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::ENERGY_WEAPONS:
                value += 2 * _statCollection->statTotal(STAT::AGILITY);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::UNARMED:
                value += 30 + 2 * (_statCollection->statTotal(STAT::AGILITY) + _statCollection->statTotal(STAT::STRENGTH));
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::MELEE_WEAPONS:
                value += 20 + 2 * (_statCollection->statTotal(STAT::AGILITY) + _statCollection->statTotal(STAT::STRENGTH));
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::THROWING:
                value += 4 * _statCollection->statTotal(STAT::AGILITY);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value -= 10;
                }
                break;
            case SKILL::FIRST_AID:
                value += 20 + 2*(_statCollection->statTotal(STAT::PERCEPTION) + _statCollection->statTotal(STAT::INTELLIGENCE));
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value += 15;
                }
                break;
            case SKILL::DOCTOR:
                value += 20 + 5 + (_statCollection->statTotal(STAT::PERCEPTION) + _statCollection->statTotal(STAT::INTELLIGENCE));
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value += 15;
                }
                break;
            case SKILL::SNEAK:
                value += 20 + 5 + 3 * _statCollection->statTotal(STAT::AGILITY);
                break;
            case SKILL::LOCKPICK:
                value += 20 + 10 + (_statCollection->statTotal(STAT::PERCEPTION) + _statCollection->statTotal(STAT::AGILITY));
                break;
            case SKILL::STEAL:
                value += 20 + 3 * _statCollection->statTotal(STAT::AGILITY);
                break;
            case SKILL::TRAPS:
                value += 20 + 10 + (_statCollection->statTotal(STAT::PERCEPTION) + _statCollection->statTotal(STAT::AGILITY));
                break;
            case SKILL::SCIENCE:
                value += 20 + 4 * _statCollection->statTotal(STAT::INTELLIGENCE);
                break;
            case SKILL::REPAIR:
                value += 20 + 3 * _statCollection->statTotal(STAT::INTELLIGENCE);
                break;
            case SKILL::SPEECH:
                value += 20 + 5 * _statCollection->statTotal(STAT::CHARISMA);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value += 15;
                }
                break;
            case SKILL::BARTER:
                value += 20 + 4 * _statCollection->statTotal(STAT::CHARISMA);
                if (_traitCollection->hasTrait(TRAIT::GOOD_NATURED)) {
                    value += 15;
                }
                break;
            case SKILL::GAMBLING:
                value += 20 + 5 * _statCollection->statTotal(STAT::LUCK);
                break;
            case SKILL::OUTDOORSMAN:
                value += 20 + 2 * (_statCollection->statTotal(STAT::ENDURANCE) + _statCollection->statTotal(STAT::INTELLIGENCE));
                break;
            default:
                break;
        }

        if (_traitCollection->hasTrait(TRAIT::GIFTED)) {
            value -= 10;
        }

        if (skillTagged(skill)) {
            value += 20;
        }

        return value;
    }

    int SkillCollection::skillGainedValue(SKILL skill) const {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::skillGainedValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
        }
        return _skillsGainedValue.at((unsigned)skill);
    }

    void SkillCollection::setSkillGainedValue(SKILL skill, int value) {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::setSkillGainedCalue(skill) - skill out of range:" + std::to_string((unsigned)skill));
        }
        _skillsGainedValue.at((unsigned)skill) = value;
    }

    int SkillCollection::skillValue(SKILL skill) const {
        if (skill > SKILL::OUTDOORSMAN) {
            throw Exception("CritterObject::skillValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
        }
        return skillBaseValue(skill) + skillGainedValue(skill);
    }
}
