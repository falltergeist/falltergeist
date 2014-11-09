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
 */

// C++ standard includes

// Falltergeist includes
#include "../../Engine/Exception.h"
#include "../../Engine/Logger.h"
#include "../../Game/GameCritterObject.h"
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
    Logger::debug("SCRIPT") << "[80CA] [+] int get_critter_stat(GameCritterObject* who, int number)" << std::endl;
    int number = _vm->popDataInteger();
    auto critter = static_cast<GameCritterObject*>(_vm->popDataPointer());
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
        default:
        {
            throw Exception("VM::opcode80CA - unimplemented number:" + std::to_string(number));
        }
        _vm->pushDataInteger(result);
    }
}

}
