// Project includes
#include "../../VM/Handler/Opcode80CAHandler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CA::Opcode80CA(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80CA::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[80CA] [+] int value = get_critter_stat(GameCritterObject* who, int number)" << std::endl;
                int number = script.dataStack()->popInteger();
                debug << "    number = " << number << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("get_critter_stat(who, stat) - who is NULL");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (!critter) {
                    _error("get_critter_stat(who, stat) - who is not a critter");
                }
                int result = 0;
                switch (number) {
                    case 0: // ST
                    case 1: // PE
                    case 2: // EN
                    case 3: // CH
                    case 4: // IN
                    case 5: // AG
                    case 6: // LU
                    {
                        result = critter->statTotal((STAT) number);
                        break;
                    }
                    case 7: // max hit points
                    {
                        result = critter->hitPointsMax();
                        break;
                    }
                    case 8: // max action points
                    {
                        result = critter->actionPointsMax();
                        break;
                    }
                    case 9: // armor class
                    {
                        result = critter->armorClass();
                        break;
                    }
                    case 11: // melee damage
                    {
                        result = critter->meleeDamage();
                        break;
                    }
                    case 12: // carry weight max
                    {
                        result = critter->carryWeightMax();
                        break;
                    }
                    case 13: // sequence
                    {
                        result = critter->sequence();
                        break;
                    }
                    case 14: // heal rate
                    {
                        result = critter->healingRate();
                        break;
                    }
                    case 15: // crit chance
                    {
                        result = critter->criticalChance();
                        break;
                    }
                    case 16: // better criticals
                        // @TODO
                        break;
                    case 17: //
                    {
                        result = critter->damageThreshold(DAMAGE::NORMAL);
                        break;
                    }
                    case 18: //
                    {
                        result = critter->damageThreshold(DAMAGE::LASER);
                        break;
                    }
                    case 19: //
                    {
                        result = critter->damageThreshold(DAMAGE::FIRE);
                        break;
                    }
                    case 20: //
                    {
                        result = critter->damageThreshold(DAMAGE::PLASMA);
                        break;
                    }
                    case 21: //
                    {
                        result = critter->damageThreshold(DAMAGE::ELECTRICAL);
                        break;
                    }
                    case 22: //
                    {
                        result = critter->damageThreshold(DAMAGE::EMP);
                        break;
                    }
                    case 23: //
                    {
                        result = critter->damageThreshold(DAMAGE::EXPLOSIVE);
                        break;
                    }
                    case 24: //
                    {
                        result = critter->damageResist(DAMAGE::NORMAL);
                        break;
                    }
                    case 25: //
                    {
                        result = critter->damageResist(DAMAGE::LASER);
                        break;
                    }
                    case 26: //
                    {
                        result = critter->damageResist(DAMAGE::FIRE);
                        break;
                    }
                    case 27: //
                    {
                        result = critter->damageResist(DAMAGE::PLASMA);
                        break;
                    }
                    case 28: //
                    {
                        result = critter->damageResist(DAMAGE::ELECTRICAL);
                        break;
                    }
                    case 29: //
                    {
                        result = critter->damageResist(DAMAGE::EMP);
                        break;
                    }
                    case 30: //
                    {
                        result = critter->damageResist(DAMAGE::EXPLOSIVE);
                        break;
                    }
                    case 31: // rad resist
                    {
                        result = critter->damageResist(DAMAGE::RADIATION);
                        break;
                    }
                    case 32: // poison resist
                    {
                        result = critter->damageResist(DAMAGE::POISON);
                        break;
                    }
                    case 33: // age
                    {
                        result = critter->age();
                        break;
                    }
                    case 34: // gender
                    {
                        result = (unsigned) critter->gender();
                        break;
                    }
                    case 35: // hit points
                    {
                        result = critter->hitPoints();
                        break;
                    }
                    case 36: // current poison
                    {
                        result = critter->poisonLevel();
                        break;
                    }
                    case 37: // current radiation
                    {
                        result = critter->radiationLevel();
                        break;
                    }
                    default: {
                        _error("VM::opcode80CA - unimplemented number:" + std::to_string(number));
                    }
                }
                script.dataStack()->push(result);
                debug << "    value  = " << result << std::endl;
            }
        }
    }
}
