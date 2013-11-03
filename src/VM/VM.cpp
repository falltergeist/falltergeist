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
#include "../Engine/Game.h"
#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
#include "../VM/VM.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"

// Third party includes

namespace Falltergeist
{

VM::VM(libfalltergeist::IntFileType* script)
{
    _game = &Game::getInstance();
    _script = script;
}

VM::VM(std::string filename)
{
    _game = &Game::getInstance();
    _script = ResourceManager::intFileType(filename);
}

VM::~VM()
{
}


void VM::call(std::string name)
{
    try
    {
        _programCounter = _script->function(name);
        _pushReturnInteger(0);
        std::cout << std::endl << "CALLED: " << name << std::endl;
        run();
        std::cout << "Function ended" << std::endl;
    }
    catch (libfalltergeist::Exception &e)
    {
        std::cout << "Function not exist: " << name << std::endl;
    }
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;
    run();
}

void VM::run()
{
    while (_programCounter != _script->size())
    {
        if (_programCounter == 0 && _initialized) return;

        _script->setPosition(_programCounter);
        unsigned short opcode;
        *_script >> opcode;
        std::cout << "0x" << std::hex << _programCounter << " [" << opcode << "] ";
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
                std::cout << "[*] void jmp(int addr)" << std::endl;
                _programCounter = _popDataInteger();
                break;
            case 0x8005:
            {
                std::cout << "[?] call" << std::endl;
                auto functionIndex = _popDataInteger();
                auto paramsNumber = _popDataInteger();
                if (paramsNumber != 0)
                {
                    throw Exception("Call Op - params number != 0");
                }
                _pushReturnInteger(_programCounter);
                _programCounter = _script->function(functionIndex);

                std::cout << "Calling: " << std::hex << _programCounter << std::endl;
                break;
            }
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
            {
                std::cout << "[*] value = SVAR[number];" << std::endl;
                auto number = _popDataInteger();
                _dataStack.push(_dataStack.values()->at(_SVAR_base + number));
                break;
            }
            case 0x8013:
            {
                std::cout << "[*] SVAR[num] = value" << std::endl;
                auto number = _popDataInteger();
                auto value = _dataStack.pop();
                _dataStack.values()->at(_SVAR_base + number) = value;
                break;
            }
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
                _programCounter = _popReturnInteger();
                break;
            case 0x8029:
                std::cout << "[*] DVAR restore" << std::endl;
                _DVAR_base = _popReturnInteger();
                break;
            case 0x802a:
                std::cout << "[*] clrargs" << std::endl;
                while (_dataStack.size() != _DVAR_base)
                {
                    _dataStack.pop();
                }
                break;
            case 0x802b:
                std::cout << "[*] set DVAR base = ";
                _pushReturnInteger(_DVAR_base);
                _DVAR_base = _dataStack.size();
                std::cout << _DVAR_base << std::endl;
                break;
            case 0x802c:
                std::cout << "[*] set SVAR_base = ";
                _SVAR_base = _dataStack.size();
                std::cout << _SVAR_base << std::endl;
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
            {
                std::cout << "[*] DVAR[num] = value" << std::endl;
                auto num = _popDataInteger();
                auto value = _dataStack.pop();
                _dataStack.values()->at(_DVAR_base + num) = value;
                break;
            }
            case 0x8032:
            {
                std::cout << "[*] DVAR[num]" << std::endl;
                auto num = _popDataInteger();
                _dataStack.push(_dataStack.values()->at(_DVAR_base + num));
                break;
            }
            case 0x8033:
            {
                std::cout << "[*] eq ==" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a == b ? 1 : 0);
                break;
            }
            case 0x8034:
            {
                std::cout << "[*] neq !=" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a != b ? 1 : 0);
                break;
            }
            case 0x8035:
            {
                std::cout << "[*] leq <=" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a <= b ? 1 : 0);
                break;
            }
            case 0x8036:
            {
                std::cout << "[*] geq >=" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a >= b ? 1 : 0);
                break;
            }
            case 0x8037:
            {
                std::cout << "[*] lt <" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a < b ? 1 : 0);
                break;
            }
            case 0x8038:
            {
                std::cout << "[*] gt >" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a > b ? 1 : 0);
                break;
            }
            case 0x8039:
            {
                std::cout << "[*] plus +" << std::endl;
                auto b = _dataStack.pop();
                auto a = _dataStack.pop();
                switch (a->type())
                {
                    case VMStackValue::TYPE_POINTER: // string
                    {
                        auto p1 = dynamic_cast<VMStackPointerValue*>(a);
                        auto s1 = (std::string*) p1->value();
                        switch(b->type())
                        {
                            case VMStackValue::TYPE_POINTER: // string
                            {
                                auto p2 = dynamic_cast<VMStackPointerValue*>(b);
                                auto s2 = (std::string*) p2->value();
                                _pushDataPointer(new std::string(*s1 + *s2));
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT:
                            {
                                auto p2 = dynamic_cast<VMStackFloatValue*>(b);
                                auto s2 = std::to_string(p2->value());
                                _pushDataPointer(new std::string(*s1 + s2));
                                break;
                            }
                            case VMStackValue::TYPE_INTEGER:
                            {
                                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                                auto s2 = std::to_string(p2->value());
                                _pushDataPointer(new std::string(*s1 + s2));
                                break;
                            }
                        }

                        break;
                    }
                    case VMStackValue::TYPE_INTEGER:
                    {
                        auto p1 = dynamic_cast<VMStackIntValue*>(a);
                        switch (b->type())
                        {
                            case VMStackValue::TYPE_INTEGER:
                            {
                                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                                _pushDataInteger(p1->value() + p2->value());
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT:
                            {
                                auto p2 = dynamic_cast<VMStackFloatValue*>(b);
                                _pushDataFloat(p1->value() + p2->value());
                                break;
                            }
                            default:
                            {
                                throw Exception("VM::opcode PLUS - second argument is a pointer");
                            }
                        }
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT:
                    {
                        auto p1 = dynamic_cast<VMStackFloatValue*>(a);
                        switch (b->type())
                        {
                            case VMStackValue::TYPE_INTEGER:
                            {
                                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                                _pushDataFloat(p1->value() + p2->value());
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT:
                            {
                                auto p2 = dynamic_cast<VMStackFloatValue*>(b);
                                _pushDataFloat(p1->value() + p2->value());
                                break;
                            }
                            default:
                            {
                                throw Exception("VM::opcode PLUS - second argument is a pointer");
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 0x803a:
            {
                std::cout << "[*] minus -" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a-b);
                break;
            }
            case 0x803b:
                std::cout << "mult *" << std::endl;
                break;
            case 0x803c:
            {
                std::cout << "[*] div /" << std::endl;
                auto b = _dataStack.pop();
                auto a = _dataStack.pop();
                auto p1 = dynamic_cast<VMStackIntValue*>(a);
                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                _pushDataInteger(p1->value()/p2->value());
                break;
            }
            case 0x803d:
            {
                std::cout << "[*] mod %" << std::endl;
                auto b = _dataStack.pop();
                auto a = _dataStack.pop();
                auto p1 = dynamic_cast<VMStackIntValue*>(a);
                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                _pushDataInteger(p1->value()%p2->value());
                break;
            }
            case 0x803e:
            {
                std::cout << "[*] AND" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a & b);
                break;
            }
            case 0x803f:
            {
                std::cout << "OR" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a | b);
                break;
            }
            case 0x8045:
                std::cout << "stack:=NOT(p1) - logical not" << std::endl;
                break;
            case 0x8046:
            {
                std::cout << "[*] - value (change sign)" << std::endl;
                auto value = _popDataInteger();
                _pushDataInteger(-value);
                break;
            }
            case 0x80a9:
            {
                std::cout << "[*]void override_map_start(int x, int y, int elev, int rot)" << std::endl;
                auto direction = _popDataInteger();
                auto elevation = _popDataInteger();
                auto y = _popDataInteger();
                auto x = _popDataInteger();
                _overrideMapStart(x, y, elevation, direction);
                break;
            }
            case 0x80b4:
            {
                std::cout << "[*] int = rand (min, max)" << std::endl;
                auto max = _popDataInteger();
                auto min = _popDataInteger();
                _pushDataInteger(_rand(min, max));
                break;
            }
            case 0x80b6:
                std::cout << "int move_to(ObjectPtr obj, int tile_num, int elev)" << std::endl;
                break;
            case 0x80b7:
            {
                std::cout << "[*] ObjectPtr create_object_sid(int pid, int tile_num, int elev, int sid)" << std::endl;
                auto SID = _popDataInteger();
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto PID = _popDataInteger();
                _pushDataPointer(_createObject(PID, position, elevation, SID));
                break;
            }
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
                std::cout << "[*] stack:=dude_obj" << std::endl;
                _pushDataPointer(_dudeObject());
                break;
            case 0x80c1:
            {
                std::cout << "[*] LVAR[num]" << std::endl;
                auto num = _popDataInteger();
                _pushDataInteger(_lvar(num));
                break;
            }
            case 0x80c2:
            {
                std::cout << "[*] LVAR[num] = value" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();
                _lvar(num, value);
                break;
            }
            case 0x80c3:
            {
                std::cout << "[*] MVAR[num]" << std::endl;
                auto num = _popDataInteger();
                _pushDataInteger(_mvar(num));
                break;
            }
            case 0x80c4:
            {
                std::cout << "[*] MVAR[num] = valuw" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();
                _mvar(num, value);
                break;
            }
            case 0x80c5:
            {
                std::cout << "[*] GVAR[num];" << std::endl;
                auto num = _popDataInteger();
                _pushDataInteger(_gvar(num));
                break;
            }
            case 0x80c6:
            {
                std::cout << "[*] GVAR[num] = value" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();
                _gvar(num, value);
                break;
            }
            case 0x80c7:
            {
                std::cout << "[*] int script_action()" << std::endl;
                _pushDataInteger(21);
                break;
            }
            case 0x80c8:
                std::cout << "stack:=obj_type(p1)" << std::endl;
                break;
            case 0x80ca:
                std::cout << "int get_critter_stat(ObjectPtr who, int stat)" << std::endl;
                break;
            case 0x80d3:
                std::cout << "stack:=tile_distance_objs(p2,p1)" << std::endl;
                break;
            case 0x80d4:
                std::cout << "int objectPosition(ObjectPtr obj)" << std::endl;
                break;
            case 0x80e5:
                std::cout << "wm_area_set_pos(p3,p2,p1)" << std::endl;
                break;
            case 0x80e9:
            {
                std::cout << "[*] void set_light_level(int level)" << std::endl;
                auto level = _popDataInteger();
                _setLightLevel(level);
                break;
            }
            case 0x80ef:
                std::cout << "void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)" << std::endl;
                break;
            case 0x80f6:
            {
                std::cout << "[*] int game_time_hour" << std::endl;
                _pushDataInteger(_getTime());
                break;
            }
            case 0x8102:
                std::cout << "int critter_add_trait(ObjectPtr who, int trait_type, int trait, int amount) " << std::endl;
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
            {
                std::cout << "[*] void add_mult_objs_to_inven(ObjectPtr who, ObjectPtr item, int count)" << std::endl;
                auto count = _popDataInteger();
                auto item = _popDataPointer();
                auto who = _popDataPointer();
                _addObjectsToInventory((std::string*)who, (std::string*)item, count);
                break;
            }
            case 0x8118:
                std::cout << "[*] int get_month" << std::endl;
                _pushDataInteger(_getMonth());
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
        auto value = stackIntValue->value();
        //std::cout << "        >Pop integer: " << std::dec << value << std::endl;
        return value;
    }
    throw Exception("VM::_popDataInteger() - stack value is not integer");
}

void VM::_pushDataInteger(int value)
{
    //std::cout << "        >Push integer: " << std::dec << value << std::endl;
    _dataStack.push(new VMStackIntValue(value));
}

float VM::_popDataFloat()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_FLOAT)
    {
        auto stackIntValue = dynamic_cast<VMStackFloatValue*>(stackValue);
        auto value = stackIntValue->value();
        //std::cout << "        >Pop float: " << std::dec << value << std::endl;
        return value;
    }
    throw Exception("VM::_popDataFloat() - stack value is not float");
}

void VM::_pushDataFloat(float value)
{
    //std::cout << "        >Push float: " << std::dec << value << std::endl;
    _dataStack.push(new VMStackFloatValue(value));
}

void* VM::_popDataPointer()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_POINTER)
    {
        auto stackIntValue = dynamic_cast<VMStackPointerValue*>(stackValue);
        auto value = stackIntValue->value();
        //std::cout << "        >Pop pointer: " <<  value << std::endl;
        return value;
    }
    throw Exception("VM::_popDataPointer() - stack value is not a pointer");
}

