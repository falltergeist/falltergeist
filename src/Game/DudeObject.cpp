// Project includes
#include "../Format/Gcd/File.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/WeaponItemObject.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib
#include <cmath>
#include <functional>

namespace Falltergeist
{
    namespace Game
    {
        DudeObject::DudeObject(
            std::shared_ptr<IStatCollection> statCollection,
            std::shared_ptr<ITraitCollection> traitCollection
        ) : CritterObject(statCollection, traitCollection) {
            _type = Type::DUDE;
            setLightIntensity(65536);
            setLightRadius(4);
        }

        void DudeObject::loadFromGCDFile(Format::Gcd::File* gcd)
        {
            for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++) {
                statCollection()->setStat((STAT)i, gcd->stat((STAT)i));
                statCollection()->setStatBonus((STAT)i, gcd->statBonus((STAT)i));
            }

            _statsPoints = gcd->characterPoints();
            _name = gcd->name();
            _age = gcd->age();

            _hitPointsMax = gcd->hitPoints() + gcd->hitPointsBonus();
            _hitPoints = _hitPointsMax;

            if ((signed)gcd->firstTrait() >= 0) {
                traitCollection()->addTrait(gcd->firstTrait());
            }
            if ((signed)gcd->secondTrait() >= 0) {
                traitCollection()->addTrait(gcd->secondTrait());
            }

            if ((signed)gcd->firstTaggedSkill() >= 0) {
                setSkillTagged(gcd->firstTaggedSkill(), 1);
                _skillsPoints--;
            }
            if ((signed)gcd->secondTaggedSkill() >= 0) {
                setSkillTagged(gcd->secondTaggedSkill(), 1);
                _skillsPoints--;
            }
            if ((signed)gcd->thirdTaggedSkill() >= 0) {
                setSkillTagged(gcd->thirdTaggedSkill(), 1);
                _skillsPoints--;
            }

            setGender(gcd->gender());
            setActionPoints(actionPointsMax());
        }

        int DudeObject::experience() const
        {
            return _experience;
        }

        void DudeObject::setExperience(int value)
        {
            _experience = value;
        }

        std::string DudeObject::biography() const
        {
            return _biography;
        }

        void DudeObject::setBiography(const std::string& value)
        {
            _biography = value;
        }

        int DudeObject::statsPoints() const
        {
            return _statsPoints;
        }

        void DudeObject::setStatsPoints(int value)
        {
            _statsPoints = value;
        }

        int DudeObject::skillsPoints() const
        {
            return _skillsPoints;
        }

        void DudeObject::setSkillsPoints(int value)
        {
            _skillsPoints = value;
        }

        int DudeObject::hitPointsMax() const
        {
            int value = 15;
            value += statCollection()->statTotal(STAT::ENDURANCE) * 2;
            value += statCollection()->statTotal(STAT::STRENGTH);
            value += (2 + static_cast<int>(ceil(statCollection()->statTotal(STAT::ENDURANCE)/2))) * (level() - 1);
            return value;
        }

        int DudeObject::level() const
        {
            return _level;
        }

        void DudeObject::setLevel(int value)
        {
            _level = value;
        }

        int DudeObject::armorClass() const
        {
            unsigned int value = 0;
            if (!traitCollection()->hasTrait(TRAIT::KAMIKAZE)) {
                value += statCollection()->statTotal(STAT::AGILITY) > 10 ? 10 : statCollection()->statTotal(STAT::AGILITY);
            }
            return value;

        }

        int DudeObject::actionPointsMax() const
        {
            unsigned int value = 0;
            value += 5 + static_cast<int>(ceil(statCollection()->statTotal(STAT::AGILITY) / 2));
            if (traitCollection()->hasTrait(TRAIT::BRUISER)) {
                value -= 2;
            }
            return value;
        }

        unsigned int DudeObject::carryWeightMax() const
        {
            unsigned int value = 0;
            unsigned int st = statCollection()->statTotal(STAT::STRENGTH);

            if (traitCollection()->hasTrait(TRAIT::SMALL_FRAME)) {
                value += 25 + 15*(st > 10 ? 10 : st);
                if (traitCollection()->hasTrait(TRAIT::GIFTED) && st <= 10) {
                    value += 10;
                }
            } else {
                value += 25 + 25*(st > 10 ? 10 : st);
            }
            return value;
        }

        int DudeObject::meleeDamage() const
        {
            unsigned int value = 0;
            unsigned int st = statCollection()->statTotal(STAT::STRENGTH);
            if (st > 10) {
                st = 10;
            }
            value += st > 5 ? st - 5 : 1;
            if (traitCollection()->hasTrait(TRAIT::HEAVY_HANDED)) {
                value += 4;
            }
            return value;
        }

        int DudeObject::damageResistance() const
        {
            return 0;
        }

        int DudeObject::radiationResistance() const
        {
            return 0;
        }

        int DudeObject::poisonResistance() const
        {
            int value = 0;
            if (!traitCollection()->hasTrait(TRAIT::FAST_METABOLISM)) {
                value += 5 * statCollection()->statTotal(STAT::ENDURANCE);
            }
            return value;
        }

        int DudeObject::sequence() const
        {
            unsigned int value = 0;
            unsigned int pe = statCollection()->statTotal(STAT::PERCEPTION);
            value += 2*(pe > 10 ? 10 : pe);
            if (traitCollection()->hasTrait(TRAIT::KAMIKAZE)) {
                value += 5;
            }
            return value;
        }

        int DudeObject::healingRate() const
        {
            int value = 0;
            int en = statCollection()->statTotal(STAT::ENDURANCE);
            value += static_cast<int>(ceil((en > 10 ? 10 : en) / 3));
            if (value == 0) {
                value = 1;
            }

            if (traitCollection()->hasTrait(TRAIT::FAST_METABOLISM)) {
                value += 2;
            }
            return value;
        }

        int DudeObject::criticalChance() const
        {
            unsigned int value = 0;
            unsigned int lk = statCollection()->statTotal(STAT::LUCK);
            value += lk > 10 ? 10 : lk;
            if (traitCollection()->hasTrait(TRAIT::FINESSE)) {
                value += 10;
            }
            return value;
        }

        void DudeObject::_generateUi()
        {
            CritterObject::_generateUi();
        }

        Graphics::Point DudeObject::eggOffset()
        {
            return animation()->frameOffset() + animation()->shift() - Graphics::Point(63, 78);
        }

        std::string DudeObject::scrName() const
        {
            return _name;
        }
    }
}
