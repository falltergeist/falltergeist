/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// C++ standard includes

// Falltergeist includes
#include "AmmoItemObject.h"
#include "ArmorItemObject.h"
#include "ContainerItemObject.h"
#include "CritterObject.h"
#include "DoorSceneryObject.h"
#include "DrugItemObject.h"
#include "ElevatorSceneryObject.h"
#include "ExitMiscObject.h"
#include "GenericSceneryObject.h"
#include "KeyItemObject.h"
#include "LadderSceneryObject.h"
#include "MiscItemObject.h"
#include "MiscObject.h"
#include "ObjectFactory.h"
#include "StairsSceneryObject.h"
#include "WallObject.h"
#include "WeaponItemObject.h"
#include "../Exception.h"
#include "../ResourceManager.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameObjectFactory::GameObjectFactory()
{
}

GameObject* GameObjectFactory::createObject(unsigned int PID)
{
    auto proto = ResourceManager::getInstance()->proFileType(PID);
    GameObject* object = 0;
    switch ((OBJECT_TYPE)proto->typeId())
    {
        case OBJECT_TYPE::ITEM:
        {
            switch((ITEM_TYPE)proto->subtypeId())
            {
                case ITEM_TYPE::AMMO:
                {
                    object = new GameAmmoItemObject();
                    break;
                }
                case ITEM_TYPE::ARMOR:
                {
                    object = new GameArmorItemObject();
                    for (unsigned i = (unsigned)DAMAGE::NORMAL; i != (unsigned)DAMAGE::POISON; ++i)
                    {
                        ((GameArmorItemObject*)object)->setDamageResist((DAMAGE)i, proto->damageResist()->at(i));
                        ((GameArmorItemObject*)object)->setDamageThreshold((DAMAGE)i, proto->damageThreshold()->at(i));
                    }
                    ((GameArmorItemObject*)object)->setPerk(proto->perk());
                    ((GameArmorItemObject*)object)->setMaleFID(proto->armorMaleFID());
                    ((GameArmorItemObject*)object)->setFemaleFID(proto->armorFemaleFID());
                    ((GameArmorItemObject*)object)->setArmorClass(proto->armorClass());
                    break;
                }
                case ITEM_TYPE::CONTAINER:
                {
                    object = new GameContainerItemObject();
                    break;
                }
                case ITEM_TYPE::DRUG:
                {
                    object = new GameDrugItemObject();
                    break;
                }
                case ITEM_TYPE::KEY:
                {
                    object = new GameKeyItemObject();
                    break;
                }
                case ITEM_TYPE::MISC:
                {
                    object = new GameMiscItemObject();
                    break;
                }
                case ITEM_TYPE::WEAPON:
                {
                    object = new GameWeaponItemObject();

                    ((GameWeaponItemObject*)object)->setPerk(proto->perk());
                    ((GameWeaponItemObject*)object)->setAnimationCode(proto->weaponAnimationCode());
                    ((GameWeaponItemObject*)object)->setDamageMin(proto->weaponDamageMin());
                    ((GameWeaponItemObject*)object)->setDamageMax(proto->weaponDamageMax());
                    ((GameWeaponItemObject*)object)->setDamageType(proto->weaponDamageType());
                    ((GameWeaponItemObject*)object)->setRangePrimary(proto->weaponRangePrimary());
                    ((GameWeaponItemObject*)object)->setRangeSecondary(proto->weaponRangeSecondary());
                    ((GameWeaponItemObject*)object)->setMinimumStrength(proto->weaponMinimumStrenght());
                    ((GameWeaponItemObject*)object)->setActionCostPrimary(proto->weaponActionCostPrimary());
                    ((GameWeaponItemObject*)object)->setActionCostSecondary(proto->weaponActionCostSecondary());
                    ((GameWeaponItemObject*)object)->setBurstRounds(proto->weaponBurstRounds());
                    ((GameWeaponItemObject*)object)->setAmmoType(proto->weaponAmmoType());
                    ((GameWeaponItemObject*)object)->setAmmoPID(proto->weaponAmmoPID());
                    ((GameWeaponItemObject*)object)->setAmmoCapacity(proto->weaponAmmoCapacity());
                    break;
                }
            }
            ((GameItemObject*)object)->setWeight(proto->weight());
            // @TODO: ((GameItemObject*)object)->setVolume(proto->containerSize());
            ((GameItemObject*)object)->setInventoryFID(proto->inventoryFID());
            auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_item.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case OBJECT_TYPE::CRITTER:
        {
            object = new GameCritterObject();
            auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_crit.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
            {
                ((GameCritterObject*)object)->setStat((STAT)i, proto->critterStats()->at(i));
                ((GameCritterObject*)object)->setStatBonus((STAT)i, proto->critterStatsBonus()->at(i));
            }
            for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
            {
                ((GameCritterObject*)object)->setSkillTagged((SKILL)i, proto->critterSkills()->at(i));
            }
            ((GameCritterObject*)object)->setActionPoints(proto->critterActionPoints());
            ((GameCritterObject*)object)->setActionPointsMax(proto->critterActionPoints());
            ((GameCritterObject*)object)->setHitPointsMax(proto->critterHitPointsMax());
            ((GameCritterObject*)object)->setArmorClass(proto->critterArmorClass());
            ((GameCritterObject*)object)->setCarryWeightMax(proto->critterCarryWeightMax());
            ((GameCritterObject*)object)->setMeleeDamage(proto->critterMeleeDamage());
            ((GameCritterObject*)object)->setSequence(proto->critterSequence());
            ((GameCritterObject*)object)->setCriticalChance(proto->critterCriticalChance());
            ((GameCritterObject*)object)->setHealingRate(proto->critterHealingRate());
            for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::POISON; i++)
            {
                ((GameCritterObject*)object)->setDamageResist((DAMAGE)i, proto->damageResist()->at(i));
                ((GameCritterObject*)object)->setDamageThreshold((DAMAGE)i, proto->damageThreshold()->at(i));
            }
            break;
        }
        case OBJECT_TYPE::SCENERY:
        {
            switch ((SCENERY_TYPE)proto->subtypeId())
            {
                case SCENERY_TYPE::DOOR:
                {
                    object = new GameDoorSceneryObject();
                    break;
                }
                case SCENERY_TYPE::ELEVATOR:
                {
                    object = new GameElevatorSceneryObject();
                    break;
                }
                case SCENERY_TYPE::GENERIC:
                {
                    object = new GameGenericSceneryObject();
                    break;
                }
                case SCENERY_TYPE::LADDER_TOP:
                case SCENERY_TYPE::LADDER_BOTTOM:
                {
                    object = new GameLadderSceneryObject();
                    break;
                }
                case SCENERY_TYPE::STAIRS:
                {
                    object = new GameStairsSceneryObject();
                    break;
                }
            }
            auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_scen.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            ((GameSceneryObject*)object)->setSoundId((char)proto->soundId());

            //first two bytes are orientation. second two - unknown
            unsigned short orientation = proto->flagsExt() >> 16;
            switch (orientation)
            {
                case 0x0000:
                    object->setLightOrientation(Orientation::NS);
                    break;
                case 0x0800:
                    object->setLightOrientation(Orientation::EW);
                    break;
                case 0x1000:
                    object->setLightOrientation(Orientation::NC);
                    break;
                case 0x2000:
                    object->setLightOrientation(Orientation::SC);
                    break;
                case 0x4000:
                    object->setLightOrientation(Orientation::EC);
                    break;
                case 0x8000:
                    object->setLightOrientation(Orientation::WC);
                    break;
            }
            break;
        }
        case OBJECT_TYPE::WALL:
        {
            object = new GameWallObject();
            auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_wall.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            //first two bytes are orientation. second two - unknown
            unsigned short orientation = proto->flagsExt() >> 16;
            switch (orientation)
            {
                case 0x0000:
                    object->setLightOrientation(Orientation::NS);
                    break;
                case 0x0800:
                    object->setLightOrientation(Orientation::EW);
                    break;
                case 0x1000:
                    object->setLightOrientation(Orientation::NC);
                    break;
                case 0x2000:
                    object->setLightOrientation(Orientation::SC);
                    break;
                case 0x4000:
                    object->setLightOrientation(Orientation::EC);
                    break;
                case 0x8000:
                    object->setLightOrientation(Orientation::WC);
                    break;
            }
            break;
        }
        case OBJECT_TYPE::TILE:
        {
            throw Exception("GameObjectFactory - unexpected tile object");
        }
        case OBJECT_TYPE::MISC:
        {
            switch(PID& 0x00FFFFFF)
            {
                // Exit Grids
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    object = new GameExitMiscObject();
                    break;
                default:
                    object = new GameMiscObject();
                    break;
            }

            auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_misc.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
    }
    object->setPID(PID);
    object->setFID(proto->FID());
    object->setFlags(proto->flags());

    if (proto->scriptId() > 0)
    {
        auto intFile = ResourceManager::getInstance()->intFileType(proto->scriptId());
        if (intFile) object->setScript(new VM(intFile, object));
    }

    return object;
}

}
}
