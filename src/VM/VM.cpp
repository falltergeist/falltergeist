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
#include <ctime>
#include <sstream>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Logger.h"
#include "../Engine/PathFinding/Hexagon.h"
#include "../Engine/PathFinding/HexagonGrid.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameDefines.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/CritterDialogState.h"
#include "../States/LocationState.h"
#include "../VM/OpcodeFactory.h"
#include "../VM/VM.h"
#include "../VM/VMHaltException.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"

// Third party includes

namespace Falltergeist
{

VM::VM(libfalltergeist::IntFileType* script, void* owner)
{
    _owner = owner;
    _script = script;
    if (!_script) throw Exception("VM::VM() - script is null");
}

VM::VM(std::string filename, void* owner)
{
    _owner = owner;
    _script = ResourceManager::intFileType(filename);
    if (!_script) throw Exception("VM::VM() - script is null: " + filename);
}

VM::~VM()
{
}

bool VM::hasFunction(std::string name)
{
    try
    {
        _script->function(name);
    }
    catch (libfalltergeist::Exception &e)
    {
        return false;
    }
    return true;
}

void VM::call(std::string name)
{
    _overrides = false;
    try
    {
        _programCounter = _script->function(name);
        pushDataInteger(0); // arguments counter;
        pushReturnInteger(0); // return adrress
        Logger::debug("SCRIPT") << "CALLED: " << name << " [" << _script->filename() << "]" << std::endl;
        run();
        popDataInteger(); // remove function result
        Logger::debug("SCRIPT") << "Function ended" << std::endl;
    }
    catch (libfalltergeist::Exception &e)
    {
        Logger::debug("SCRIPT") << "Function not exist: " << name << std::endl;
    }
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;
    run();
    popDataInteger(); // remove @start function result
}

void VM::run()
{
    while (_programCounter != _script->size())
    {
        if (_programCounter == 0 && _initialized) return;

        _script->setPosition(_programCounter);
        unsigned short opcode;
        *_script >> opcode;

        OpcodeHandler* opcodeHandler = OpcodeFactory::createOpcode(opcode, this);
        try
        {
            opcodeHandler->run();
        }
        catch(VMHaltException& e)
        {
            return;
        }
    }
}

int VM::popDataInteger()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popDataInteger() - stack value is not integer");
}

void VM::pushDataInteger(int value)
{
    _dataStack.push(new VMStackIntValue(value));
}

float VM::popDataFloat()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_FLOAT)
    {
        auto stackFloatValue = dynamic_cast<VMStackFloatValue*>(stackValue);
        auto value = stackFloatValue->value();
        return value;
    }
    throw Exception("VM::popDataFloat() - stack value is not float");
}

void VM::pushDataFloat(float value)
{
    _dataStack.push(new VMStackFloatValue(value));
}

void* VM::popDataPointer()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_POINTER)
    {
        auto stackPointerValue = dynamic_cast<VMStackPointerValue*>(stackValue);
        auto value = stackPointerValue->value();
        return value;
    }
    throw Exception("VM::popDataPointer() - stack value is not a pointer");
}

void VM::pushDataPointer(void* value, unsigned int type)
{
    auto pointer = new VMStackPointerValue(value);
    pointer->setPointerType(type);
    _dataStack.push(pointer);
}

int VM::popReturnInteger()
{
    auto stackValue = _returnStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popReturnInteger() - stack value is not integer");
}

void VM::pushReturnInteger(int value)
{
    _returnStack.push(new VMStackIntValue(value));
}

bool VM::popDataLogical()
{
    switch (_dataStack.top()->type())
    {
        case VMStackValue::TYPE_FLOAT:
            return (bool) popDataFloat();
        case VMStackValue::TYPE_INTEGER:
            return (bool) popDataInteger();
        case VMStackValue::TYPE_POINTER:
            return (bool) popDataPointer();
    }
    throw Exception("VM::popDataLogical() - something strange happened");
}

