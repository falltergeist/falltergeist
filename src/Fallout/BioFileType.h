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

#ifndef FALLTERGEIST_BIOFILETYPE_H
#define FALLTERGEIST_BIOFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

class BioFileType : public VirtualFile
{
protected:
    void _init();
public:
    BioFileType(VirtualFile * virtualFile);
    ~BioFileType();
    char * getText();
};

}
#endif // FALLTERGEIST_BIOFILETYPE_H
