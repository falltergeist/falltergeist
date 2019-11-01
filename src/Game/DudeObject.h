#pragma once

#include "../Game/CritterObject.h"
#include "../Graphics/Point.h"

namespace Falltergeist
{
    using Graphics::Point;

    namespace Format
    {
        namespace Gcd
        {
            class File;
        }
    }
    namespace Game
    {
        /**
         * Player-controlled critter
         */
        class DudeObject : public CritterObject
        {
            public:
                DudeObject();
                ~DudeObject() override = default;

                void loadFromGCDFile(Format::Gcd::File* gcd);

                int experience() const;
                void setExperience(int value);

                std::string biography() const;
                void setBiography(const std::string& value);

                int statsPoints() const;
                void setStatsPoints(int value);

                int skillsPoints() const;
                void setSkillsPoints(int value);

                int level() const;
                void setLevel(int value);

                int damageResistance() const;
                int poisonResistance() const;
                int radiationResistance() const;

                int hitPointsMax() const override;
                int actionPointsMax() const override;
                int armorClass() const override;
                int meleeDamage() const override;
                int sequence() const override;
                int healingRate() const override;
                int criticalChance() const override;
                unsigned int carryWeightMax() const override;

                std::string scrName() const override;

                /**
                 * Offset where to draw egg relative to dude hex.
                 */
                Point eggOffset();

            protected:
                int _level = 1;
                int _experience = 0;
                int _statsPoints = 0;
                int _skillsPoints = 3;
                std::string _biography;
                void _generateUi() override;
        };
    }
}
