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
#include "../Exception.h"
#include "../VM/OpcodeFactory.h"
#include "../VM/Handlers/Opcode8002Handler.h"
#include "../VM/Handlers/Opcode8003Handler.h"
#include "../VM/Handlers/Opcode8004Handler.h"
#include "../VM/Handlers/Opcode8005Handler.h"
#include "../VM/Handlers/Opcode800CHandler.h"
#include "../VM/Handlers/Opcode800DHandler.h"
#include "../VM/Handlers/Opcode8010Handler.h"
#include "../VM/Handlers/Opcode8012Handler.h"
#include "../VM/Handlers/Opcode8013Handler.h"
#include "../VM/Handlers/Opcode8014Handler.h"
#include "../VM/Handlers/Opcode8015Handler.h"
#include "../VM/Handlers/Opcode8016Handler.h"
#include "../VM/Handlers/Opcode8018Handler.h"
#include "../VM/Handlers/Opcode8019Handler.h"
#include "../VM/Handlers/Opcode801AHandler.h"
#include "../VM/Handlers/Opcode801BHandler.h"
#include "../VM/Handlers/Opcode801CHandler.h"
#include "../VM/Handlers/Opcode8027Handler.h"
#include "../VM/Handlers/Opcode8028Handler.h"
#include "../VM/Handlers/Opcode8029Handler.h"
#include "../VM/Handlers/Opcode802AHandler.h"
#include "../VM/Handlers/Opcode802BHandler.h"
#include "../VM/Handlers/Opcode802CHandler.h"
#include "../VM/Handlers/Opcode802FHandler.h"
#include "../VM/Handlers/Opcode8030Handler.h"
#include "../VM/Handlers/Opcode8031Handler.h"
#include "../VM/Handlers/Opcode8032Handler.h"
#include "../VM/Handlers/Opcode8033Handler.h"
#include "../VM/Handlers/Opcode8034Handler.h"
#include "../VM/Handlers/Opcode8035Handler.h"
#include "../VM/Handlers/Opcode8036Handler.h"
#include "../VM/Handlers/Opcode8037Handler.h"
#include "../VM/Handlers/Opcode8038Handler.h"
#include "../VM/Handlers/Opcode8039Handler.h"
#include "../VM/Handlers/Opcode803AHandler.h"
#include "../VM/Handlers/Opcode803BHandler.h"
#include "../VM/Handlers/Opcode803CHandler.h"
#include "../VM/Handlers/Opcode803DHandler.h"
#include "../VM/Handlers/Opcode803EHandler.h"
#include "../VM/Handlers/Opcode803FHandler.h"
#include "../VM/Handlers/Opcode8040Handler.h"
#include "../VM/Handlers/Opcode8041Handler.h"
#include "../VM/Handlers/Opcode8045Handler.h"
#include "../VM/Handlers/Opcode8046Handler.h"
#include "../VM/Handlers/Opcode80A1Handler.h"
#include "../VM/Handlers/Opcode80A3Handler.h"
#include "../VM/Handlers/Opcode80A4Handler.h"
#include "../VM/Handlers/Opcode80A6Handler.h"
#include "../VM/Handlers/Opcode80A7Handler.h"
#include "../VM/Handlers/Opcode80A8Handler.h"
#include "../VM/Handlers/Opcode80A9Handler.h"
#include "../VM/Handlers/Opcode80AAHandler.h"
#include "../VM/Handlers/Opcode80ABHandler.h"
#include "../VM/Handlers/Opcode80ACHandler.h"
#include "../VM/Handlers/Opcode80AEHandler.h"
#include "../VM/Handlers/Opcode80AFHandler.h"
#include "../VM/Handlers/Opcode80B0Handler.h"
#include "../VM/Handlers/Opcode80B2Handler.h"
#include "../VM/Handlers/Opcode80B4Handler.h"
#include "../VM/Handlers/Opcode80B6Handler.h"
#include "../VM/Handlers/Opcode80B7Handler.h"
#include "../VM/Handlers/Opcode80B8Handler.h"
#include "../VM/Handlers/Opcode80B9Handler.h"
#include "../VM/Handlers/Opcode80BAHandler.h"
#include "../VM/Handlers/Opcode80BBHandler.h"
#include "../VM/Handlers/Opcode80BCHandler.h"
#include "../VM/Handlers/Opcode80BDHandler.h"
#include "../VM/Handlers/Opcode80BFHandler.h"
#include "../VM/Handlers/Opcode80C1Handler.h"
#include "../VM/Handlers/Opcode80C2Handler.h"
#include "../VM/Handlers/Opcode80C3Handler.h"
#include "../VM/Handlers/Opcode80C4Handler.h"
#include "../VM/Handlers/Opcode80C5Handler.h"
#include "../VM/Handlers/Opcode80C6Handler.h"
#include "../VM/Handlers/Opcode80C7Handler.h"
#include "../VM/Handlers/Opcode80C8Handler.h"
#include "../VM/Handlers/Opcode80C9Handler.h"
#include "../VM/Handlers/Opcode80CAHandler.h"
#include "../VM/Handlers/Opcode80CBHandler.h"
#include "../VM/Handlers/Opcode80CCHandler.h"
#include "../VM/Handlers/Opcode80CEHandler.h"
#include "../VM/Handlers/Opcode80CFHandler.h"
#include "../VM/Handlers/Opcode80D0Handler.h"
#include "../VM/Handlers/Opcode80D2Handler.h"
#include "../VM/Handlers/Opcode80D3Handler.h"
#include "../VM/Handlers/Opcode80D4Handler.h"
#include "../VM/Handlers/Opcode80D5Handler.h"
#include "../VM/Handlers/Opcode80D8Handler.h"
#include "../VM/Handlers/Opcode80D9Handler.h"
#include "../VM/Handlers/Opcode80DAHandler.h"
#include "../VM/Handlers/Opcode80DCHandler.h"
#include "../VM/Handlers/Opcode80DEHandler.h"
#include "../VM/Handlers/Opcode80DFHandler.h"
#include "../VM/Handlers/Opcode80E1Handler.h"
#include "../VM/Handlers/Opcode80E3Handler.h"
#include "../VM/Handlers/Opcode80E4Handler.h"
#include "../VM/Handlers/Opcode80E5Handler.h"
#include "../VM/Handlers/Opcode80E7Handler.h"
#include "../VM/Handlers/Opcode80E8Handler.h"
#include "../VM/Handlers/Opcode80E9Handler.h"
#include "../VM/Handlers/Opcode80EAHandler.h"
#include "../VM/Handlers/Opcode80ECHandler.h"
#include "../VM/Handlers/Opcode80EFHandler.h"
#include "../VM/Handlers/Opcode80F0Handler.h"
#include "../VM/Handlers/Opcode80F1Handler.h"
#include "../VM/Handlers/Opcode80F2Handler.h"
#include "../VM/Handlers/Opcode80F3Handler.h"
#include "../VM/Handlers/Opcode80F4Handler.h"
#include "../VM/Handlers/Opcode80F6Handler.h"
#include "../VM/Handlers/Opcode80F7Handler.h"
#include "../VM/Handlers/Opcode80F9Handler.h"
#include "../VM/Handlers/Opcode80FAHandler.h"
#include "../VM/Handlers/Opcode80FBHandler.h"
#include "../VM/Handlers/Opcode80FCHandler.h"
#include "../VM/Handlers/Opcode80FDHandler.h"
#include "../VM/Handlers/Opcode80FEHandler.h"
#include "../VM/Handlers/Opcode80FFHandler.h"
#include "../VM/Handlers/Opcode8100Handler.h"
#include "../VM/Handlers/Opcode8101Handler.h"
#include "../VM/Handlers/Opcode8102Handler.h"
#include "../VM/Handlers/Opcode8105Handler.h"
#include "../VM/Handlers/Opcode8106Handler.h"
#include "../VM/Handlers/Opcode810AHandler.h"
#include "../VM/Handlers/Opcode810BHandler.h"
#include "../VM/Handlers/Opcode810CHandler.h"
#include "../VM/Handlers/Opcode810DHandler.h"
#include "../VM/Handlers/Opcode810EHandler.h"
#include "../VM/Handlers/Opcode810FHandler.h"
#include "../VM/Handlers/Opcode8113Handler.h"
#include "../VM/Handlers/Opcode8115Handler.h"
#include "../VM/Handlers/Opcode8116Handler.h"
#include "../VM/Handlers/Opcode8117Handler.h"
#include "../VM/Handlers/Opcode8118Handler.h"
#include "../VM/Handlers/Opcode8119Handler.h"
#include "../VM/Handlers/Opcode811CHandler.h"
#include "../VM/Handlers/Opcode811DHandler.h"
#include "../VM/Handlers/Opcode811EHandler.h"
#include "../VM/Handlers/Opcode8120Handler.h"
#include "../VM/Handlers/Opcode8121Handler.h"
#include "../VM/Handlers/Opcode8122Handler.h"
#include "../VM/Handlers/Opcode8123Handler.h"
#include "../VM/Handlers/Opcode8126Handler.h"
#include "../VM/Handlers/Opcode8127Handler.h"
#include "../VM/Handlers/Opcode8128Handler.h"
#include "../VM/Handlers/Opcode8129Handler.h"
#include "../VM/Handlers/Opcode812DHandler.h"
#include "../VM/Handlers/Opcode812EHandler.h"
#include "../VM/Handlers/Opcode812FHandler.h"
#include "../VM/Handlers/Opcode8130Handler.h"
#include "../VM/Handlers/Opcode8131Handler.h"
#include "../VM/Handlers/Opcode8132Handler.h"
#include "../VM/Handlers/Opcode8134Handler.h"
#include "../VM/Handlers/Opcode8136Handler.h"
#include "../VM/Handlers/Opcode8137Handler.h"
#include "../VM/Handlers/Opcode8138Handler.h"
#include "../VM/Handlers/Opcode8139Handler.h"
#include "../VM/Handlers/Opcode813CHandler.h"
#include "../VM/Handlers/Opcode8143Handler.h"
#include "../VM/Handlers/Opcode8147Handler.h"
#include "../VM/Handlers/Opcode8149Handler.h"
#include "../VM/Handlers/Opcode814BHandler.h"
#include "../VM/Handlers/Opcode814CHandler.h"
#include "../VM/Handlers/Opcode814EHandler.h"
#include "../VM/Handlers/Opcode8150Handler.h"
#include "../VM/Handlers/Opcode8151Handler.h"
#include "../VM/Handlers/Opcode8153Handler.h"
#include "../VM/Handlers/Opcode8154Handler.h"
#include "../VM/Handlers/Opcode9001Handler.h"
#include "../VM/Handlers/OpcodeC001Handler.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

