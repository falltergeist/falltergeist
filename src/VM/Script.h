#pragma once

#include <string>
#include "../Format/Enums.h"
#include "../VM/Stack.h"
#include "../VM/StackValue.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Int
        {
            class File;
        }
    }

    namespace Game
    {
        class Object;
    }

    namespace VM
    {
        /**
         * Script class represents Virtual Machine for running vanilla Fallout scripts.
         * VM uses 2 stacks (return stack and data stack).
         * Each operator from .INT script is handled by one of the Handler classes and it manipulates one or both stacks in some way.
         * Typical scripting command takes 0 or more arguments from the data stack and puts one return value to the same stack.
         */
        class Script
        {
            public:
                Script(Format::Int::File *script, const std::shared_ptr<Game::Object> &owner);

                Script(const std::string &filename, const std::shared_ptr<Game::Object> &owner);

                virtual ~Script();

                void run();

                void initialize();

                bool initialized();

                bool overrides();

                void setOverrides(bool Value);

                void setInitialized(bool value);

                std::string msgMessage(int msg_file_num, int msg_num);

                std::string msgSpeech(int msg_file_num, int msg_num);

                // Returns filename of an .int script file
                std::string filename();

                bool hasFunction(const std::string &name);

                void call(const std::string &name);

                Format::Int::File *script();

                const std::shared_ptr<Game::Object> &owner();

                unsigned int programCounter();

                void setProgramCounter(unsigned int value);

                Stack *dataStack();

                Stack *returnStack();

                std::vector<StackValue> *LVARS();

                size_t DVARbase();

                void setDVARBase(size_t Value);

                size_t SVARbase();

                void setSVARbase(size_t value);

                VM::Script *setFixedParam(int _fixedParam);

                int fixedParam() const;

                VM::Script *setTargetObject(const std::shared_ptr<Game::Object> &targetObject);

                const std::shared_ptr<Falltergeist::Game::Object> &targetObject() const;

                VM::Script *setSourceObject(const std::shared_ptr<Game::Object> &sourceObject);

                const std::shared_ptr<Falltergeist::Game::Object> &sourceObject() const;

                SKILL usedSkill() const;

                VM::Script *setUsedSkill(SKILL skill);

            protected:
                std::shared_ptr<Game::Object> _owner;
                std::shared_ptr<Game::Object> _sourceObject;
                std::shared_ptr<Game::Object> _targetObject;
                SKILL _usedSkill = SKILL::NONE;

                int _fixedParam = 0;
                int _actionUsed = 0;
                Format::Int::File *_script = 0;
                bool _initialized = false;
                bool _overrides = false;
                Stack _dataStack;
                Stack _returnStack;
                std::vector<StackValue> _LVARS;
                unsigned int _programCounter = 0;
                size_t _DVAR_base = 0;
                size_t _SVAR_base = 0;
        };
    }
}
