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
#include "../Game/Object.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../VM/OpcodeFactory.h"
#include "../VM/VM.h"
#include "../VM/VMErrorException.h"
#include "../VM/VMHaltException.h"
<<<<<<< HEAD
#include "../VM/VMStackValue.h"
=======
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"
#include "../VM/VMStackStringValue.h"
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts

// Third party includes

namespace Falltergeist
{

VM::VM(libfalltergeist::Int::File* script, Game::GameObject* owner)
{
    _owner = owner;
    _script = script;
    if (!_script) throw Exception("VM::VM() - script is null");
}

VM::VM(std::string filename, Game::GameObject* owner)
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
    return _script->procedure(name) != nullptr;
}

void VM::call(std::string name)
{
    _overrides = false;
    auto procedure = _script->procedure(name);
    if (!procedure) return;

    _programCounter = procedure->bodyOffset();
    _dataStack.push(0); // arguments counter;
    _returnStack.push(0); // return address
    Logger::debug("SCRIPT") << "CALLED: " << name << " [" << _script->filename() << "]" << std::endl;
    run();
    _dataStack.popInteger(); // remove function result
    Logger::debug("SCRIPT") << "Function ended" << std::endl;

    // reset special script arguments
    _sourceObject = _targetObject = nullptr;
    _actionUsed = _fixedParam = 0;
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;
    run();
    _dataStack.popInteger(); // remove @start function result
}

void VM::run()
{
    while (_programCounter != _script->size())
    {
        if (_programCounter == 0 && _initialized) return;
        auto offset = _programCounter;
        _script->setPosition(_programCounter);
        unsigned short opcode;
        *_script >> opcode;

        OpcodeHandler* opcodeHandler = OpcodeFactory::createOpcode(opcode, this);
        try
        {
            opcodeHandler->run();
            delete opcodeHandler;
        }
        catch (VMHaltException& e)
        {
            return;
        }
<<<<<<< HEAD
        catch (VMErrorException& e)
        {
            Logger::error("SCRIPT") << e.what() << " in [" << std::hex << opcode << "] at " << _script->filename() << ":0x" << offset << std::endl;
            _dataStack.values()->clear();
            _dataStack.push(0); // to end script properly
            return;
        }
    }
=======
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
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
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

libfalltergeist::Int::File* VM::script()
{
    return _script;
}

unsigned int VM::programCounter()
{
    return _programCounter;
}

void VM::setProgramCounter(unsigned int value)
{
    if (value >= _script->size())
    {
        std::stringstream ss;
        ss << "VM::setProgramCounter() - address out of range: " << std::hex << value;
        throw VMErrorException(ss.str());
    }
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

Game::GameObject* VM::owner()
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

VM* VM::setFixedParam(int fixedParam)
{
    this->_fixedParam = fixedParam;
    return this;
}

int VM::fixedParam() const
{
    return _fixedParam;
}

VM* VM::setTargetObject(Game::GameObject* targetObject)
{
    this->_targetObject = targetObject;
    return this;
}

Game::GameObject* VM::targetObject() const
{
    return _targetObject;
}

VM* VM::setSourceObject(Game::GameObject* sourceObject)
{
    this->_sourceObject = sourceObject;
    return this;
}

Game::GameObject* VM::sourceObject() const
{
    return _sourceObject;
}

VM* VM::setActionUsed(int actionUsed)
{
    this->_actionUsed = actionUsed;
    return this;
}

int VM::actionUsed() const
{
    return _actionUsed;
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
