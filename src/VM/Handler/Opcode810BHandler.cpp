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

// Related headers
#include "../../VM/Handler/Opcode810BHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810B::Opcode810B(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode810B::_run()
            {
                Logger::debug("SCRIPT") << "[810B] [*] int metarule(int type, value)" << std::endl;
                auto value = _script->dataStack()->pop();
                auto type = _script->dataStack()->popInteger();
                int result = 0;

                switch(type)
                {
                    case 14: // METARULE_TEST_FIRSTRUN
                        result = 1;
                        break;
                    case 16: // METARULE_PARTY_COUNT
                        result = 0;
                        break;
                    case 17: //  METARULE_AREA_KNOWN
                        result = 1;
                        break;
                    case 18: // METARULE_WHO_ON_DRUGS
                        result = 0;
                        break;
                    case 19: // METARULE_MAP_KNOWN
                        result = 1;
                        break;
                    case 22: // METARULE_IS_LOADGAME
                        result = 0;
                        break;
                    case 30: // METARULE_CAR_CURRENT_TOWN
                        result = 0;
                        break;
                    case 40: // METARULE_SKILL_CHECK_TAG
                        result = 0;
                        break;
                    case 44: // METARULE_GET_WORLDMAP_XPOS
                        result = 300;
                        break;
                    case 45: // METARULE_GET_WORLDMAP_YPOS
                        result = 300;
                        break;
                    case 46: // METARULE_CURRENT_TOWN
                        result = 0;
                        break;
                    default:
                        _error("metarule - unimplemented type: " + std::to_string(type));
                }

                _script->dataStack()->push(result);
            }
        }
    }
}
