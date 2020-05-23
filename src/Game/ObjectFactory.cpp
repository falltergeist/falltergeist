#include "../Game/ObjectFactory.h"
#include "../Format/Int/File.h"
#include "../Format/Msg/File.h"
#include "../Format/Pro/File.h"
#include "../Game/AmmoItemObject.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/CritterObject.h"
#include "../Game/DoorSceneryObject.h"
#include "../Game/DrugItemObject.h"
#include "../Game/ElevatorSceneryObject.h"
#include "../Game/ExitMiscObject.h"
#include "../Game/GenericSceneryObject.h"
#include "../Game/KeyItemObject.h"
#include "../Game/LadderSceneryObject.h"
#include "../Game/MiscItemObject.h"
#include "../Game/StairsSceneryObject.h"
#include "../Game/WallObject.h"
#include "../Game/WeaponItemObject.h"
#include "../Exception.h"
#include "../ResourceManager.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        ObjectFactory* ObjectFactory::getInstance()
        {
            return Base::Singleton<ObjectFactory>::get();
        }

        std::shared_ptr<Object> ObjectFactory::createObject(unsigned int PID)
        {
            auto proto = ResourceManager::getInstance()->proFileType(PID);
            std::shared_ptr<Object> object;
            switch ((OBJECT_TYPE)proto->typeId())
            {
                case OBJECT_TYPE::ITEM:
                {
                    switch((ITEM_TYPE)proto->subtypeId())
                    {
                        case ITEM_TYPE::AMMO:
                        {
                            object = std::make_shared<AmmoItemObject>();
                            break;
                        }
                        case ITEM_TYPE::ARMOR:
                        {
                            std::shared_ptr<ArmorItemObject> armorObject = std::make_shared<ArmorItemObject>();
                            object = armorObject;
                            for (unsigned i = (unsigned)DAMAGE::NORMAL; i != (unsigned)DAMAGE::POISON; ++i)
                            {
                                armorObject->setDamageResist((DAMAGE)i, proto->damageResist()->at(i));
                                armorObject->setDamageThreshold((DAMAGE)i, proto->damageThreshold()->at(i));
                            }
                            armorObject->setPerk(proto->perk());
                            armorObject->setMaleFID(proto->armorMaleFID());
                            armorObject->setFemaleFID(proto->armorFemaleFID());
                            armorObject->setArmorClass(proto->armorClass());
                            break;
                        }
                        case ITEM_TYPE::CONTAINER:
                        {
                            object = std::make_shared<ContainerItemObject>();
                            break;
                        }
                        case ITEM_TYPE::DRUG:
                        {
                            object = std::make_shared<DrugItemObject>();
                            break;
                        }
                        case ITEM_TYPE::KEY:
                        {
                            object = std::make_shared<KeyItemObject>();
                            break;
                        }
                        case ITEM_TYPE::MISC:
                        {
                            object = std::make_shared<MiscItemObject>();
                            break;
                        }
                        case ITEM_TYPE::WEAPON:
                        {
                            std::shared_ptr<WeaponItemObject> weaponObject = std::make_shared<WeaponItemObject>();
                            object = weaponObject;

                            weaponObject->setPerk(proto->perk());
                            weaponObject->setAnimationCode(proto->weaponAnimationCode());
                            weaponObject->setDamageMin(proto->weaponDamageMin());
                            weaponObject->setDamageMax(proto->weaponDamageMax());
                            weaponObject->setDamageType(proto->weaponDamageType());
                            weaponObject->setRangePrimary(proto->weaponRangePrimary());
                            weaponObject->setRangeSecondary(proto->weaponRangeSecondary());
                            weaponObject->setMinimumStrength(proto->weaponMinimumStrenght());
                            weaponObject->setActionCostPrimary(proto->weaponActionCostPrimary());
                            weaponObject->setActionCostSecondary(proto->weaponActionCostSecondary());
                            weaponObject->setBurstRounds(proto->weaponBurstRounds());
                            weaponObject->setAmmoType(proto->weaponAmmoType());
                            weaponObject->setAmmoPID(proto->weaponAmmoPID());
                            weaponObject->setAmmoCapacity(proto->weaponAmmoCapacity());
                            break;
                        }
                    }
                    std::shared_ptr<ItemObject> itemObject = std::dynamic_pointer_cast<ItemObject>(object);
                    itemObject->setWeight(proto->weight());
                    // @TODO: ((GameItemObject*)object)->setVolume(proto->containerSize());
                    itemObject->setInventoryFID(proto->inventoryFID());
                    itemObject->setPrice(proto->basePrice());
                    auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_item.msg");
                    try
                    {
                        object->setName(msg->message(proto->messageId())->text());
                        object->setDescription(msg->message(proto->messageId() + 1)->text());
                    }
                    catch (const Exception&) {}
                    break;
                }
                case OBJECT_TYPE::CRITTER:
                {
                    std::shared_ptr<CritterObject> critterObject = std::make_shared<CritterObject>();
                    object = critterObject;
                    auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_crit.msg");
                    try
                    {
                        object->setName(msg->message(proto->messageId())->text());
                        object->setDescription(msg->message(proto->messageId() + 1)->text());
                    }
                    catch (const Exception&) {}

                    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
                    {
                        critterObject->setStat((STAT)i, proto->critterStats()->at(i));
                        critterObject->setStatBonus((STAT)i, proto->critterStatsBonus()->at(i));
                    }
                    for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
                    {
                        critterObject->setSkillTagged((SKILL)i, proto->critterSkills()->at(i));
                    }
                    critterObject->setActionPoints(proto->critterActionPoints());
                    critterObject->setActionPointsMax(proto->critterActionPoints());
                    critterObject->setCritterFlags(proto->critterFlags());
                    critterObject->setHitPointsMax(proto->critterHitPointsMax());
                    critterObject->setArmorClass(proto->critterArmorClass());
                    critterObject->setCarryWeightMax(proto->critterCarryWeightMax());
                    critterObject->setMeleeDamage(proto->critterMeleeDamage());
                    critterObject->setSequence(proto->critterSequence());
                    critterObject->setCriticalChance(proto->critterCriticalChance());
                    critterObject->setHealingRate(proto->critterHealingRate());
                    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::POISON; i++)
                    {
                        critterObject->setDamageResist((DAMAGE)i, proto->damageResist()->at(i));
                        critterObject->setDamageThreshold((DAMAGE)i, proto->damageThreshold()->at(i));
                    }
                    critterObject->setGender(proto->critterGender() ? GENDER::FEMALE : GENDER::MALE);
                    critterObject->setAge(proto->critterAge());
                    break;
                }
                case OBJECT_TYPE::SCENERY:
                {
                    switch ((SCENERY_TYPE)proto->subtypeId())
                    {
                        case SCENERY_TYPE::DOOR:
                        {
                            object = std::make_shared<DoorSceneryObject>();
                            break;
                        }
                        case SCENERY_TYPE::ELEVATOR:
                        {
                            object = std::make_shared<ElevatorSceneryObject>();
                            break;
                        }
                        case SCENERY_TYPE::GENERIC:
                        {
                            object = std::make_shared<GenericSceneryObject>();
                            break;
                        }
                        case SCENERY_TYPE::LADDER_TOP:
                        case SCENERY_TYPE::LADDER_BOTTOM:
                        {
                            object = std::make_shared<LadderSceneryObject>();
                            break;
                        }
                        case SCENERY_TYPE::STAIRS:
                        {
                            object = std::make_shared<StairsSceneryObject>();
                            break;
                        }
                    }
                    auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_scen.msg");
                    try
                    {
                        object->setName(msg->message(proto->messageId())->text());
                        object->setDescription(msg->message(proto->messageId() + 1)->text());
                    }
                    catch (const Exception&) {}

                    std::dynamic_pointer_cast<SceneryObject>(object)->setSoundId((char)proto->soundId());

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
                    object = std::make_shared<WallObject>();
                    auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_wall.msg");
                    try
                    {
                        object->setName(msg->message(proto->messageId())->text());
                        object->setDescription(msg->message(proto->messageId() + 1)->text());
                    }
                    catch (const Exception&) {}

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
                    throw Exception("ObjectFactory - unexpected tile object");
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
                            object = std::make_shared<ExitMiscObject>();
                            break;
                        default:
                            object = std::make_shared<MiscObject>();
                            break;
                    }

                    auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/pro_misc.msg");
                    try
                    {
                        object->setName(msg->message(proto->messageId())->text());
                        object->setDescription(msg->message(proto->messageId() + 1)->text());
                    }
                    catch (const Exception&) {}
                    break;
                }
            }
            object->setPID(PID);
            object->setFID(proto->FID());
            object->setFlags(proto->flags());

            if (proto->scriptId() > 0)
            {
                auto intFile = ResourceManager::getInstance()->intFileType(proto->scriptId());
                if (intFile) object->setScript(new VM::Script(intFile, object));
            }

            return object;
        }
    }
}
