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

#ifndef FALLTERGEIST_VM_H
#define FALLTERGEIST_VM_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../VM/VMStack.h"
#include "../../lib/libfalltergeist/libfalltergeist.h"

// Third party includes

namespace Falltergeist
{

class VM
{
protected:
    std::shared_ptr<void> _owner;
    std::shared_ptr<libfalltergeist::IntFileType> _script;
    bool _initialized = false;
    VMStack _dataStack;
    VMStack _returnStack;
    std::vector<std::shared_ptr<VMStackValue>> _LVARS;
    unsigned int _programCounter = 0;
    int _DVAR_base = 0;
    int _SVAR_base = 0;

    int _metarule(int type, std::shared_ptr<VMStackValue> value);
    int _metarule3(int meta, std::shared_ptr<VMStackValue> p1, int p2, int p3);
    int _getMonth();
    int _getTime();
    void _setLightLevel(int level);
    void _playMovie(int movieNum);
    void _displayString(std::shared_ptr<std::string> str);
    void _debugMessage(std::shared_ptr<std::string> str);
    int _tile_num_in_direction(int start_tile, int dir, int distance);
    int _critter_add_trait(std::shared_ptr<void> who, int trait_type, int trait, int amount);
    void _anim(std::shared_ptr<void> who, int anim, int direction);
    std::string msgMessage(int msg_file_num, int msg_num);
public:
    VM(std::shared_ptr<libfalltergeist::IntFileType> script, std::shared_ptr<void> owner);
    VM(std::string filename, std::shared_ptr<void> owner);
    virtual ~VM();
    void run();
    void initialize();
    void call(std::string name);
    std::shared_ptr<libfalltergeist::IntFileType> script();

    unsigned int programCounter();
    void setProgramCounter(unsigned int value);

    int popReturnInteger();
    void pushReturnInteger(int value);
    int popDataInteger();
    void pushDataInteger(int value);
    float popDataFloat();
    void pushDataFloat(float value);
    std::shared_ptr<void> popDataPointer();
    void pushDataPointer(std::shared_ptr<void> value);
    bool popDataLogical();

    VMStack* dataStack();
    VMStack* returnStack();

};

}
#endif // FALLTERGEIST_VM_H
