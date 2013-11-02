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
    libfalltergeist::IntFileType * _script = 0;
    bool _initialized = false;
    VMStack _dataStack;
    VMStack _returnStack;
    int _programCounter = 0;
    int _localVarBase = 0;
    int _scriptVarsBase = 0;

    int _popDataInteger();
    int _metarule(int type, int value);
    void _pushDataInteger(int value);
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
