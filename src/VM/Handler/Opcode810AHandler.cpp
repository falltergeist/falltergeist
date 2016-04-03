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
#include "../../VM/Handler/Opcode810AHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Base/StlFeatures.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../ResourceManager.h"
#include "../../UI/TextArea.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            using namespace Base;

            Opcode810A::Opcode810A(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode810A::_run()
            {
                Logger::debug("SCRIPT") << "[810A] [=] void float_msg(object who, string msg, int type) " << std::endl;
                int type = _script->dataStack()->popInteger();
                SDL_Color color = {0x00, 0x00, 0x00, 0xff};
                switch (type)
                {
                    case -2:
                        // CAPITAL RED LETTERS  FF 00 00
                        color = {0xff, 0x00, 0x00, 0xff};
                        break;
                    case -1:
                        // Self-rotating colors @todo
                        color = {0xff, 0x00, 0x00, 0xff}; // temporary taken from -2
                        break;
                    case 0:
                    case 8:
                    case 13:
                        color = {0xff, 0xff, 0x7f, 0xff};
                        break;
                    case 1:
                    case 5:
                    case 10:
                        color = {0x55, 0x55, 0x55, 0xff};
                        break;
                    case 2:
                        color = {0xff, 0x00, 0x00, 0xff};
                        break;
                    case 3:
                        color = {0x3c, 0xfb, 0x00, 0xff};
                        break;
                    case 4:
                        color = {0x30, 0x59, 0x8e, 0xff};
                        break;
                    case 6:
                        color = {0xa2, 0xa2, 0xa2, 0xff};
                        break;
                    case 7:
                        color = {0xff, 0x49, 0x49, 0xff};
                        break;
                    case 9:
                        color = {0xff, 0xff, 0xff, 0xff};
                        break;
                    case 11:
                        color = {0x3c, 0x3c, 0x3c, 0xff};
                        break;
                    case 12:
                        color = {0x75, 0x75, 0x75, 0xff};
                        break;
                    default:
                        _error("float_msg - wrong type: " + std::to_string(type));
                }

                auto string = _script->dataStack()->popString();
                auto object = _script->dataStack()->popObject();

                auto floatMessage = make_unique<UI::TextArea>(string);
                floatMessage->setWidth(200);
                floatMessage->setWordWrap(true);
                floatMessage->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
                floatMessage->setOutlineColor({0x00, 0x00, 0x00, 0xFF});
                floatMessage->setFont("font1.aaf", color);
                object->setFloatMessage(std::move(floatMessage));

            }
        }
    }
}
