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

#ifndef FALLTERGEIST_VM_SCRIPT_H
#define FALLTERGEIST_VM_SCRIPT_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Format/Enums.h"
#include "../VM/Stack.h"
#include "../VM/StackValue.h"
#include "../VM/IFalloutContext.h"

// Third party includes

namespace Falltergeist {
    namespace Format {
        namespace Int {
            class File;
        }
    }
    namespace Game {
        class Object;
    }
    namespace VM {
        /**
         * Script class represents Virtual Machine for running vanilla Fallout scripts.
         * VM uses 2 stacks (return stack and data stack).
         * Each operator from .INT script is handled by one of the Handler classes and it manipulates one or both stacks in some way.
         * Typical scripting command takes 0 or more arguments from the data stack and puts one return value to the same stack.
         *
         * TODO remove enable_shared_from_this
         */
        class Script : public std::enable_shared_from_this<Script>, public virtual IFalloutContext {
        public:
            Script(Format::Int::File *script, Game::Object *owner);

            Script(const std::string &filename, Game::Object *owner);

            virtual ~Script();

            // IFalloutContext
            std::shared_ptr<Game::DudeObject> player() override;

            void stopExecution() override;

            std::shared_ptr<IFalloutProcedure> getProcedureByIndex(unsigned int index) const override;

            std::shared_ptr<IFalloutStack> dataStack() override;

            std::shared_ptr<IFalloutStack> returnStack() override;

            std::shared_ptr<IFalloutProcedure> getProcedureByName(const std::string &name) const override;

            unsigned programCounter() const override;

            unsigned int scriptVarStackBase() const override;

            void setScriptVarStackBase(unsigned int stackBase) override;

            unsigned int dynamicVarStackBase() const override;

            void setDynamicVarStackBase(unsigned int stackBase) override;

            void setProgramCounter(unsigned value) override;

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

            Game::Object *owner();


            std::vector<StackValue> *LVARS();

            size_t DVARbase();

            void setDVARBase(size_t Value);

            size_t SVARbase();

            void setSVARbase(size_t Value);

            VM::Script *setFixedParam(int _fixedParam);

            int fixedParam() const;

            VM::Script *setTargetObject(Game::Object *_targetObject);

            Game::Object *targetObject() const;

            VM::Script *setSourceObject(Game::Object *_sourceObject);

            Game::Object *sourceObject() const;

            SKILL usedSkill() const;

            VM::Script *setUsedSkill(SKILL skill);

            std::string getIdentifierByIndex(unsigned int index) const override;

        protected:
            Game::Object *_owner = nullptr;
            Game::Object *_sourceObject = nullptr;
            Game::Object *_targetObject = nullptr;
            SKILL _usedSkill = SKILL::NONE;

            int _fixedParam = 0;
            int _actionUsed = 0;
            Format::Int::File *_script = 0;
            bool _initialized = false;
            bool _overrides = false;
            std::shared_ptr<IFalloutStack> _dataStack;
            std::shared_ptr<IFalloutStack> _returnStack;
            std::vector<StackValue> _LVARS;
            unsigned _programCounter = 0;
            size_t _DVAR_base = 0;
            size_t _SVAR_base = 0;
        };
    }
}
#endif // FALLTERGEIST_VM_SCRIPT_H
