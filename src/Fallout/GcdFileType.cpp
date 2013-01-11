/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Fallout/GcdFileType.h"

#include <iostream>

namespace Falltergeist
{

GcdFileType::GcdFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _init();
}

void GcdFileType::_init()
{
    setPosition(0);
    // unknown 4 bytes
    skipBytes(4);
    // primary stats
    (*this) >> strength
            >> perception
            >> endurance
            >> charisma
            >> intelligence
            >> agility
            >> luck;
    // secondary stats
    (*this) >> hitPoints
            >> actionPoints
            >> armorClass;
    // unknown
    skipBytes(4);
    (*this) >> meleeDamage
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
    (*this) >> strengthBonus
            >> perceptionBonus
            >> enduranceBonus
            >> charismaBonus
            >> intelligenceBonus
            >> agilityBonus
            >> luckBonus;
    // bonuses to secondary stats
    (*this) >> hitPointsBonus
            >> actionPointsBonus
            >> armorClassBonus;
    // unknown bonus
    skipBytes(4);
    (*this) >> meleeDamageBonus
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
    (*this) >> smallGunsSkill
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
    skipBytes(16);

    // name
    name = new char[32];
    for (int i=0; i != 32; ++i) (*this) >> name[i];

    (*this) >> firstTaggedSkill
            >> secondTaggedSkill
            >> thirdTaggedSkill
            >> fourthTaggedSkill
            >> firstTrait
            >> secondTrait
            >> characterPoints;
}



}
