#include "../Fallout/GcdFileType.h"
#include "../Fallout/DatFileItem.h"

#include <iostream>

namespace Falltergeist
{

GcdFileType::GcdFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _init();
}

void GcdFileType::_init()
{
    _datFileItem->seek(0);
    // unknown 4 bytes
    _datFileItem->skip(4);
    // primary stats
    (*_datFileItem) >> strength
                    >> perception
                    >> endurance
                    >> charisma
                    >> intelligence
                    >> agility
                    >> luck;
    // secondary stats
    (*_datFileItem) >> hitPoints
                    >> actionPoints
                    >> armorClass;
    // unknown
    _datFileItem->skip(4);
    (*_datFileItem) >> meleeDamage
                    >> carryWeight
                    >> sequence
                    >> healingRate
                    >> criticalChance
                    >> criticalHitModifier
                    >> damageThresholdNormal
                    >> damageThresholdLaser
                    >> damageThresholdFire
                    >> damageThresholdPlasma
                    >> damageThresholdElectrical
                    >> damageThresholdEMP
                    >> damageThresholdExplosive
                    >> damageResistanceNormal
                    >> damageResistanceLaser
                    >> damageResistanceFire
                    >> damageResistancePlasma
                    >> damageResistanceElectrical
                    >> damageResistanceEMP
                    >> damageResistanceExplosive
                    >> radiationResistance
                    >> poisonResistance
                    >> age
                    >> gender;
    // bonuses to primary stats
    (*_datFileItem) >> strengthBonus
                    >> perceptionBonus
                    >> enduranceBonus
                    >> charismaBonus
                    >> intelligenceBonus
                    >> agilityBonus
                    >> luckBonus;
    // bonuses to secondary stats
    (*_datFileItem) >> hitPointsBonus
                    >> actionPointsBonus
                    >> armorClassBonus;
    // unknown bonus
    _datFileItem->skip(4);
    (*_datFileItem) >> meleeDamageBonus
                    >> carryWeightBonus
                    >> sequenceBonus
                    >> healingRateBonus
                    >> criticalChanceBonus
                    >> criticalHitModifierBonus
                    >> damageThresholdNormalBonus
                    >> damageThresholdLaserBonus
                    >> damageThresholdFireBonus
                    >> damageThresholdPlasmaBonus
                    >> damageThresholdElectricalBonus
                    >> damageThresholdEMPBonus
                    >> damageThresholdExplosiveBonus
                    >> damageResistanceNormalBonus
                    >> damageResistanceLaserBonus
                    >> damageResistanceFireBonus
                    >> damageResistancePlasmaBonus
                    >> damageResistanceElectricalBonus
                    >> damageResistanceEMPBonus
                    >> damageResistanceExplosiveBonus
                    >> radiationResistanceBonus
                    >> poisonResistanceBonus
                    >> ageBonus
                    >> genderBonus;
    //skills
    (*_datFileItem) >> smallGunsSkill
                    >> bigGunsSkill
                    >> energyWeaponsSkill
                    >> unarmedSkill
                    >> meleeWeaponsSkill
                    >> throwingWeaponsSkill
                    >> firstAidSkill
                    >> doctorSkill
                    >> sneakSkill
                    >> lockpickSkill
                    >> stealSkill
                    >> trapsSkill
                    >> scienceSkill
                    >> repairSkill
                    >> speechSkill
                    >> barterSkill
                    >> gamblingSkill
                    >> outdoorsmanSkill;
    // unknown
    _datFileItem->skip(16);

    // name
    name = new char[32];
    for (int i=0; i != 32; ++i) (*_datFileItem) >> name[i];

    (*_datFileItem) >> firstTaggedSkill
                    >> secondTaggedSkill
                    >> thirdTaggedSkill
                    >> fourthTaggedSkill
                    >> firstTrait
                    >> secondTrait
                    >> characterPoints;
}



}
