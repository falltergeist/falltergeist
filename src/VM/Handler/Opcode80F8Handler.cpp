/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../../VM/Handler/Opcode80F8Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Graphics/Rect.h"
#include "../../LocationCamera.h"
#include "../../Logger.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F8::Opcode80F8(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80F8::_run()
            {
                Logger::debug("SCRIPT") << "[80F8] [=] bool tile_is_visible (int hex)" << std::endl;
                int hexnum = _script->dataStack()->popInteger();
                auto hex = Game::getInstance()->locationState()->hexagonGrid()->at(hexnum);
                bool inrect = Graphics::Rect::inRect( Point( hex->position() - Game::getInstance()->locationState()->camera()->topLeft() ),
                                                      Game::getInstance()->locationState()->camera()->size() );
                _script->dataStack()->push(inrect);
            }
        }
    }
}


