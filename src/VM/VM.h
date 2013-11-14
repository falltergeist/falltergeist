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
    void* _owner;
    libfalltergeist::IntFileType * _script = 0;    
    bool _initialized = false;
    VMStack _dataStack;
    VMStack _returnStack;
    std::vector<VMStackValue*> _LVARS;
    unsigned int _programCounter = 0;
    int _DVAR_base = 0;
    int _SVAR_base = 0;

    int _popReturnInteger();
    void _pushReturnInteger(int value);
    int _popDataInteger();
    void _pushDataInteger(int value);
    float _popDataFloat();
    void _pushDataFloat(float value);
    void* _popDataPointer();
    void _pushDataPointer(void* value);
    bool _popDataLogical();


    int _metarule(int type, VMStackValue* value);
    int _metarule3(int meta, VMStackValue* p1, int p2, int p3);
    int _getMonth();
    int _getTime();
    void _setLightLevel(int level);
    void _playMovie(int movieNum);
    void _displayString(std::string* str);
    void _debugMessage(std::string* str);
    int _tile_num_in_direction(int start_tile, int dir, int distance);
    int _critter_add_trait(void* who, int trait_type, int trait, int amount);
    void _anim(void* who, int anim, int direction);
public:
    VM(libfalltergeist::IntFileType * script, void* owner);
    VM(std::string filename, void* owner);
    virtual ~VM();
    void run();
    void initialize();
    void call(std::string name);
};

}
#endif // FALLTERGEIST_VM_H
