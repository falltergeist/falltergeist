#pragma once

// Project includes
#include "../Format/Enums.h"
#include "../Format/Int/File.h"
#include "../VM/Stack.h"
#include "../VM/StackValue.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist
{
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
        class Script final
        {
            public:
                Script(std::unique_ptr<Format::Int::File> intFile, Game::Object *owner);

                ~Script() = default;

                void run();

                void initialize();

                bool initialized();

                bool overrides();

                void setOverrides(bool Value);

                void setInitialized(bool value);

                std::string msgMessage(int msg_file_num, int msg_num);

                std::string msgSpeech(int msg_file_num, int msg_num);

                // Returns filename of an .int script file
                const std::string& filename() const;

                bool hasFunction(const std::string &name);

                void call(const std::string &name);

                std::unique_ptr<Format::Int::File>& intFile();

                Game::Object *owner();

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

                VM::Script *setTargetObject(Game::Object *_targetObject);

                Game::Object *targetObject() const;

                VM::Script *setSourceObject(Game::Object *_sourceObject);

                Game::Object *sourceObject() const;

                SKILL usedSkill() const;

                VM::Script *setUsedSkill(SKILL skill);

            private:
                Game::Object *_owner = nullptr;

                Game::Object *_sourceObject = nullptr;

                Game::Object *_targetObject = nullptr;

                SKILL _usedSkill = SKILL::NONE;

                int _fixedParam = 0;

                int _actionUsed = 0;

                std::unique_ptr<Format::Int::File> _intFile;

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
