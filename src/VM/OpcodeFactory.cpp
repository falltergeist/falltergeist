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
#include <sstream>

// Falltergeist includes
#include "../Base/StlFeatures.h"
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
#include "../VM/Handlers/OpcodeComparisonHandler.h"
#include "../VM/Handlers/Opcode8039Handler.h"
#include "../VM/Handlers/Opcode803AHandler.h"
#include "../VM/Handlers/Opcode803BHandler.h"
#include "../VM/Handlers/Opcode803CHandler.h"
#include "../VM/Handlers/Opcode803DHandler.h"
#include "../VM/Handlers/Opcode803EHandler.h"
#include "../VM/Handlers/Opcode803FHandler.h"
#include "../VM/Handlers/Opcode8040Handler.h"
#include "../VM/Handlers/Opcode8041Handler.h"
#include "../VM/Handlers/Opcode8042Handler.h"
#include "../VM/Handlers/Opcode8043Handler.h"
#include "../VM/Handlers/Opcode8044Handler.h"
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
#include "../VM/Handlers/Opcode80BEHandler.h"
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
#include "../VM/Handlers/Opcode8107Handler.h"
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
#include "../VM/Handlers/Opcode8145Handler.h"
#include "../VM/Handlers/Opcode8147Handler.h"
#include "../VM/Handlers/Opcode8149Handler.h"
#include "../VM/Handlers/Opcode814BHandler.h"
#include "../VM/Handlers/Opcode814CHandler.h"
#include "../VM/Handlers/Opcode814EHandler.h"
#include "../VM/Handlers/Opcode8150Handler.h"
#include "../VM/Handlers/Opcode8151Handler.h"
#include "../VM/Handlers/Opcode8152Handler.h"
#include "../VM/Handlers/Opcode8153Handler.h"
#include "../VM/Handlers/Opcode8154Handler.h"
#include "../VM/Handlers/Opcode9001Handler.h"
#include "../VM/Handlers/OpcodeC001Handler.h"
#include "../VM/Handlers/OpcodeA001Handler.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
using Base::make_unique;

