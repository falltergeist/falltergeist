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
#include "../VM/OpcodeFactory.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Exception.h"
#include "../VM/Handler/Opcode8002.h"
#include "../VM/Handler/Opcode8003.h"
#include "../VM/Handler/Opcode8004.h"
#include "../VM/Handler/Opcode8005.h"
#include "../VM/Handler/Opcode800CHandler.h"
#include "../VM/Handler/Opcode800DHandler.h"
#include "../VM/Handler/Opcode8010Handler.h"
#include "../VM/Handler/Opcode8012Handler.h"
#include "../VM/Handler/Opcode8013Handler.h"
#include "../VM/Handler/Opcode8014Handler.h"
#include "../VM/Handler/Opcode8015Handler.h"
#include "../VM/Handler/Opcode8016Handler.h"
#include "../VM/Handler/Opcode8018Handler.h"
#include "../VM/Handler/Opcode8019Handler.h"
#include "../VM/Handler/Opcode801AHandler.h"
#include "../VM/Handler/Opcode801BHandler.h"
#include "../VM/Handler/Opcode801CHandler.h"
#include "../VM/Handler/Opcode8027Handler.h"
#include "../VM/Handler/Opcode8028Handler.h"
#include "../VM/Handler/Opcode8029Handler.h"
#include "../VM/Handler/Opcode802AHandler.h"
#include "../VM/Handler/Opcode802BHandler.h"
#include "../VM/Handler/Opcode802CHandler.h"
#include "../VM/Handler/Opcode802FHandler.h"
#include "../VM/Handler/Opcode8030Handler.h"
#include "../VM/Handler/Opcode8031Handler.h"
#include "../VM/Handler/Opcode8032Handler.h"
#include "../VM/Handler/OpcodeComparisonHandler.h"
#include "../VM/Handler/Opcode8039Handler.h"
#include "../VM/Handler/Opcode803AHandler.h"
#include "../VM/Handler/Opcode803BHandler.h"
#include "../VM/Handler/Opcode803CHandler.h"
#include "../VM/Handler/Opcode803DHandler.h"
#include "../VM/Handler/Opcode803EHandler.h"
#include "../VM/Handler/Opcode803FHandler.h"
#include "../VM/Handler/Opcode8040Handler.h"
#include "../VM/Handler/Opcode8041Handler.h"
#include "../VM/Handler/Opcode8042Handler.h"
#include "../VM/Handler/Opcode8043Handler.h"
#include "../VM/Handler/Opcode8044Handler.h"
#include "../VM/Handler/Opcode8045Handler.h"
#include "../VM/Handler/Opcode8046Handler.h"
#include "../VM/Handler/Opcode80A1Handler.h"
#include "../VM/Handler/Opcode80A3Handler.h"
#include "../VM/Handler/Opcode80A4Handler.h"
#include "../VM/Handler/Opcode80A6Handler.h"
#include "../VM/Handler/Opcode80A7Handler.h"
#include "../VM/Handler/Opcode80A8Handler.h"
#include "../VM/Handler/Opcode80A9Handler.h"
#include "../VM/Handler/Opcode80AAHandler.h"
#include "../VM/Handler/Opcode80ABHandler.h"
#include "../VM/Handler/Opcode80ACHandler.h"
#include "../VM/Handler/Opcode80AEHandler.h"
#include "../VM/Handler/Opcode80AFHandler.h"
#include "../VM/Handler/Opcode80B0Handler.h"
#include "../VM/Handler/Opcode80B2Handler.h"
#include "../VM/Handler/Opcode80B4Handler.h"
#include "../VM/Handler/Opcode80B6Handler.h"
#include "../VM/Handler/Opcode80B7Handler.h"
#include "../VM/Handler/Opcode80B8Handler.h"
#include "../VM/Handler/Opcode80B9Handler.h"
#include "../VM/Handler/Opcode80BAHandler.h"
#include "../VM/Handler/Opcode80BBHandler.h"
#include "../VM/Handler/Opcode80BCHandler.h"
#include "../VM/Handler/Opcode80BDHandler.h"
#include "../VM/Handler/Opcode80BEHandler.h"
#include "../VM/Handler/Opcode80BFHandler.h"
#include "../VM/Handler/Opcode80C1Handler.h"
#include "../VM/Handler/Opcode80C2Handler.h"
#include "../VM/Handler/Opcode80C3Handler.h"
#include "../VM/Handler/Opcode80C4Handler.h"
#include "../VM/Handler/Opcode80C5Handler.h"
#include "../VM/Handler/Opcode80C6Handler.h"
#include "../VM/Handler/Opcode80C7Handler.h"
#include "../VM/Handler/Opcode80C8Handler.h"
#include "../VM/Handler/Opcode80C9Handler.h"
#include "../VM/Handler/Opcode80CAHandler.h"
#include "../VM/Handler/Opcode80CBHandler.h"
#include "../VM/Handler/Opcode80CCHandler.h"
#include "../VM/Handler/Opcode80CEHandler.h"
#include "../VM/Handler/Opcode80CFHandler.h"
#include "../VM/Handler/Opcode80D0Handler.h"
#include "../VM/Handler/Opcode80D2Handler.h"
#include "../VM/Handler/Opcode80D3Handler.h"
#include "../VM/Handler/Opcode80D4Handler.h"
#include "../VM/Handler/Opcode80D5Handler.h"
#include "../VM/Handler/Opcode80D8Handler.h"
#include "../VM/Handler/Opcode80D9Handler.h"
#include "../VM/Handler/Opcode80DAHandler.h"
#include "../VM/Handler/Opcode80DCHandler.h"
#include "../VM/Handler/Opcode80DEHandler.h"
#include "../VM/Handler/Opcode80DFHandler.h"
#include "../VM/Handler/Opcode80E1Handler.h"
#include "../VM/Handler/Opcode80E3Handler.h"
#include "../VM/Handler/Opcode80E4Handler.h"
#include "../VM/Handler/Opcode80E5Handler.h"
#include "../VM/Handler/Opcode80E7Handler.h"
#include "../VM/Handler/Opcode80E8Handler.h"
#include "../VM/Handler/Opcode80E9Handler.h"
#include "../VM/Handler/Opcode80EAHandler.h"
#include "../VM/Handler/Opcode80ECHandler.h"
#include "../VM/Handler/Opcode80EFHandler.h"
#include "../VM/Handler/Opcode80F0Handler.h"
#include "../VM/Handler/Opcode80F1Handler.h"
#include "../VM/Handler/Opcode80F2Handler.h"
#include "../VM/Handler/Opcode80F3Handler.h"
#include "../VM/Handler/Opcode80F4Handler.h"
#include "../VM/Handler/Opcode80F6Handler.h"
#include "../VM/Handler/Opcode80F7Handler.h"
#include "../VM/Handler/Opcode80F8Handler.h"
#include "../VM/Handler/Opcode80F9Handler.h"
#include "../VM/Handler/Opcode80FAHandler.h"
#include "../VM/Handler/Opcode80FBHandler.h"
#include "../VM/Handler/Opcode80FCHandler.h"
#include "../VM/Handler/Opcode80FDHandler.h"
#include "../VM/Handler/Opcode80FEHandler.h"
#include "../VM/Handler/Opcode80FFHandler.h"
#include "../VM/Handler/Opcode8100Handler.h"
#include "../VM/Handler/Opcode8101Handler.h"
#include "../VM/Handler/Opcode8102Handler.h"
#include "../VM/Handler/Opcode8105Handler.h"
#include "../VM/Handler/Opcode8106Handler.h"
#include "../VM/Handler/Opcode8107Handler.h"
#include "../VM/Handler/Opcode810AHandler.h"
#include "../VM/Handler/Opcode810BHandler.h"
#include "../VM/Handler/Opcode810CHandler.h"
#include "../VM/Handler/Opcode810DHandler.h"
#include "../VM/Handler/Opcode810EHandler.h"
#include "../VM/Handler/Opcode810FHandler.h"
#include "../VM/Handler/Opcode8113Handler.h"
#include "../VM/Handler/Opcode8115Handler.h"
#include "../VM/Handler/Opcode8116Handler.h"
#include "../VM/Handler/Opcode8117Handler.h"
#include "../VM/Handler/Opcode8118Handler.h"
#include "../VM/Handler/Opcode8119Handler.h"
#include "../VM/Handler/Opcode811CHandler.h"
#include "../VM/Handler/Opcode811DHandler.h"
#include "../VM/Handler/Opcode811EHandler.h"
#include "../VM/Handler/Opcode8120Handler.h"
#include "../VM/Handler/Opcode8121Handler.h"
#include "../VM/Handler/Opcode8122Handler.h"
#include "../VM/Handler/Opcode8123Handler.h"
#include "../VM/Handler/Opcode8126Handler.h"
#include "../VM/Handler/Opcode8127Handler.h"
#include "../VM/Handler/Opcode8128Handler.h"
#include "../VM/Handler/Opcode8129Handler.h"
#include "../VM/Handler/Opcode812DHandler.h"
#include "../VM/Handler/Opcode812EHandler.h"
#include "../VM/Handler/Opcode812FHandler.h"
#include "../VM/Handler/Opcode8130Handler.h"
#include "../VM/Handler/Opcode8131Handler.h"
#include "../VM/Handler/Opcode8132Handler.h"
#include "../VM/Handler/Opcode8133Handler.h"
#include "../VM/Handler/Opcode8134Handler.h"
#include "../VM/Handler/Opcode8136Handler.h"
#include "../VM/Handler/Opcode8137Handler.h"
#include "../VM/Handler/Opcode8138Handler.h"
#include "../VM/Handler/Opcode8139Handler.h"
#include "../VM/Handler/Opcode813CHandler.h"
#include "../VM/Handler/Opcode8143Handler.h"
#include "../VM/Handler/Opcode8145Handler.h"
#include "../VM/Handler/Opcode8147Handler.h"
#include "../VM/Handler/Opcode8149Handler.h"
#include "../VM/Handler/Opcode814AHandler.h"
#include "../VM/Handler/Opcode814BHandler.h"
#include "../VM/Handler/Opcode814CHandler.h"
#include "../VM/Handler/Opcode814EHandler.h"
#include "../VM/Handler/Opcode8150Handler.h"
#include "../VM/Handler/Opcode8151Handler.h"
#include "../VM/Handler/Opcode8152Handler.h"
#include "../VM/Handler/Opcode8153Handler.h"
#include "../VM/Handler/Opcode8154Handler.h"
#include "../VM/Handler/Opcode9001Handler.h"
#include "../VM/Handler/OpcodeC001Handler.h"
#include "../VM/Handler/OpcodeA001Handler.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        using Base::make_unique;
        std::unique_ptr<OpcodeHandler> OpcodeFactory::createOpcode(unsigned int number, VM::Script* script)
        {
            switch (number)
            {
                case 0x8000: return make_unique<OpcodeHandler>(script); // O_NOOP
                case 0x8002: return make_unique<Handler::Opcode8002>(script);
                case 0x8003: return make_unique<Handler::Opcode8003>(script);
                case 0x8004: return make_unique<Handler::Opcode8004>(script);
                case 0x8005: return make_unique<Handler::Opcode8005>(script);
                case 0x800C: return make_unique<Handler::Opcode800C>(script);
                case 0x800D: return make_unique<Handler::Opcode800D>(script);
                case 0x8010: return make_unique<Handler::Opcode8010>(script);
                case 0x8012: return make_unique<Handler::Opcode8012>(script);
                case 0x8013: return make_unique<Handler::Opcode8013>(script);
                case 0x8014: return make_unique<Handler::Opcode8014>(script);
                case 0x8015: return make_unique<Handler::Opcode8015>(script);
                case 0x8016: return make_unique<Handler::Opcode8016>(script);
                case 0x8018: return make_unique<Handler::Opcode8018>(script);
                case 0x8019: return make_unique<Handler::Opcode8019>(script);
                case 0x801A: return make_unique<Handler::Opcode801A>(script);
                case 0x801B: return make_unique<Handler::Opcode801B>(script);
                case 0x801C: return make_unique<Handler::Opcode801C>(script);
                case 0x8027: return make_unique<Handler::Opcode8027>(script);
                case 0x8028: return make_unique<Handler::Opcode8028>(script);
                case 0x8029: return make_unique<Handler::Opcode8029>(script);
                case 0x802A: return make_unique<Handler::Opcode802A>(script);
                case 0x802B: return make_unique<Handler::Opcode802B>(script);
                case 0x802C: return make_unique<Handler::Opcode802C>(script);
                case 0x802F: return make_unique<Handler::Opcode802F>(script);
                case 0x8030: return make_unique<Handler::Opcode8030>(script);
                case 0x8031: return make_unique<Handler::Opcode8031>(script);
                case 0x8032: return make_unique<Handler::Opcode8032>(script);
                case 0x8033: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::EQUAL);
                case 0x8034: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::NOT_EQUAL);
                case 0x8035: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::LESS_EQUAL);
                case 0x8036: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::GREATER_EQUAL);
                case 0x8037: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::LESS);
                case 0x8038: return make_unique<Handler::OpcodeComparison>(script, Handler::OpcodeComparison::Type::GREATER);
                case 0x8039: return make_unique<Handler::Opcode8039>(script);
                case 0x803A: return make_unique<Handler::Opcode803A>(script);
                case 0x803B: return make_unique<Handler::Opcode803B>(script);
                case 0x803C: return make_unique<Handler::Opcode803C>(script);
                case 0x803D: return make_unique<Handler::Opcode803D>(script);
                case 0x803E: return make_unique<Handler::Opcode803E>(script);
                case 0x803F: return make_unique<Handler::Opcode803F>(script);
                case 0x8040: return make_unique<Handler::Opcode8040>(script);
                case 0x8041: return make_unique<Handler::Opcode8041>(script);
                case 0x8042: return make_unique<Handler::Opcode8042>(script); // bwxor
                case 0x8043: return make_unique<Handler::Opcode8043>(script); // bwnot
                case 0x8044: return make_unique<Handler::Opcode8044>(script);
                case 0x8045: return make_unique<Handler::Opcode8045>(script);
                case 0x8046: return make_unique<Handler::Opcode8046>(script);
                case 0x80A1: return make_unique<Handler::Opcode80A1>(script);
                case 0x80A3: return make_unique<Handler::Opcode80A3>(script);
                case 0x80A4: return make_unique<Handler::Opcode80A4>(script);
                case 0x80A6: return make_unique<Handler::Opcode80A6>(script);
                case 0x80A7: return make_unique<Handler::Opcode80A7>(script);
                case 0x80A8: return make_unique<Handler::Opcode80A8>(script);
                case 0x80A9: return make_unique<Handler::Opcode80A9>(script);
                case 0x80AA: return make_unique<Handler::Opcode80AA>(script);
                case 0x80AB: return make_unique<Handler::Opcode80AB>(script);
                case 0x80AC: return make_unique<Handler::Opcode80AC>(script);
                case 0x80AE: return make_unique<Handler::Opcode80AE>(script);
                case 0x80AF: return make_unique<Handler::Opcode80AF>(script);
                case 0x80B0: return make_unique<Handler::Opcode80B0>(script);
                case 0x80B2: return make_unique<Handler::Opcode80B2>(script);
                case 0x80B4: return make_unique<Handler::Opcode80B4>(script);
                case 0x80B6: return make_unique<Handler::Opcode80B6>(script);
                case 0x80B7: return make_unique<Handler::Opcode80B7>(script);
                case 0x80B8: return make_unique<Handler::Opcode80B8>(script);
                case 0x80B9: return make_unique<Handler::Opcode80B9>(script);
                case 0x80BA: return make_unique<Handler::Opcode80BA>(script);
                case 0x80BB: return make_unique<Handler::Opcode80BB>(script);
                case 0x80BC: return make_unique<Handler::Opcode80BC>(script); // self_obj
                case 0x80BD: return make_unique<Handler::Opcode80BD>(script); // source_obj
                case 0x80BE: return make_unique<Handler::Opcode80BE>(script); // target_obj
                case 0x80BF: return make_unique<Handler::Opcode80BF>(script); // dude_obj
                case 0x80C0: return make_unique<Handler::Opcode80BE>(script); // obj_being_used_with - uses the same code as target_obj in original
                case 0x80C1: return make_unique<Handler::Opcode80C1>(script);
                case 0x80C2: return make_unique<Handler::Opcode80C2>(script);
                case 0x80C3: return make_unique<Handler::Opcode80C3>(script);
                case 0x80C4: return make_unique<Handler::Opcode80C4>(script);
                case 0x80C5: return make_unique<Handler::Opcode80C5>(script);
                case 0x80C6: return make_unique<Handler::Opcode80C6>(script);
                case 0x80C7: return make_unique<Handler::Opcode80C7>(script);
                case 0x80C8: return make_unique<Handler::Opcode80C8>(script);
                case 0x80C9: return make_unique<Handler::Opcode80C9>(script);
                case 0x80CA: return make_unique<Handler::Opcode80CA>(script);
                case 0x80CB: return make_unique<Handler::Opcode80CB>(script);
                case 0x80CC: return make_unique<Handler::Opcode80CC>(script);
                case 0x80CE: return make_unique<Handler::Opcode80CE>(script);
                case 0x80CF: return make_unique<Handler::Opcode80CF>(script);
                case 0x80D0: return make_unique<Handler::Opcode80D0>(script);
                case 0x80D2: return make_unique<Handler::Opcode80D2>(script);
                case 0x80D3: return make_unique<Handler::Opcode80D3>(script);
                case 0x80D4: return make_unique<Handler::Opcode80D4>(script);
                case 0x80D5: return make_unique<Handler::Opcode80D5>(script);
                case 0x80D8: return make_unique<Handler::Opcode80D8>(script);
                case 0x80D9: return make_unique<Handler::Opcode80D9>(script);
                case 0x80DA: return make_unique<Handler::Opcode80DA>(script);
                case 0x80DC: return make_unique<Handler::Opcode80DC>(script);
                case 0x80DE: return make_unique<Handler::Opcode80DE>(script);
                case 0x80DF: return make_unique<Handler::Opcode80DF>(script);
                case 0x80E1: return make_unique<Handler::Opcode80E1>(script);
                case 0x80E3: return make_unique<Handler::Opcode80E3>(script);
                case 0x80E4: return make_unique<Handler::Opcode80E4>(script);
                case 0x80E5: return make_unique<Handler::Opcode80E5>(script);
                case 0x80E7: return make_unique<Handler::Opcode80E7>(script);
                case 0x80E8: return make_unique<Handler::Opcode80E8>(script);
                case 0x80E9: return make_unique<Handler::Opcode80E9>(script);
                case 0x80EA: return make_unique<Handler::Opcode80EA>(script);
                case 0x80EC: return make_unique<Handler::Opcode80EC>(script);
                case 0x80EF: return make_unique<Handler::Opcode80EF>(script);
                case 0x80F0: return make_unique<Handler::Opcode80F0>(script);
                case 0x80F1: return make_unique<Handler::Opcode80F1>(script);
                case 0x80F2: return make_unique<Handler::Opcode80F2>(script);
                case 0x80F3: return make_unique<Handler::Opcode80F3>(script);
                case 0x80F4: return make_unique<Handler::Opcode80F4>(script);
                case 0x80F6: return make_unique<Handler::Opcode80F6>(script);
                case 0x80F7: return make_unique<Handler::Opcode80F7>(script);
                case 0x80F8: return make_unique<Handler::Opcode80F8>(script);
                case 0x80F9: return make_unique<Handler::Opcode80F9>(script);
                case 0x80FA: return make_unique<Handler::Opcode80FA>(script);
                case 0x80FB: return make_unique<Handler::Opcode80FB>(script);
                case 0x80FC: return make_unique<Handler::Opcode80FC>(script);
                case 0x80FD: return make_unique<Handler::Opcode80FD>(script);
                case 0x80FE: return make_unique<Handler::Opcode80FE>(script);
                case 0x80FF: return make_unique<Handler::Opcode80FF>(script);
                case 0x8100: return make_unique<Handler::Opcode8100>(script);
                case 0x8101: return make_unique<Handler::Opcode8101>(script);
                case 0x8102: return make_unique<Handler::Opcode8102>(script);
                case 0x8105: return make_unique<Handler::Opcode8105>(script);
                case 0x8106: return make_unique<Handler::Opcode8106>(script);
                case 0x8107: return make_unique<Handler::Opcode8107>(script);
                case 0x810A: return make_unique<Handler::Opcode810A>(script);
                case 0x810B: return make_unique<Handler::Opcode810B>(script);
                case 0x810C: return make_unique<Handler::Opcode810C>(script);
                case 0x810D: return make_unique<Handler::Opcode810D>(script);
                case 0x810E: return make_unique<Handler::Opcode810E>(script);
                case 0x810F: return make_unique<Handler::Opcode810F>(script);
                case 0x8113: return make_unique<Handler::Opcode8113>(script);
                case 0x8115: return make_unique<Handler::Opcode8115>(script);
                case 0x8116: return make_unique<Handler::Opcode8116>(script);
                case 0x8117: return make_unique<Handler::Opcode8117>(script);
                case 0x8118: return make_unique<Handler::Opcode8118>(script);
                case 0x8119: return make_unique<Handler::Opcode8119>(script);
                case 0x811C: return make_unique<Handler::Opcode811C>(script);
                case 0x811D: return make_unique<Handler::Opcode811D>(script);
                case 0x811E: return make_unique<Handler::Opcode811E>(script);
                case 0x8120: return make_unique<Handler::Opcode8120>(script);
                case 0x8121: return make_unique<Handler::Opcode8121>(script);
                case 0x8122: return make_unique<Handler::Opcode8122>(script);
                case 0x8123: return make_unique<Handler::Opcode8123>(script);
                case 0x8126: return make_unique<Handler::Opcode8126>(script);
                case 0x8127: return make_unique<Handler::Opcode8127>(script);
                case 0x8128: return make_unique<Handler::Opcode8128>(script);
                case 0x8129: return make_unique<Handler::Opcode8129>(script);
                case 0x812D: return make_unique<Handler::Opcode812D>(script);
                case 0x812E: return make_unique<Handler::Opcode812E>(script);
                case 0x812F: return make_unique<Handler::Opcode812F>(script);
                case 0x8130: return make_unique<Handler::Opcode8130>(script);
                case 0x8131: return make_unique<Handler::Opcode8131>(script);
                case 0x8132: return make_unique<Handler::Opcode8132>(script);
                case 0x8133: return make_unique<Handler::Opcode8133>(script);
                case 0x8134: return make_unique<Handler::Opcode8134>(script);
                case 0x8136: return make_unique<Handler::Opcode8136>(script);
                case 0x8137: return make_unique<Handler::Opcode8137>(script);
                case 0x8138: return make_unique<Handler::Opcode8138>(script);
                case 0x8139: return make_unique<Handler::Opcode8139>(script);
                case 0x813C: return make_unique<Handler::Opcode813C>(script);
                case 0x8143: return make_unique<Handler::Opcode8143>(script);
                case 0x8145: return make_unique<Handler::Opcode8145>(script);
                case 0x8147: return make_unique<Handler::Opcode8147>(script);
                case 0x8149: return make_unique<Handler::Opcode8149>(script);
                case 0x814A: return make_unique<Handler::Opcode814A>(script);
                case 0x814B: return make_unique<Handler::Opcode814B>(script);
                case 0x814C: return make_unique<Handler::Opcode814C>(script);
                case 0x814E: return make_unique<Handler::Opcode814E>(script);
                case 0x8150: return make_unique<Handler::Opcode8150>(script);
                case 0x8151: return make_unique<Handler::Opcode8151>(script);
                case 0x8152: return make_unique<Handler::Opcode8152>(script);
                case 0x8153: return make_unique<Handler::Opcode8153>(script);
                case 0x8154: return make_unique<Handler::Opcode8154>(script);
                case 0x9001: return make_unique<Handler::Opcode9001>(script);
                case 0xC001: return make_unique<Handler::OpcodeC001>(script);
                case 0xA001: return make_unique<Handler::OpcodeA001>(script);
                default:
                {
                    std::stringstream ss;
                    ss << "OpcodeFactory::createOpcode() - unimplemented opcode: " << std::hex << number;
                    throw Exception(ss.str());
                }
            }
        }
    }
}
