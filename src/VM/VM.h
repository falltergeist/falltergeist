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
    Game* _game = 0;
    libfalltergeist::IntFileType * _script = 0;    
    bool _initialized = false;
    VMStack _dataStack;
    VMStack _returnStack;
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

    int _metarule(int type, int value);
    std::string* _createObject(int PID, int position, int elevation, int SID);
    std::string* _dudeObject();
    void _addObjectsToInventory(std::string* who, std::string* item, int count);
    int _getMonth();
    int _getTime();
    void _setLightLevel(int level);
    void _overrideMapStart(int x, int y, int elevation, int direction);
    void _gvar(int num, int value);
    int _gvar(int num);
    void _mvar(int num, int value);
    int _mvar(int num);
    void _lvar(int num, int value);
    int _lvar(int num);
    int _rand(int min, int max);
    void _exportVar(std::string* name);
    void _exportVar(std::string* name, int value);
    void _playMovie(int movieNum);
    std::string* _msgMessage(int msgList, int msgNum);
    void _displayString(std::string* str);
    void _debugMessage(std::string* str);
    void _giveExpPoints(int value);
public:
    VM(libfalltergeist::IntFileType * script);
    VM(std::string filename);
    virtual ~VM();
    void run();
    void initialize();
    void call(std::string name);
};

}
#endif // FALLTERGEIST_VM_H