std::unique_ptr<OpcodeHandler> OpcodeFactory::createOpcode(unsigned int number, VM* vm)
{
    switch (number)
    {
        case 0x8000: return make_unique<OpcodeHandler>(vm); // O_NOOP
        case 0x8002: return make_unique<Opcode8002Handler>(vm);
        case 0x8003: return make_unique<Opcode8003Handler>(vm);
        case 0x8004: return make_unique<Opcode8004Handler>(vm);
        case 0x8005: return make_unique<Opcode8005Handler>(vm);
        case 0x800C: return make_unique<Opcode800CHandler>(vm);
        case 0x800D: return make_unique<Opcode800DHandler>(vm);
        case 0x8010: return make_unique<Opcode8010Handler>(vm);
        case 0x8012: return make_unique<Opcode8012Handler>(vm);
        case 0x8013: return make_unique<Opcode8013Handler>(vm);
        case 0x8014: return make_unique<Opcode8014Handler>(vm);
        case 0x8015: return make_unique<Opcode8015Handler>(vm);
        case 0x8016: return make_unique<Opcode8016Handler>(vm);
        case 0x8018: return make_unique<Opcode8018Handler>(vm);
        case 0x8019: return make_unique<Opcode8019Handler>(vm);
        case 0x801A: return make_unique<Opcode801AHandler>(vm);
        case 0x801B: return make_unique<Opcode801BHandler>(vm);
        case 0x801C: return make_unique<Opcode801CHandler>(vm);
        case 0x8027: return make_unique<Opcode8027Handler>(vm);
        case 0x8028: return make_unique<Opcode8028Handler>(vm);
        case 0x8029: return make_unique<Opcode8029Handler>(vm);
        case 0x802A: return make_unique<Opcode802AHandler>(vm);
        case 0x802B: return make_unique<Opcode802BHandler>(vm);
        case 0x802C: return make_unique<Opcode802CHandler>(vm);
        case 0x802F: return make_unique<Opcode802FHandler>(vm);
        case 0x8030: return make_unique<Opcode8030Handler>(vm);
        case 0x8031: return make_unique<Opcode8031Handler>(vm);
        case 0x8032: return make_unique<Opcode8032Handler>(vm);
        case 0x8033: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::EQUAL);
        case 0x8034: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::NOT_EQUAL);
        case 0x8035: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::LESS_EQUAL);
        case 0x8036: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::GREATER_EQUAL);
        case 0x8037: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::LESS);
        case 0x8038: return make_unique<OpcodeComparisonHandler>(vm, OpcodeComparisonHandler::Type::GREATER);
        case 0x8039: return make_unique<Opcode8039Handler>(vm);
        case 0x803A: return make_unique<Opcode803AHandler>(vm);
        case 0x803B: return make_unique<Opcode803BHandler>(vm);
        case 0x803C: return make_unique<Opcode803CHandler>(vm);
        case 0x803D: return make_unique<Opcode803DHandler>(vm);
        case 0x803E: return make_unique<Opcode803EHandler>(vm);
        case 0x803F: return make_unique<Opcode803FHandler>(vm);
        case 0x8040: return make_unique<Opcode8040Handler>(vm);
        case 0x8041: return make_unique<Opcode8041Handler>(vm);
        case 0x8042: return make_unique<Opcode8042Handler>(vm); // bwxor
        case 0x8043: return make_unique<Opcode8043Handler>(vm); // bwnot
        case 0x8044: return make_unique<Opcode8044Handler>(vm);
        case 0x8045: return make_unique<Opcode8045Handler>(vm);
        case 0x8046: return make_unique<Opcode8046Handler>(vm);
        case 0x80A1: return make_unique<Opcode80A1Handler>(vm);
        case 0x80A3: return make_unique<Opcode80A3Handler>(vm);
        case 0x80A4: return make_unique<Opcode80A4Handler>(vm);
        case 0x80A6: return make_unique<Opcode80A6Handler>(vm);
        case 0x80A7: return make_unique<Opcode80A7Handler>(vm);
        case 0x80A8: return make_unique<Opcode80A8Handler>(vm);
        case 0x80A9: return make_unique<Opcode80A9Handler>(vm);
        case 0x80AA: return make_unique<Opcode80AAHandler>(vm);
        case 0x80AB: return make_unique<Opcode80ABHandler>(vm);
        case 0x80AC: return make_unique<Opcode80ACHandler>(vm);
        case 0x80AE: return make_unique<Opcode80AEHandler>(vm);
        case 0x80AF: return make_unique<Opcode80AFHandler>(vm);
        case 0x80B0: return make_unique<Opcode80B0Handler>(vm);
        case 0x80B2: return make_unique<Opcode80B2Handler>(vm);
        case 0x80B4: return make_unique<Opcode80B4Handler>(vm);
        case 0x80B6: return make_unique<Opcode80B6Handler>(vm);
        case 0x80B7: return make_unique<Opcode80B7Handler>(vm);
        case 0x80B8: return make_unique<Opcode80B8Handler>(vm);
        case 0x80B9: return make_unique<Opcode80B9Handler>(vm);
        case 0x80BA: return make_unique<Opcode80BAHandler>(vm);
        case 0x80BB: return make_unique<Opcode80BBHandler>(vm);
        case 0x80BC: return make_unique<Opcode80BCHandler>(vm); // self_obj
        case 0x80BD: return make_unique<Opcode80BDHandler>(vm); // source_obj
        case 0x80BE: return make_unique<Opcode80BEHandler>(vm); // target_obj
        case 0x80BF: return make_unique<Opcode80BFHandler>(vm); // dude_obj
        case 0x80C0: return make_unique<Opcode80BEHandler>(vm); // obj_being_used_with - uses the same code as target_obj in original
        case 0x80C1: return make_unique<Opcode80C1Handler>(vm);
        case 0x80C2: return make_unique<Opcode80C2Handler>(vm);
        case 0x80C3: return make_unique<Opcode80C3Handler>(vm);
        case 0x80C4: return make_unique<Opcode80C4Handler>(vm);
        case 0x80C5: return make_unique<Opcode80C5Handler>(vm);
        case 0x80C6: return make_unique<Opcode80C6Handler>(vm);
        case 0x80C7: return make_unique<Opcode80C7Handler>(vm);
        case 0x80C8: return make_unique<Opcode80C8Handler>(vm);
        case 0x80C9: return make_unique<Opcode80C9Handler>(vm);
        case 0x80CA: return make_unique<Opcode80CAHandler>(vm);
        case 0x80CB: return make_unique<Opcode80CBHandler>(vm);
        case 0x80CC: return make_unique<Opcode80CCHandler>(vm);
        case 0x80CE: return make_unique<Opcode80CEHandler>(vm);
        case 0x80CF: return make_unique<Opcode80CFHandler>(vm);
        case 0x80D0: return make_unique<Opcode80D0Handler>(vm);
        case 0x80D2: return make_unique<Opcode80D2Handler>(vm);
        case 0x80D3: return make_unique<Opcode80D3Handler>(vm);
        case 0x80D4: return make_unique<Opcode80D4Handler>(vm);
        case 0x80D5: return make_unique<Opcode80D5Handler>(vm);
        case 0x80D8: return make_unique<Opcode80D8Handler>(vm);
        case 0x80D9: return make_unique<Opcode80D9Handler>(vm);
        case 0x80DA: return make_unique<Opcode80DAHandler>(vm);
        case 0x80DC: return make_unique<Opcode80DCHandler>(vm);
        case 0x80DE: return make_unique<Opcode80DEHandler>(vm);
        case 0x80DF: return make_unique<Opcode80DFHandler>(vm);
        case 0x80E1: return make_unique<Opcode80E1Handler>(vm);
        case 0x80E3: return make_unique<Opcode80E3Handler>(vm);
        case 0x80E4: return make_unique<Opcode80E4Handler>(vm);
        case 0x80E5: return make_unique<Opcode80E5Handler>(vm);
        case 0x80E7: return make_unique<Opcode80E7Handler>(vm);
        case 0x80E8: return make_unique<Opcode80E8Handler>(vm);
        case 0x80E9: return make_unique<Opcode80E9Handler>(vm);
        case 0x80EA: return make_unique<Opcode80EAHandler>(vm);
        case 0x80EC: return make_unique<Opcode80ECHandler>(vm);
        case 0x80EF: return make_unique<Opcode80EFHandler>(vm);
        case 0x80F0: return make_unique<Opcode80F0Handler>(vm);
        case 0x80F1: return make_unique<Opcode80F1Handler>(vm);
        case 0x80F2: return make_unique<Opcode80F2Handler>(vm);
        case 0x80F3: return make_unique<Opcode80F3Handler>(vm);
        case 0x80F4: return make_unique<Opcode80F4Handler>(vm);
        case 0x80F6: return make_unique<Opcode80F6Handler>(vm);
        case 0x80F7: return make_unique<Opcode80F7Handler>(vm);
        case 0x80F9: return make_unique<Opcode80F9Handler>(vm);
        case 0x80FA: return make_unique<Opcode80FAHandler>(vm);
        case 0x80FB: return make_unique<Opcode80FBHandler>(vm);
        case 0x80FC: return make_unique<Opcode80FCHandler>(vm);
        case 0x80FD: return make_unique<Opcode80FDHandler>(vm);
        case 0x80FE: return make_unique<Opcode80FEHandler>(vm);
        case 0x80FF: return make_unique<Opcode80FFHandler>(vm);
        case 0x8100: return make_unique<Opcode8100Handler>(vm);
        case 0x8101: return make_unique<Opcode8101Handler>(vm);
        case 0x8102: return make_unique<Opcode8102Handler>(vm);
        case 0x8105: return make_unique<Opcode8105Handler>(vm);
        case 0x8106: return make_unique<Opcode8106Handler>(vm);
        case 0x8107: return make_unique<Opcode8107Handler>(vm);
        case 0x810A: return make_unique<Opcode810AHandler>(vm);
        case 0x810B: return make_unique<Opcode810BHandler>(vm);
        case 0x810C: return make_unique<Opcode810CHandler>(vm);
        case 0x810D: return make_unique<Opcode810DHandler>(vm);
        case 0x810E: return make_unique<Opcode810EHandler>(vm);
        case 0x810F: return make_unique<Opcode810FHandler>(vm);
        case 0x8113: return make_unique<Opcode8113Handler>(vm);
        case 0x8115: return make_unique<Opcode8115Handler>(vm);
        case 0x8116: return make_unique<Opcode8116Handler>(vm);
        case 0x8117: return make_unique<Opcode8117Handler>(vm);
        case 0x8118: return make_unique<Opcode8118Handler>(vm);
        case 0x8119: return make_unique<Opcode8119Handler>(vm);
        case 0x811C: return make_unique<Opcode811CHandler>(vm);
        case 0x811D: return make_unique<Opcode811DHandler>(vm);
        case 0x811E: return make_unique<Opcode811EHandler>(vm);
        case 0x8120: return make_unique<Opcode8120Handler>(vm);
        case 0x8121: return make_unique<Opcode8121Handler>(vm);
        case 0x8122: return make_unique<Opcode8122Handler>(vm);
        case 0x8123: return make_unique<Opcode8123Handler>(vm);
        case 0x8126: return make_unique<Opcode8126Handler>(vm);
        case 0x8127: return make_unique<Opcode8127Handler>(vm);
        case 0x8128: return make_unique<Opcode8128Handler>(vm);
        case 0x8129: return make_unique<Opcode8129Handler>(vm);
        case 0x812D: return make_unique<Opcode812DHandler>(vm);
        case 0x812E: return make_unique<Opcode812EHandler>(vm);
        case 0x812F: return make_unique<Opcode812FHandler>(vm);
        case 0x8130: return make_unique<Opcode8130Handler>(vm);
        case 0x8131: return make_unique<Opcode8131Handler>(vm);
        case 0x8132: return make_unique<Opcode8132Handler>(vm);
        case 0x8134: return make_unique<Opcode8134Handler>(vm);
        case 0x8136: return make_unique<Opcode8136Handler>(vm);
        case 0x8137: return make_unique<Opcode8137Handler>(vm);
        case 0x8138: return make_unique<Opcode8138Handler>(vm);
        case 0x8139: return make_unique<Opcode8139Handler>(vm);
        case 0x813C: return make_unique<Opcode813CHandler>(vm);
        case 0x8143: return make_unique<Opcode8143Handler>(vm);
        case 0x8145: return make_unique<Opcode8145Handler>(vm);
        case 0x8147: return make_unique<Opcode8147Handler>(vm);
        case 0x8149: return make_unique<Opcode8149Handler>(vm);
        case 0x814B: return make_unique<Opcode814BHandler>(vm);
        case 0x814C: return make_unique<Opcode814CHandler>(vm);
        case 0x814E: return make_unique<Opcode814EHandler>(vm);
        case 0x8150: return make_unique<Opcode8150Handler>(vm);
        case 0x8151: return make_unique<Opcode8151Handler>(vm);
        case 0x8152: return make_unique<Opcode8152Handler>(vm);
        case 0x8153: return make_unique<Opcode8153Handler>(vm);
        case 0x8154: return make_unique<Opcode8154Handler>(vm);
        case 0x9001: return make_unique<Opcode9001Handler>(vm);
        case 0xC001: return make_unique<OpcodeC001Handler>(vm);
        case 0xA001: return make_unique<OpcodeA001Handler>(vm);
        default:
        {
            std::stringstream ss;
            ss << "OpcodeFactory::createOpcode() - unimplemented opcode: " << std::hex << number;
            throw Exception(ss.str());
        }
    }
}

}
