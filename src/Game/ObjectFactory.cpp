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
    auto proto = ResourceManager::proFileType(PID);
    GameObject* object = 0;
    switch (proto->typeId())
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
        {
            switch(proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_ITEM_AMMO:
                {
                    object = new GameAmmoItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_ARMOR:
                {
                    object = new GameArmorItemObject();
                    for (unsigned int i = 0; i != 9; ++i)
                    {
                        ((GameArmorItemObject*)object)->setDamageResist(i, proto->damageResist()->at(i));
                        ((GameArmorItemObject*)object)->setDamageThreshold(i, proto->damageThreshold()->at(i));
                    }
                    ((GameArmorItemObject*)object)->setPerk(proto->perk());
                    ((GameArmorItemObject*)object)->setMaleFID(proto->armorMaleFID());
                    ((GameArmorItemObject*)object)->setFemaleFID(proto->armorFemaleFID());
                    ((GameArmorItemObject*)object)->setArmorClass(proto->armorClass());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_CONTAINER:
                {
                    object = new GameContainerItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_DRUG:
                {
                    object = new GameDrugItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_KEY:
                {
                    object = new GameKeyItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_MISC:
                {
                    object = new GameMiscItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_WEAPON:
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
            ((GameItemObject*)object)->setInventoryFID(proto->inventoryFID());
            auto msg = ResourceManager::msgFileType("text/english/game/pro_item.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case libfalltergeist::ProFileType::TYPE_CRITTER:
        {
            object = new GameCritterObject();
            auto msg = ResourceManager::msgFileType("text/english/game/pro_crit.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            for (unsigned int i = 0; i != 7; ++i)
            {
                ((GameCritterObject*)object)->setStat(i, proto->critterStats()->at(i));
                ((GameCritterObject*)object)->setStatBonus(i, proto->critterStatsBonus()->at(i));
            }
            for (unsigned int i = 0; i != 18; ++i)
            {
                ((GameCritterObject*)object)->setSkillTagged(i, proto->critterSkills()->at(i));
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
            for (unsigned int i = 0; i != 9; ++i)
            {
                ((GameCritterObject*)object)->setDamageResist(i, proto->damageResist()->at(i));
                ((GameCritterObject*)object)->setDamageThreshold(i, proto->damageThreshold()->at(i));
            }
            break;
        }
        case libfalltergeist::ProFileType::TYPE_SCENERY:
        {
            switch (proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_SCENERY_DOOR:
                {
                    object = new GameDoorSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_ELEVATOR:
                {
                    object = new GameElevatorSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_GENERIC:
                {
                    object = new GameGenericSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_TOP:
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                {
                    object = new GameLadderSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_STAIRS:
                {
                    object = new GameStairsSceneryObject();
                    break;
                }
            }
            auto msg = ResourceManager::msgFileType("text/english/game/pro_scen.msg");
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
                    object->setLightOrientation(GameObject::ORIENTATION_NS);
                    break;
                case 0x0800:
                    object->setLightOrientation(GameObject::ORIENTATION_EW);
                    break;
                case 0x1000:
                    object->setLightOrientation(GameObject::ORIENTATION_NC);
                    break;
                case 0x2000:
                    object->setLightOrientation(GameObject::ORIENTATION_SC);
                    break;
                case 0x4000:
                    object->setLightOrientation(GameObject::ORIENTATION_EC);
                    break;
                case 0x8000:
                    object->setLightOrientation(GameObject::ORIENTATION_WC);
                    break;
            }
            break;
        }
        case libfalltergeist::ProFileType::TYPE_WALL:
        {
            object = new GameWallObject();
            auto msg = ResourceManager::msgFileType("text/english/game/pro_wall.msg");
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
                    object->setLightOrientation(GameObject::ORIENTATION_NS);
                    break;
                case 0x0800:
                    object->setLightOrientation(GameObject::ORIENTATION_EW);
                    break;
                case 0x1000:
                    object->setLightOrientation(GameObject::ORIENTATION_NC);
                    break;
                case 0x2000:
                    object->setLightOrientation(GameObject::ORIENTATION_SC);
                    break;
                case 0x4000:
                    object->setLightOrientation(GameObject::ORIENTATION_EC);
                    break;
                case 0x8000:
                    object->setLightOrientation(GameObject::ORIENTATION_WC);
                    break;
            }
            break;
        }
        case libfalltergeist::ProFileType::TYPE_TILE:
        {
            throw Exception("GameObjectFactory - unexpected tile object");
        }
        case libfalltergeist::ProFileType::TYPE_MISC:
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

            auto msg = ResourceManager::msgFileType("text/english/game/pro_misc.msg");
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
    object->setCanWalkThru(proto->flags()&0x00000010);

    object->setTrans(GameObject::TRANS_NONE);
    if (proto->flags()&0x00004000) object->setTrans(GameObject::TRANS_RED);
    if (proto->flags()&0x00008000) object->setTrans(GameObject::TRANS_NONE);
    if (proto->flags()&0x00010000) object->setTrans(GameObject::TRANS_WALL);
    if (proto->flags()&0x00020000) object->setTrans(GameObject::TRANS_GLASS);
    if (proto->flags()&0x00040000) object->setTrans(GameObject::TRANS_STEAM);
    if (proto->flags()&0x00080000) object->setTrans(GameObject::TRANS_ENERGY);

    if (proto->scriptId() > 0)
    {
        auto intFile = ResourceManager::intFileType(proto->scriptId());
        if (intFile) object->setScript(new VM(intFile, object));
    }

    return object;
}

}
}
