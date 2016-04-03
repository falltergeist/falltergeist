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
#include <memory>
#include <sstream>

// Falltergeist includes
#include "../Exception.h"
#include "../Format/Int/File.h"
#include "../Format/Int/Procedure.h"
#include "../Format/Lst/File.h"
#include "../Format/Msg/File.h"
#include "../Format/Msg/Message.h"
#include "../Game/Game.h"
#include "../Game/Object.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../VM/ErrorException.h"
#include "../VM/HaltException.h"
#include "../VM/OpcodeFactory.h"
#include "../VM/Script.h"
#include "../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        Script::Script(Format::Int::File* script, Game::Object* owner)
        {
            _owner = owner;
            _script = script;
            if (!_script) throw Exception("Script::VM() - script is null");
        }

        Script::Script(const std::string& filename, Game::Object* owner)
        {
            _owner = owner;
            _script = ResourceManager::getInstance()->intFileType(filename);
            if (!_script) throw Exception("Script::VM() - script is null: " + filename);
        }

        Script::~Script()
        {
        }

        std::string Script::filename()
        {
            return _script->filename();
        }

        bool Script::hasFunction(const std::string& name)
        {
            return _script->procedure(name) != nullptr;
        }

        void Script::call(const std::string& name)
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

        void Script::initialize()
        {
            if (_initialized) return;
            _programCounter = 0;
            run();
            _dataStack.popInteger(); // remove @start function result
        }

        void Script::run()
        {
            while (_programCounter != _script->size())
            {
                if (_programCounter == 0 && _initialized) return;
                auto offset = _programCounter;
                _script->setPosition(_programCounter);
                unsigned short opcode;
                *_script >> opcode;

                std::unique_ptr<OpcodeHandler> opcodeHandler(OpcodeFactory::createOpcode(opcode, this));
                try
                {
                    opcodeHandler->run();
                }
                catch (HaltException& e)
                {
                    return;
                }
                catch (ErrorException& e)
                {
                    Logger::error("SCRIPT") << e.what() << " in [" << std::hex << opcode << "] at " << _script->filename() << ":0x" << offset << std::endl;
                    _dataStack.values()->clear();
                    _dataStack.push(0); // to end script properly
                    return;
                }
            }
        }

        std::string Script::msgMessage(int msg_file_num, int msg_num)
        {
            auto lst = ResourceManager::getInstance()->lstFileType("scripts/scripts.lst");
            auto scriptName = lst->strings()->at(msg_file_num - 1);
            auto msg = ResourceManager::getInstance()->msgFileType("text/english/dialog/" + scriptName.substr(0, scriptName.find(".int")).append(".msg"));
            if (!msg)
            {
                Logger::debug("SCRIPT") << "Script::msgMessage(file, num) not found. file: " + std::to_string(msg_file_num) + " num: " + std::to_string(msg_num) << std::endl;
                return "";
            }
            return msg->message(msg_num)->text();
        }

        Format::Int::File* Script::script()
        {
            return _script;
        }

        unsigned int Script::programCounter()
        {
            return _programCounter;
        }

        void Script::setProgramCounter(unsigned int value)
        {
            if (value >= _script->size())
            {
                std::stringstream ss;
                ss << "Script::setProgramCounter() - address out of range: " << std::hex << value;
                throw ErrorException(ss.str());
            }
            _programCounter = value;
        }

        Stack* Script::dataStack()
        {
            return &_dataStack;
        }

        Stack* Script::returnStack()
        {
            return &_returnStack;
        }

        std::vector<StackValue>* Script::LVARS()
        {
            return &_LVARS;
        }

        Game::Object* Script::owner()
        {
            return _owner;
        }

        bool Script::initialized()
        {
            return _initialized;
        }

        void Script::setInitialized(bool value)
        {
            _initialized = value;
        }

        int Script::SVARbase()
        {
            return _SVAR_base;
        }

        void Script::setSVARbase(int Value)
        {
            _SVAR_base = Value;
        }

        Script* Script::setFixedParam(int fixedParam)
        {
            this->_fixedParam = fixedParam;
            return this;
        }

        int Script::fixedParam() const
        {
            return _fixedParam;
        }

        Script* Script::setTargetObject(Game::Object* targetObject)
        {
            this->_targetObject = targetObject;
            return this;
        }

        Game::Object* Script::targetObject() const
        {
            return _targetObject;
        }

        Script* Script::setSourceObject(Game::Object* sourceObject)
        {
            this->_sourceObject = sourceObject;
            return this;
        }

        Game::Object* Script::sourceObject() const
        {
            return _sourceObject;
        }

        Script* Script::setActionUsed(int actionUsed)
        {
            this->_actionUsed = actionUsed;
            return this;
        }

        int Script::actionUsed() const
        {
            return _actionUsed;
        }

        int Script::DVARbase()
        {
            return _DVAR_base;
        }

        void Script::setDVARBase(int Value)
        {
            _DVAR_base = Value;
        }

        bool Script::overrides()
        {
            return _overrides;
        }

        void Script::setOverrides(bool Value)
        {
            _overrides = Value;
        }
    }
}
