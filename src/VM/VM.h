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
#include "../VM/VMStackPointerValue.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
class GameCritterObject;

class VM
{
protected:
    void* _owner = 0;
    libfalltergeist::IntFileType* _script = 0;
    bool _initialized = false;
    bool _overrides = false;
    VMStack _dataStack;
    VMStack _returnStack;
    std::vector<VMStackValue*> _LVARS;
    unsigned int _programCounter = 0;
    int _DVAR_base = 0;
    int _SVAR_base = 0;

    int _metarule(int type, VMStackValue* value);
    int _metarule3(int meta, VMStackValue* p1, int p2, int p3);
    int _getMonth();
    int _getTime();
    void _playMovie(int movieNum);
    void _displayString(std::string str);
    int _tile_num_in_direction(int start_tile, int dir, int distance);
    int _critter_add_trait(void* who, int trait_type, int trait, int amount);
    std::string msgMessage(int msg_file_num, int msg_num);
public:
    VM(libfalltergeist::IntFileType* script, void* owner);
    VM(std::string filename, void* owner);
    virtual ~VM();
    void run();
    void initialize();

    bool initialized();
    bool overrides();
    void setOverrides(bool Value);
    void setInitialized(bool value);

    bool hasFunction(std::string name);
    int getTime();
    int metarule3(int meta, VMStackValue* p1, int p2, int p3);
    int tile_num_in_direction(int start_tile, int dir, int distance);
    void setLightLevel(int level);

    void call(std::string name);
    libfalltergeist::IntFileType* script();

    void* owner();

    unsigned int programCounter();
    void setProgramCounter(unsigned int value);

    int popReturnInteger();
    void pushReturnInteger(int value);
    int popDataInteger();
    void pushDataInteger(int value);
    float popDataFloat();
    void pushDataFloat(float value);
    void* popDataPointer();
    void pushDataPointer(void* value, unsigned int type = VMStackPointerValue::POINTER_TYPE_UNKNOWN);
    bool popDataLogical();

    VMStack* dataStack();
    VMStack* returnStack();
    std::vector<VMStackValue*>* LVARS();

    int DVARbase();
    void setDVARBase(int Value);
    int SVARbase();
    void setSVARbase(int Value);

    void anim(GameCritterObject* who, int anim, int direction);

};

}
#endif // FALLTERGEIST_VM_H
