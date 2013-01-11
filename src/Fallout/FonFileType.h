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

#ifndef FALLTERGEIST_FONFILETYPE_H
#define FALLTERGEIST_FONFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

struct FonSymbol
{
    unsigned int width;
    unsigned int dataOffset;
    char * data;
};

class FonFileType : public VirtualFile
{
protected:
    void _init();
    unsigned int _numberOfCharacters;
    unsigned int _height;
    unsigned int _distance;
    FonSymbol * _symbols;
public:
    FonFileType(VirtualFile * virtualFile);
    ~FonFileType();
};

}
#endif // FALLTERGEIST_FONFILETYPE_H