int VM::_metarule(int type, VMStackValue* value)
{
    switch(type)
    {
        case 14: // METARULE_TEST_FIRSTRUN
            // Если карта открывается в первый раз, то возвращает TRUE;
            return 1;
        case 16: // METARULE_PARTY_COUNT
            return 0;
        case 17: //  METARULE_AREA_KNOWN
            return 1;
        case 18: // METARULE_WHO_ON_DRUGS
            return 0;
        case 19: // METARULE_MAP_KNOWN
            return 1;
        case 22: // METARULE_IS_LOADGAME
            // Игра загружается?
            return 0;  // 0 - false
        case 30: // METARULE_CAR_CURRENT_TOWN
            return 0;
        case 40: // METARULE_SKILL_CHECK_TAG
            return 0;
        case 44: // METARULE_GET_WORLDMAP_XPOS
            // позиция по x на карте мира
            return 300;
        case 45: // METARULE_GET_WORLDMAP_YPOS
            // позиция по y на карте мира
            return 300;
        case 46: // METARULE_CURRENT_TOWN
            // Текущий город
            return 0;

    }
    throw Exception("VM::_metarule() - unknown type: " + std::to_string(type));
}

int VM::metarule(int type, VMStackValue* value)
{
  return _metarule(type,value);
}

void VM::setLightLevel(int level)
{
    Logger::debug("SCRIPT") << "     Setting light level to: " + std::to_string(level) << std::endl;
}

void VM::_playMovie(int movieNum)
{

}

void VM::playMovie(int movieNum)
{
  _playMovie(movieNum);
}

int VM::tile_num_in_direction(int start_tile, int dir, int distance)
{
    return _tile_num_in_direction(start_tile,dir,distance);
}


void VM::_displayString(std::string str)
{
    Logger::debug("SCRIPT") << str << std::endl;
}

int VM::_tile_num_in_direction(int start_tile, int dir, int distance)
{
    return start_tile + 20;
}

int VM::_critter_add_trait(void* who, int trait_type, int trait, int amount)
{
    return 0;
}

int VM::critter_add_trait(void* who, int trait_type, int trait, int amount)
{
    return _critter_add_trait(who,trait_type,trait,amount);
}

int VM::_metarule3(int meta, VMStackValue* p1, int p2, int p3)
{
    switch(meta)
    {
        case 100: // rm_fixed_timer_event
            return 0;
        case 110:   // unknown
            return 0;
    }
    throw Exception("VM::_metarule3() - unknown meta: " + std::to_string(meta));

}

int VM::metarule3(int meta, VMStackValue* p1, int p2, int p3)
{
    return _metarule3(meta,p1,p2,p3);
}

std::string VM::msgMessage(int msg_file_num, int msg_num)
{
    auto lst = ResourceManager::lstFileType("data/dialogs.lst");
    auto msg = ResourceManager::msgFileType("text/english/dialog/" + lst->strings()->at(msg_file_num - 1));
    if (!msg)
    {
        Logger::debug("SCRIPT") << "VM::msgMessage(file, num) not found. file: " + std::to_string(msg_file_num) + " num: " + std::to_string(msg_num) << std::endl;
        return "";
    }
    return msg->message(msg_num)->text();
}

libfalltergeist::IntFileType* VM::script()
{
    return _script;
}

unsigned int VM::programCounter()
{
    return _programCounter;
}

void VM::setProgramCounter(unsigned int value)
{
    _programCounter = value;
}

VMStack* VM::dataStack()
{
    return &_dataStack;
}

VMStack* VM::returnStack()
{
    return &_returnStack;
}

std::vector<VMStackValue*>* VM::LVARS()
{
    return &_LVARS;
}

void* VM::owner()
{
    return _owner;
}

bool VM::initialized()
{
    return _initialized;
}

void VM::setInitialized(bool value)
{
    _initialized = value;
}

int VM::SVARbase()
{
    return _SVAR_base;
}

void VM::setSVARbase(int Value)
{
    _SVAR_base = Value;
}

int VM::DVARbase()
{
    return _DVAR_base;
}

void VM::setDVARBase(int Value)
{
    _DVAR_base = Value;
}

bool VM::overrides()
{
    return _overrides;
}

void VM::setOverrides(bool Value)
{
    _overrides = Value;
}

}