OpcodeHandler* OpcodeFactory::createOpcode(unsigned int number, VM* vm)
{
    switch (number)
    {
        case 0x8000: // O_NOOP
            break;
        case 0x8002:
            return new Opcode8002Handler(vm);
            break;
        case 0x8003:
            return new Opcode8003Handler(vm);
            break;
        case 0x8004:
            return new Opcode8004Handler(vm);
            break;
        case 0x8005:
            return new Opcode8005Handler(vm);
            break;
        case 0x800C:
            return new Opcode800CHandler(vm);
            break;
        case 0x800D:
            return new Opcode800DHandler(vm);
            break;
        case 0x8010:
            return new Opcode8010Handler(vm);
            break;
        case 0x8012:
            return new Opcode8012Handler(vm);
            break;
        case 0x8013:
            return new Opcode8013Handler(vm);
            break;
        case 0x8014:
            return new Opcode8014Handler(vm);
            break;
        case 0x8015:
            return new Opcode8015Handler(vm);
            break;
        case 0x8016:
            return new Opcode8016Handler(vm);
            break;
        case 0x8018:
            return new Opcode8018Handler(vm);
            break;
        case 0x8019:
            return new Opcode8019Handler(vm);
            break;
        case 0x801A:
            return new Opcode801AHandler(vm);
            break;
        case 0x801B:
            return new Opcode801BHandler(vm);
            break;
        case 0x801C:
            return new Opcode801CHandler(vm);
            break;
        case 0x8027:
            return new Opcode8027Handler(vm);
            break;
        case 0x8028:
            return new Opcode8028Handler(vm);
            break;
        case 0x8029:
            return new Opcode8029Handler(vm);
            break;
        case 0x802A:
            return new Opcode802AHandler(vm);
            break;
        case 0x802B:
            return new Opcode802BHandler(vm);
            break;
        case 0x802C:
            return new Opcode802CHandler(vm);
            break;
        case 0x802F:
            return new Opcode802FHandler(vm);
            break;
        case 0x8030:
            return new Opcode8030Handler(vm);
            break;
        case 0x8031:
            return new Opcode8031Handler(vm);
            break;
        case 0x8032:
            return new Opcode8032Handler(vm);
            break;
        case 0x8033:
            return new Opcode8033Handler(vm);
            break;
        case 0x8034:
            return new Opcode8034Handler(vm);
            break;
        case 0x8035:
            return new Opcode8035Handler(vm);
            break;
        case 0x8036:
            return new Opcode8036Handler(vm);
            break;
        case 0x8037:
            return new Opcode8037Handler(vm);
            break;
        case 0x8038:
            return new Opcode8038Handler(vm);
            break;
        case 0x8039:
            return new Opcode8039Handler(vm);
            break;
        case 0x803A:
            return new Opcode803AHandler(vm);
            break;
        case 0x803B:
            return new Opcode803BHandler(vm);
            break;
        case 0x803C:
            return new Opcode803CHandler(vm);
            break;
        case 0x803D:
            return new Opcode803DHandler(vm);
            break;
        case 0x803E:
            return new Opcode803EHandler(vm);
            break;
        case 0x803F:
            return new Opcode803FHandler(vm);
            break;
        case 0x8040:
            return new Opcode8040Handler(vm);
            break;
        case 0x8041:
            return new Opcode8041Handler(vm);
            break;
        case 0x8045:
            return new Opcode8045Handler(vm);
            break;
        case 0x8046:
            return new Opcode8046Handler(vm);
            break;
        case 0x80A1:
            return new Opcode80A1Handler(vm);
            break;
        case 0x80A3:
            return new Opcode80A3Handler(vm);
            break;
        case 0x80A4:
            return new Opcode80A4Handler(vm);
            break;
        case 0x80A6:
            return new Opcode80A6Handler(vm);
            break;
        case 0x80A7:
            return new Opcode80A7Handler(vm);
            break;
        case 0x80A8:
            return new Opcode80A8Handler(vm);
            break;
        case 0x80A9:
            return new Opcode80A9Handler(vm);
            break;
        case 0x80AA:
            return new Opcode80AAHandler(vm);
            break;
        case 0x80AB:
            return new Opcode80ABHandler(vm);
            break;
        case 0x80AC:
            return new Opcode80ACHandler(vm);
            break;
        case 0x80AE:
            return new Opcode80AEHandler(vm);
            break;
        case 0x80AF:
            return new Opcode80AFHandler(vm);
            break;
        case 0x80B0:
            return new Opcode80B0Handler(vm);
            break;
        case 0x80B2:
            return new Opcode80B2Handler(vm);
            break;
        case 0x80B4:
            return new Opcode80B4Handler(vm);
            break;
        case 0x80B6:
            return new Opcode80B6Handler(vm);
            break;
        case 0x80B7:
            return new Opcode80B7Handler(vm);
            break;
        case 0x80B8:
            return new Opcode80B8Handler(vm);
            break;
        case 0x80B9:
            return new Opcode80B9Handler(vm);
            break;
        case 0x80BA:
            return new Opcode80BAHandler(vm);
            break;
        case 0x80BB:
            return new Opcode80BBHandler(vm);
            break;
        case 0x80BC:
            return new Opcode80BCHandler(vm);
            break;
        case 0x80BD:
            return new Opcode80BDHandler(vm);
            break;
        case 0x80BF:
            return new Opcode80BFHandler(vm);
            break;
        case 0x80C1:
            return new Opcode80C1Handler(vm);
            break;
        case 0x80C2:
            return new Opcode80C2Handler(vm);
            break;
        case 0x80C3:
            return new Opcode80C3Handler(vm);
            break;
        case 0x80C4:
            return new Opcode80C4Handler(vm);
            break;
        case 0x80C5:
            return new Opcode80C5Handler(vm);
            break;
        case 0x80C6:
            return new Opcode80C6Handler(vm);
            break;
        case 0x80C7:
            return new Opcode80C7Handler(vm);
            break;
        case 0x80C8:
            return new Opcode80C8Handler(vm);
            break;
        case 0x80C9:
            return new Opcode80C9Handler(vm);
            break;
        case 0x80CA:
            return new Opcode80CAHandler(vm);
            break;
        case 0x80CB:
            return new Opcode80CBHandler(vm);
            break;
        case 0x80CC:
            return new Opcode80CCHandler(vm);
            break;
        case 0x80CE:
            return new Opcode80CEHandler(vm);
            break;
        case 0x80CF:
            return new Opcode80CFHandler(vm);
            break;
        case 0x80D0:
            return new Opcode80D0Handler(vm);
            break;
        case 0x80D2:
            return new Opcode80D2Handler(vm);
            break;
        case 0x80D3:
            return new Opcode80D3Handler(vm);
            break;
        case 0x80D4:
            return new Opcode80D4Handler(vm);
            break;
        case 0x80D5:
            return new Opcode80D5Handler(vm);
            break;
        case 0x80D8:
            return new Opcode80D8Handler(vm);
            break;
        case 0x80D9:
            return new Opcode80D9Handler(vm);
            break;
        case 0x80DA:
            return new Opcode80DAHandler(vm);
            break;
        case 0x80DC:
            return new Opcode80DCHandler(vm);
            break;
        case 0x80DE:
            return new Opcode80DEHandler(vm);
            break;
        case 0x80DF:
            return new Opcode80DFHandler(vm);
            break;
        case 0x80E1:
            return new Opcode80E1Handler(vm);
            break;
        case 0x80E3:
            return new Opcode80E3Handler(vm);
            break;
        case 0x80E4:
            return new Opcode80E4Handler(vm);
            break;
        case 0x80E5:
            return new Opcode80E5Handler(vm);
            break;
        case 0x80E7:
            return new Opcode80E7Handler(vm);
            break;
        case 0x80E8:
            return new Opcode80E8Handler(vm);
            break;
        case 0x80E9:
            return new Opcode80E9Handler(vm);
            break;
        case 0x80EA:
            return new Opcode80EAHandler(vm);
            break;
        case 0x80EC:
            return new Opcode80ECHandler(vm);
            break;
        case 0x80EF:
            return new Opcode80EFHandler(vm);
            break;
        case 0x80F0:
            return new Opcode80F0Handler(vm);
            break;
        case 0x80F1:
            return new Opcode80F1Handler(vm);
            break;
        case 0x80F2:
            return new Opcode80F2Handler(vm);
            break;
        case 0x80F3:
            return new Opcode80F3Handler(vm);
            break;
        case 0x80F4:
            return new Opcode80F4Handler(vm);
            break;
        case 0x80F6:
            return new Opcode80F6Handler(vm);
            break;
        case 0x80F7:
            return new Opcode80F7Handler(vm);
            break;
        case 0x80F9:
            return new Opcode80F9Handler(vm);
            break;
        case 0x80FA:
            return new Opcode80FAHandler(vm);
            break;
        case 0x80FB:
            return new Opcode80FBHandler(vm);
            break;
        case 0x80FC:
            return new Opcode80FCHandler(vm);
            break;
        case 0x80FD:
            return new Opcode80FDHandler(vm);
            break;
        case 0x80FE:
            return new Opcode80FEHandler(vm);
            break;
        case 0x80FF:
            return new Opcode80FFHandler(vm);
            break;
        case 0x8100:
            return new Opcode8100Handler(vm);
            break;
        case 0x8101:
            return new Opcode8101Handler(vm);
            break;
        case 0x8102:
            return new Opcode8102Handler(vm);
            break;
        case 0x8105:
            return new Opcode8105Handler(vm);
            break;
        case 0x8106:
            return new Opcode8106Handler(vm);
            break;
        case 0x810A:
            return new Opcode810AHandler(vm);
            break;
        case 0x810B:
            return new Opcode810BHandler(vm);
            break;
        case 0x810C:
            return new Opcode810CHandler(vm);
            break;
        case 0x810D:
            return new Opcode810DHandler(vm);
            break;
        case 0x810E:
            return new Opcode810EHandler(vm);
            break;
        case 0x810F:
            return new Opcode810FHandler(vm);
            break;
        case 0x8113:
            return new Opcode8113Handler(vm);
            break;
        case 0x8115:
            return new Opcode8115Handler(vm);
            break;
        case 0x8116:
            return new Opcode8115Handler(vm);
            break;
        case 0x8117:
            return new Opcode8117Handler(vm);
            break;
        case 0x8118:
            return new Opcode8118Handler(vm);
            break;
        case 0x8119:
            return new Opcode8119Handler(vm);
            break;
        case 0x811C:
            return new Opcode811CHandler(vm);
            break;
        case 0x811D:
            return new Opcode811DHandler(vm);
            break;
        case 0x811E:
            return new Opcode811EHandler(vm);
            break;
        case 0x8120:
            return new Opcode8120Handler(vm);
            break;
        case 0x8121:
            return new Opcode8121Handler(vm);
            break;
        case 0x8122:
            return new Opcode8122Handler(vm);
            break;
        case 0x8123:
            return new Opcode8123Handler(vm);
            break;
        case 0x8126:
            return new Opcode8126Handler(vm);
            break;
        case 0x8127:
            return new Opcode8127Handler(vm);
            break;
        case 0x8128:
            return new Opcode8128Handler(vm);
            break;
        case 0x8129:
            return new Opcode8129Handler(vm);
            break;
        case 0x812D:
            return new Opcode812DHandler(vm);
            break;
        case 0x812E:
            return new Opcode812EHandler(vm);
            break;
        case 0x812F:
            return new Opcode812FHandler(vm);
            break;
        case 0x8130:
            return new Opcode8130Handler(vm);
            break;
        case 0x8131:
            return new Opcode8131Handler(vm);
            break;
        case 0x8132:
            return new Opcode8132Handler(vm);
            break;
        case 0x8134:
            return new Opcode8134Handler(vm);
            break;
        case 0x8136:
            return new Opcode8136Handler(vm);
            break;
        case 0x8137:
            return new Opcode8137Handler(vm);
            break;
        case 0x8138:
            return new Opcode8138Handler(vm);
            break;
        case 0x8139:
            return new Opcode8139Handler(vm);
            break;
        case 0x813C:
            return new Opcode813CHandler(vm);
            break;
        case 0x8143:
            return new Opcode8143Handler(vm);
            break;
        case 0x8147:
            return new Opcode8147Handler(vm);
            break;
        case 0x8149:
            return new Opcode8149Handler(vm);
            break;
        case 0x814B:
            return new Opcode814BHandler(vm);
            break;
        case 0x814C:
            return new Opcode814CHandler(vm);
            break;
        case 0x814E:
            return new Opcode814EHandler(vm);
            break;
        case 0x8150:
            return new Opcode8150Handler(vm);
            break;
        case 0x8151:
            return new Opcode8151Handler(vm);
            break;
        case 0x8153:
            return new Opcode8153Handler(vm);
            break;
        case 0x8154:
            return new Opcode8154Handler(vm);
            break;
        case 0x9001:
            return new Opcode9001Handler(vm);
            break;
        case 0xC001:
            return new OpcodeC001Handler(vm);
            break;
        default:
            throw Exception("OpcodeFactory::createOpcode() - unimplemented opcode: " + std::to_string(number));
    }
}

}
