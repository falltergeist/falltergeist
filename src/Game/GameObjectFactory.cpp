/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameElevatorSceneryObject.h"
#include "../Game/GameGenericSceneryObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameLadderSceneryObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameMiscObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameStairsSceneryObject.h"
#include "../Game/GameWallObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../Engine/ResourceManager.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

GameObjectFactory::GameObjectFactory()
{
}

std::shared_ptr<GameObject> GameObjectFactory::createObject(unsigned int PID)
{
    auto proto = ResourceManager::proFileType(PID);
    std::shared_ptr<GameObject> object;
    switch (proto->typeId())
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
        {
            switch(proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_ITEM_AMMO:
                {
                    object = std::shared_ptr<GameAmmoItemObject>(new GameAmmoItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_ARMOR:
                {
                    object = std::shared_ptr<GameArmorItemObject>(new GameArmorItemObject());
                    for (unsigned int i = 0; i != 9; ++i)
                    {
                        ((GameArmorItemObject*)object.get())->setDamageResist(i, proto->damageResist()->at(i));
                        ((GameArmorItemObject*)object.get())->setDamageThreshold(i, proto->damageThreshold()->at(i));
                    }
                    ((GameArmorItemObject*)object.get())->setPerk(proto->perk());
                    ((GameArmorItemObject*)object.get())->setMaleFID(proto->armorMaleFID());
                    ((GameArmorItemObject*)object.get())->setFemaleFID(proto->armorFemaleFID());
                    ((GameArmorItemObject*)object.get())->setArmorClass(proto->armorClass());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_CONTAINER:
                {
                    object = std::shared_ptr<GameContainerItemObject>(new GameContainerItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_DRUG:
                {
                    object = std::shared_ptr<GameDrugItemObject>(new GameDrugItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_KEY:
                {
                    object = std::shared_ptr<GameKeyItemObject>(new GameKeyItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_MISC:
                {
                    object = std::shared_ptr<GameMiscItemObject>(new GameMiscItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_WEAPON:
                {
                    object = std::shared_ptr<GameWeaponItemObject>(new GameWeaponItemObject());

                    ((GameWeaponItemObject*)object.get())->setPerk(proto->perk());
                    ((GameWeaponItemObject*)object.get())->setAnimationCode(proto->weaponAnimationCode());
                    ((GameWeaponItemObject*)object.get())->setDamageMin(proto->weaponDamageMin());
                    ((GameWeaponItemObject*)object.get())->setDamageMax(proto->weaponDamageMax());
                    ((GameWeaponItemObject*)object.get())->setDamageType(proto->weaponDamageType());
                    ((GameWeaponItemObject*)object.get())->setRangePrimary(proto->weaponRangePrimary());
                    ((GameWeaponItemObject*)object.get())->setRangeSecondary(proto->weaponRangeSecondary());
                    ((GameWeaponItemObject*)object.get())->setMinimumStrenght(proto->weaponMinimumStrenght());
                    ((GameWeaponItemObject*)object.get())->setActionCostPrimary(proto->weaponActionCostPrimary());
                    ((GameWeaponItemObject*)object.get())->setActionCostSecondary(proto->weaponActionCostSecondary());
                    ((GameWeaponItemObject*)object.get())->setBurstRounds(proto->weaponBurstRounds());
                    ((GameWeaponItemObject*)object.get())->setAmmoType(proto->weaponAmmoType());
                    ((GameWeaponItemObject*)object.get())->setAmmoPID(proto->weaponAmmoPID());
                    ((GameWeaponItemObject*)object.get())->setAmmoCapacity(proto->weaponAmmoCapacity());
                    break;
                }
            }
            ((GameItemObject*)object.get())->setWeight(proto->weight());
            ((GameItemObject*)object.get())->setInventoryFID(proto->inventoryFID());
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
            object = std::shared_ptr<GameCritterObject>(new GameCritterObject());
            auto msg = ResourceManager::msgFileType("text/english/game/pro_crit.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            for (unsigned int i = 0; i != 7; ++i)
            {
                ((GameCritterObject*)object.get())->setStat(i, proto->critterStats()->at(i));
                ((GameCritterObject*)object.get())->setStatBonus(i, proto->critterStatsBonus()->at(i));
            }
            for (unsigned int i = 0; i != 18; ++i)
            {
                ((GameCritterObject*)object.get())->setSkill(i, proto->critterSkills()->at(i));
            }
            ((GameCritterObject*)object.get())->setActionPoints(proto->critterActionPoints());
            ((GameCritterObject*)object.get())->setHitPointsMax(proto->critterHitPointsMax());
            ((GameCritterObject*)object.get())->setArmorClass(proto->critterArmorClass());
            ((GameCritterObject*)object.get())->setCarryWeightMax(proto->critterCarryWeightMax());
            ((GameCritterObject*)object.get())->setMeleeDamage(proto->critterMeleeDamage());
            ((GameCritterObject*)object.get())->setSequence(proto->critterSequence());
            ((GameCritterObject*)object.get())->setCriticalChance(proto->critterCriticalChance());
            ((GameCritterObject*)object.get())->setHealingRate(proto->critterHealingRate());
            for (unsigned int i = 0; i != 9; ++i)
            {
                ((GameCritterObject*)object.get())->setDamageResist(i, proto->damageResist()->at(i));
                ((GameCritterObject*)object.get())->setDamageThreshold(i, proto->damageThreshold()->at(i));
            }
            break;
        }
        case libfalltergeist::ProFileType::TYPE_SCENERY:
        {
            switch (proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_SCENERY_DOOR:
                {
                    object = std::shared_ptr<GameDoorSceneryObject>(new GameDoorSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_ELEVATOR:
                {
                    object = std::shared_ptr<GameElevatorSceneryObject>(new GameElevatorSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_GENERIC:
                {
                    object = std::shared_ptr<GameGenericSceneryObject>(new GameGenericSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_TOP:
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                {
                    object = std::shared_ptr<GameLadderSceneryObject>(new GameLadderSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_STAIRS:
                {
                    object = std::shared_ptr<GameStairsSceneryObject>(new GameStairsSceneryObject());
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
            break;
        }
        case libfalltergeist::ProFileType::TYPE_WALL:
        {
            object = std::shared_ptr<GameWallObject>(new GameWallObject());
            auto msg = ResourceManager::msgFileType("text/english/game/pro_wall.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case libfalltergeist::ProFileType::TYPE_TILE:
        {
            //auto msg = ResourceManager::msgFileType("text/english/game/pro_tile.msg");
            throw 1;
            //object->setName(msg->message(proto->messageId())->text());
            break;
        }
        case libfalltergeist::ProFileType::TYPE_MISC:
        {
            object = std::shared_ptr<GameMiscObject>(new GameMiscObject());
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

    if (proto->scriptId() > 0)
    {
        auto intFile = ResourceManager::intFileType(proto->scriptId());
        if (intFile) object->scripts()->push_back(new VM(intFile, object));
    }

    return object;
}

}
