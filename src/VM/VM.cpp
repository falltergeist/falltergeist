/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <iostream>

// Falltergeist includes
#include "../Engine/ResourceManager.h"
#include "../Engine/Exception.h"
#include "../VM/VM.h"
#include "../VM/VMStackIntValue.h"

// Third party includes

namespace Falltergeist
{

VM::VM(libfalltergeist::IntFileType* script)
{
    _script = script;
}

VM::VM(std::string filename)
{
    _script = ResourceManager::intFileType(filename);
}

VM::~VM()
{
}


void VM::call(std::string name)
{
    std::cout << std::endl << "CALLED: " << name << std::endl;
    _programCounter = _script->function(name);
    run();
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;
    run();
}

void VM::run()
{
    unsigned short opcode;
    VMStackValue* stackValue;
    VMStackIntValue* stackIntValue;

    while (_programCounter != _script->size())
    {
        _script->setPosition(_programCounter);

        *_script >> opcode;
        std::cout << "0x" << std::hex << _programCounter << " > ";
        switch (opcode)
        {
            case 0xC001:
                _programCounter += 6;
                break;
            default:
                _programCounter += 2;
                break;
        }
        switch (opcode)
        {
            case 0x8002:
                std::cout << "lock" << std::endl;
                break;
            case 0x8003:
                std::cout << "unlock" << std::endl;
                break;
            case 0x8004:
                stackValue = _dataStack.pop();
                if (stackValue->type() == VMStackValue::TYPE_INTEGER)
                {
                    stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
                    _programCounter = stackIntValue->value();
                }
                else
                {
                    throw Exception("VM::opcode[8004] - stack value is not integer");
                }
                std::cout << "[*] pop_d => jmp" << std::endl;
                break;
            case 0x8005:
                std::cout << "call" << std::endl;
                break;
            case 0x800c:
                std::cout << "[*] pop_r => push_d" << std::endl;
                _dataStack.push(_returnStack.pop());
                break;
            case 0x800d:
                std::cout << "[*] pop_d => push_r" << std::endl;
                _returnStack.push(_dataStack.pop());
                break;
            case 0x8010:
                std::cout << "[*] strtdone" << std::endl;
                _initialized = true;
                return;
                break;
            case 0x8012:
                std::cout << "pop_d number; value = SVAR[number]; push_d value;" << std::endl;
                break;
            case 0x8013:
                std::cout << "pop_d number, pop_d value, SVAR[num] = value" << std::endl;
                break;
            case 0x8016:
                std::cout << "exportv" << std::endl;
                break;
            case 0x8017:
                std::cout << "exportp`" << std::endl;
                break;
            case 0x8018:
                std::cout << "[*] dswap" << std::endl;
                _dataStack.swap();
                break;
            case 0x8019:
                std::cout << "[*] rswap" << std::endl;
                _returnStack.swap();
                break;
            case 0x801a:
                std::cout << "[*] pop_d and discard" << std::endl;
                _dataStack.pop();
                break;
            case 0x801c:
                std::cout << "[*] restpc - pop_r => $pc" << std::endl;
                stackValue = _returnStack.pop();
                if (stackValue->type() == VMStackValue::TYPE_INTEGER)
                {
                    stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
                    _programCounter = stackIntValue->value();
                }
                else
                {
                    throw Exception("VM::opcode[801c] - stack value is not integer");
                }
                break;
            case 0x8029:
                std::cout << "[*] popbase - pop_r => $lvar_base" << std::endl;
                stackValue = _returnStack.pop();
                if (stackValue->type() == VMStackValue::TYPE_INTEGER)
                {
                    stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
                    _localVarBase = stackIntValue->value();
                }
                else
                {
                    throw Exception("VM::opcode[8029] - stack value is not integer");
                }
                break;
            case 0x802a:
                std::cout << "[*] clrargs - pop_d while $dstack.size() != $lvar_base" << std::endl;
                while (_dataStack.size() != _localVarBase) _dataStack.pop();
                break;
            case 0x802b:
                std::cout << "[*] push_r $lvar_base" << std::endl;
                std::cout << "$lvar_base = " << std::dec << _localVarBase << std::endl;
                _returnStack.push(new VMStackIntValue(_localVarBase));
                break;
            case 0x802c:
                std::cout << "[*] $dstack.size() => $svar_base" << std::endl;
                std::cout << "$dstack.size() = " << std::dec << _dataStack.size() << std::endl;
                _scriptVarsBase = _dataStack.size();
                break;
            case 0x802f:
            {
                std::cout << "[*] ifthen (pop_d condition_value, pop_d address) if (condition == 0) jmp address" << std::endl;
                auto condition = _popDataInteger();
                auto address = _popDataInteger();
                if (condition == 0)
                {
                    std::cout  << "condition == 0" << std::endl;
                    _programCounter = address;
                }
                else
                {
                    std::cout  << "condition != 0" << std::endl;
                }
                break;
            }
            case 0x8031:
                std::cout << "LVAR[num] = value" << std::endl;
                break;
            case 0x8032:
                std::cout << "stack = LVAR[num]" << std::endl;
                break;
            case 0x8033:
                std::cout << "eq (pop_d a, pop_d b)  a == b ? push_d 1 : push_d 0" << std::endl;
                break;
            case 0x8034:
                std::cout << "neq !=" << std::endl;
                break;
            case 0x8035:
                std::cout << "leq <=" << std::endl;
                break;
            case 0x8036:
                std::cout << "geq >=" << std::endl;
                break;
            case 0x8037:
                std::cout << "lt <" << std::endl;
                break;
            case 0x8038:
                std::cout << "gt >" << std::endl;
                break;
            case 0x8039:
                std::cout << "plus +" << std::endl;
                break;
            case 0x803a:
                std::cout << "minus -" << std::endl;
                break;
            case 0x803b:
                std::cout << "mult *" << std::endl;
                break;
            case 0x803c:
                std::cout << "div /" << std::endl;
                break;
            case 0x803d:
                std::cout << "mod %" << std::endl;
                break;
            case 0x803e:
                std::cout << "AND" << std::endl;
                break;
            case 0x803f:
                std::cout << "OR" << std::endl;
                break;
            case 0x8045:
                std::cout << "stack:=NOT(p1) - logical not" << std::endl;
                break;
            case 0x8046:
                std::cout << " - value (change sign)" << std::endl;
                break;
            case 0x80a9:
                std::cout << "void override_map_start(int x, int y, int elev, int rot)" << std::endl;
                break;
            case 0x80b4:
                std::cout << "pop_max, pop_min, value = rand (min, max), push_d value;" << std::endl;
                break;
            case 0x80b6:
                std::cout << "int move_to(ObjectPtr obj, int tile_num, int elev)" << std::endl;
                break;
            case 0x80b7:
                std::cout << "ObjectPtr create_object_sid(int pid, int tile_num, int elev, int sid)" << std::endl;
                break;
            case 0x80b8:
                std::cout << "pop_d pointer; display_msg(pointer) " << std::endl;
                break;
            case 0x80b9:
                std::cout << "script_overrides" << std::endl;
                break;
            case 0x80bc:
                std::cout << "stack:=self_obj" << std::endl;
                break;
            case 0x80bd:
                std::cout << "stack:=source_obj" << std::endl;
                break;
            case 0x80bf:
                std::cout << "stack:=dude_obj" << std::endl;
                break;
            case 0x80c1:
                std::cout << "value = local_var(index) " << std::endl;
                break;
            case 0x80c2:
                std::cout << "set_local_var(index, value)" << std::endl;
                break;
            case 0x80c6:
                std::cout << "void set_global_var(unsigned int var_index, int value)" << std::endl;
                break;
            case 0x80c7:
                std::cout << "int script_action()" << std::endl;
                break;
            case 0x80c8:
                std::cout << "stack:=obj_type(p1)" << std::endl;
                break;
            case 0x80ca:
                std::cout << "int get_critter_stat(ObjectPtr who, int stat)" << std::endl;
                break;
            case 0x80d3:
                std::cout << "stack:=tile_distance_objs(p2,p1)" << std::endl;
                break;
            case 0x80e5:
                std::cout << "wm_area_set_pos(p3,p2,p1)" << std::endl;
                break;
            case 0x80e9:
                std::cout << "void set_light_level(int level)" << std::endl;
                break;
            case 0x80ef:
                std::cout << "void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)" << std::endl;
                break;
            case 0x80f6:
                std::cout << "int game_time_hour" << std::endl;
                break;
            case 0x8105:
                std::cout << "pop_d num, pop_d list, char* pointer = message_str(int msg_list, int msg_num); push_d pointer;" << std::endl;
                break;
            case 0x810b:
            {
                std::cout << "[*] stack:=metarule(p2,p1)" << std::endl;
                auto p1 = _popDataInteger();
                auto p2 = _popDataInteger();
                _pushDataInteger(_metarule(p2, p1));
                break;
            }
            case 0x8116:
                std::cout << "void add_mult_objs_to_inven(ObjectPtr who, ObjectPtr item, int count)" << std::endl;
                break;
            case 0x8118:
                std::cout << "int get_month" << std::endl;
                break;
            case 0x814b:
                std::cout << "ObjectPtr party_member_obj(int pid)" << std::endl;
                break;

            case 0xC001:
                unsigned int value;
                *_script >> value;
                _dataStack.push(new VMStackIntValue(value));
                std::cout << "[*] push_d 0x" << std::hex << value << std::endl;
                break;
            default:
                std::cout << "0x" << std::hex << opcode << std::endl;
                break;
        }

    }
}

int VM::_popDataInteger()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        return stackIntValue->value();
    }
    throw Exception("VM::_popDataInteger() - stack value is not integer");
}

void VM::_pushDataInteger(int value)
{
    _dataStack.push(new VMStackIntValue(value));
}

int VM::_metarule(int type, int value)
{
    std::cout  << "Metarule: " << std::to_string(type) << " : " << std::to_string(value) << std::endl;
    switch(type)
    {
        case 14: // METARULE_TEST_FIRSTRUN
            // Если карта открывается в первый раз, то возвращает TRUE;
            return 1;
    }
    throw Exception("VM::_metarule() - unknown type: " + std::to_string(type));
}

}




