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
#include "../../Exception.h"
#include "../../Logger.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Handlers/Opcode80CAHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80CAHandler::Opcode80CAHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80CAHandler::_run()
{
    int number = _vm->popDataInteger();
    auto critter = static_cast<Game::GameCritterObject*>(_vm->popDataPointer());
    if (!critter)
    {
        throw Exception("VM::opcode80CA pointer error");
    }

    int result;
    switch (number)
    {
        case 0: // ST
        case 1: // PE
        case 2: // EN
        case 3: // CH
        case 4: // IN
        case 5: // AG
        case 6: // LU
        {
            result = critter->statTotal(number);
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
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_NORMAL);
            break;
        }
        case 18: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_LASER);
            break;
        }
        case 19: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_FIRE);
            break;
        }
        case 20: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_PLASMA);
            break;
        }
        case 21: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_ELECTRICAL);
            break;
        }
        case 22: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_EMP);
            break;
        }
        case 23: // 
        {
            result = critter->damageThreshold(Game::GameCritterObject::DAMAGE_EXPLOSION);
            break;
        }
        case 24: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_NORMAL);
            break;
        }
        case 25: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_LASER);
            break;
        }
        case 26: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_FIRE);
            break;
        }
        case 27: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_PLASMA);
            break;
        }
        case 28: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_ELECTRICAL);
            break;
        }
        case 29: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_EMP);
            break;
        }
        case 30: // 
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_EXPLOSION);
            break;
        }
        case 31: // rad resist
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_RADIATION);
            break;
        }
        case 32: // poison resist
        {
            result = critter->damageResist(Game::GameCritterObject::DAMAGE_POISON);
            break;
        }
        case 33: // age
        {
            result = critter->gender();
            break;
        }
        case 34: // gender
        {
            result = critter->gender();
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
        default:
        {
            throw Exception("VM::opcode80CA - unimplemented number:" + std::to_string(number));
        }
    }
    _vm->pushDataInteger(result);
    Logger::debug("SCRIPT") << "[80CA] [+] int value = get_critter_stat(GameCritterObject* who, int number)" << std::endl
                            << "    number = " << number << std::endl
                            << "    value  = " << result << std::endl;
}

}
