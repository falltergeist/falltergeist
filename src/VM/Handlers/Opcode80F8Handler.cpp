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

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Graphics/Rect.h"
#include "../../LocationCamera.h"
#include "../../Logger.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Handlers/Opcode80F8Handler.h"
#include "../../VM/VM.h"


// Third party includes

namespace Falltergeist
{

Opcode80F8Handler::Opcode80F8Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80F8Handler::_run()
{
    Logger::debug("SCRIPT") << "[80F8] [=] bool tile_is_visible (int hex)" << std::endl;
    int hexnum = _vm->dataStack()->popInteger();
    auto hex = Game::getInstance()->locationState()->hexagonGrid()->at(hexnum);
    bool inrect = Graphics::Rect::inRect( Point( hex->position() - Game::getInstance()->locationState()->camera()->topLeft() ),
                                          Game::getInstance()->locationState()->camera()->size() );
    _vm->dataStack()->push(inrect);
}

}


