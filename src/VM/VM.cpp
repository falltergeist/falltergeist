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
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../VM/OpcodeFactory.h"
#include "../VM/VM.h"
#include "../VM/VMHaltException.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"
#include "../VM/VMStackStringValue.h"

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

std::string VM::filename()
{
    return _script->filename();
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
            delete opcodeHandler;
        }
        catch(VMHaltException& e)
        {
            return;
        }
    }
}

int VM::popDataInteger()
{
    return _dataStack.pop()->integerValue();
}

void VM::pushDataInteger(int value)
{
    _dataStack.push(VMStackValue(value));
}

float VM::popDataFloat()
{
    return _dataStack.pop()->floatValue();
}

void VM::pushDataFloat(float value)
{
    _dataStack.push(VMStackValue(value));
}

Game::GameObject* VM::popDataObject()
{
    return _dataStack.pop()->objectValue();
}

void VM::pushDataObject(Game::GameObject* value)
{
    _dataStack.push(VMStackValue(value));
}

std::string& VM::popDataString()
{
    auto stackStringValue = dynamic_cast<VMStackStringValue*>(_dataStack.pop());
    if (stackStringValue)
    {
        return stackStringValue->value();
    }
    throw Exception("VM::popDataString() - stack value is not a string");
}

void VM::pushDataString(std::string &value)
{
    auto stackStringValue = new VMStackStringValue(value);
    _dataStack.push(stackStringValue);
}

int VM::popReturnInteger()
{
    return _returnStack.pop()->integerValue();
}

void VM::pushReturnInteger(int value)
{
    _returnStack.push(VMStackValue(value));
}

bool VM::popDataLogical()
{
    auto stackValue = _dataStack.pop();
    switch (stackValue->type())
    {
        case VMStackValue::TYPE_INTEGER:
            return stackValue->integerValue() != 0;
        case VMStackValue::TYPE_FLOAT:
            return (bool)stackValue->floatValue();
        case VMStackValue::TYPE_STRING:
            return stackValue->stringValue().length() > 0;
        case VMStackValue::TYPE_OBJECT:
            return stackValue->objectValue() != nullptr;
    }
    throw Exception("VM::popDataLogical() - something strange happened");
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
    // @TODO: add check for valid address
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

std::vector<VMStackValue>* VM::LVARS()
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
