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
#include "../../VM/Handlers/Opcode80DEHandler.h"
#include "../../States/CritterDialogState.h"
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Game.h"
#include "../../Game/GameCritterObject.h"
#include "../../VM/VM.h"
#include "../../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

Opcode80DEHandler::Opcode80DEHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80DEHandler::_run()
{
    auto dialog = std::shared_ptr<CritterDialogState>(new CritterDialogState());
    Game::getInstance()->setDialog(dialog);
    // @todo Implement!
    _vm->popDataInteger(); //auto backgroundIdx = popDataInteger();
    _vm->popDataInteger(); //auto headNum = popDataInteger();
    _vm->popDataInteger(); //auto mood = popDataInteger();
    auto critter = std::static_pointer_cast<GameCritterObject>(_vm->popDataPointer());
    if (!critter) throw Exception("VM::opcode80de - wrong critter pointers");

    dialog->setCritter(critter);
    dialog->setScript(_vm);

    _vm->popDataInteger(); //auto msgFileNum = popDataInteger();

    // logging
    CrossPlatform::debug("[*] void start_gdialog(int msgFileNum, GameCritterObject* who, int mood, int headNum, int backgroundIdx)", DEBUG_SCRIPT);
}

}
