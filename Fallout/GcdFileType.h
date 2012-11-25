#ifndef FALLTERGEIST_GCDFILETYPE_H
#define FALLTERGEIST_GCDFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

class GcdFileType
{
protected:
    DatFileItem * _datFileItem;
    void _init();
public:
    // primary stats
    unsigned int strength;
    unsigned int perception;
    unsigned int endurance;
    unsigned int charisma;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int luck;
    // secondary stats
    unsigned int hitPoints;
    unsigned int actionPoints;
    unsigned int armorClass;
    //unsigned int unknown;
    unsigned int meleeDamage;
    unsigned int carryWeight;
    unsigned int sequence;
    unsigned int healingRate;
    unsigned int criticalChance;
    unsigned int criticalHitModifier;
    unsigned int damageThresholdNormal;
    unsigned int damageThresholdLaser;
    unsigned int damageThresholdFire;
    unsigned int damageThresholdPlasma;
    unsigned int damageThresholdElectrical;
    unsigned int damageThresholdEMP;
    unsigned int damageThresholdExplosive;
    unsigned int damageResistanceNormal;
    unsigned int damageResistanceLaser;
    unsigned int damageResistanceFire;
    unsigned int damageResistancePlasma;
    unsigned int damageResistanceElectrical;
    unsigned int damageResistanceEMP;
    unsigned int damageResistanceExplosive;
    unsigned int radiationResistance;
    unsigned int poisonResistance;
    unsigned int age;
    unsigned int gender;
    // bonuses to primary stats
    unsigned int strengthBonus;
    unsigned int perceptionBonus;
    unsigned int enduranceBonus;
    unsigned int charismaBonus;
    unsigned int intelligenceBonus;
    unsigned int agilityBonus;
    unsigned int luckBonus;
    // bonuses to secondaty stats
    unsigned int hitPointsBonus;
    unsigned int actionPointsBonus;
    unsigned int armorClassBonus;
    //unsigned int unknownBonus;
    unsigned int meleeDamageBonus;
    unsigned int carryWeightBonus;
    unsigned int sequenceBonus;
    unsigned int healingRateBonus;
    unsigned int criticalChanceBonus;
    unsigned int criticalHitModifierBonus;
    unsigned int damageThresholdNormalBonus;
    unsigned int damageThresholdLaserBonus;
    unsigned int damageThresholdFireBonus;
    unsigned int damageThresholdPlasmaBonus;
    unsigned int damageThresholdElectricalBonus;
    unsigned int damageThresholdEMPBonus;
    unsigned int damageThresholdExplosiveBonus;
    unsigned int damageResistanceNormalBonus;
    unsigned int damageResistanceLaserBonus;
    unsigned int damageResistanceFireBonus;
    unsigned int damageResistancePlasmaBonus;
    unsigned int damageResistanceElectricalBonus;
    unsigned int damageResistanceEMPBonus;
    unsigned int damageResistanceExplosiveBonus;
    unsigned int radiationResistanceBonus;
    unsigned int poisonResistanceBonus;
    unsigned int ageBonus;
    unsigned int genderBonus;
    //skills
    unsigned int smallGunsSkill;
    unsigned int bigGunsSkill;
    unsigned int energyWeaponsSkill;
    unsigned int unarmedSkill;
    unsigned int meleeWeaponsSkill;
    unsigned int throwingWeaponsSkill;
    unsigned int firstAidSkill;
    unsigned int doctorSkill;
    unsigned int sneakSkill;
    unsigned int lockpickSkill;
    unsigned int stealSkill;
    unsigned int trapsSkill;
    unsigned int scienceSkill;
    unsigned int repairSkill;
    unsigned int speechSkill;
    unsigned int barterSkill;
    unsigned int gamblingSkill;
    unsigned int outdoorsmanSkill;

    char * name;

    unsigned int firstTaggedSkill;
    unsigned int secondTaggedSkill;
    unsigned int thirdTaggedSkill;
    unsigned int fourthTaggedSkill;
    unsigned int firstTrait;
    unsigned int secondTrait;
    unsigned int characterPoints;

    GcdFileType(DatFileItem * datFileItem);
};

}
#endif // FALLTERGEIST_GCDFILETYPE_H