void VM::_pushDataPointer(void* value)
{
    //std::cout << "        >Push pointer: " <<  value << std::endl;
    _dataStack.push(new VMStackPointerValue(value));
}

int VM::_popReturnInteger()
{
    auto stackValue = _returnStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        //std::cout << "        >dPop integer: " << std::dec << stackIntValue->value() << std::endl;
        return stackIntValue->value();
    }
    throw Exception("VM::_popReturnInteger() - stack value is not integer");
}

void VM::_pushReturnInteger(int value)
{
    //std::cout << "        >dPush integer: " << std::dec << value << std::endl;
    _returnStack.push(new VMStackIntValue(value));
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

std::string* VM::_createObject(int PID, int position, int elevation, int SID)
{
    return new std::string("I am new object"); // just for testing
}

std::string* VM::_dudeObject()
{
    return new std::string("I am Dude object");
}

void VM::_addObjectsToInventory(std::string* who, std::string* item, int count)
{
    std::cout << "Adding objects to inventory" << std::endl;
    std::cout << *who << std::endl;
    std::cout << *item << std::endl;
    std::cout << count << std::endl;
}

int VM::_getMonth()
{
    return 1; // January
}

int VM::_getTime()
{
    return 1212; //12 hours 12 minutes
}

void VM::_setLightLevel(int level)
{
    std::cout << "     Setting light level to: " << level << std::endl;
}

void VM::_overrideMapStart(int x, int y, int elevation, int direction)
{
    std::cout << "      Overriding map start" << std::endl;
    std::cout << "      x: " << x << std::endl;
    std::cout << "      y: " << y << std::endl;
    std::cout << "      elevation: " << elevation << std::endl;
    std::cout << "      direction: " << direction << std::endl;
    auto position = y*200 + x;
    auto player = _game->location()->player();
    player->setX(_game->location()->hexagonToX(position));
    player->setY(_game->location()->hexagonToY(position));
    player->setOrientation(direction);
    player->setElevation(elevation);

}

void VM::_gvar(int num, int value)
{
}

int VM::_gvar(int num)
{
    return 0;
}

void VM::_mvar(int num, int value)
{
}

int VM::_mvar(int num)
{
    return 0;
}

void VM::_lvar(int num, int value)
{
}

int VM::_lvar(int num)
{
    return 0;
}

int VM::_rand(int min, int max)
{
    return min;
}

}




