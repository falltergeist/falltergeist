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

#ifndef FALLTERGEIST_FRMFILETYPE_H
#define FALLTERGEIST_FRMFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

struct FrmFrame {
    unsigned short width;
    unsigned short height;
    unsigned int dataSize;
    char * data;
    short offsetX;
    short offsetY;
};

struct FrmDirection {
    short shiftX;
    short shiftY;
    unsigned int dataOffset;
    FrmFrame * frames;
};

class FrmFileType : public VirtualFile
{
protected:
    void _init(); // loads all necessary data
    unsigned int _version; // frm file version
    unsigned short _framesPerSecond;  // frames per second
    unsigned short _framesPerDirection; // frames per each direction
    unsigned short _actionFrame; // number of frame on which action is occurs
    unsigned int _dataSize;
    FrmDirection * _directions;
public:
    FrmFileType(VirtualFile * virtualFile);
    ~FrmFileType();
    unsigned short getFramesPerSecond();
    unsigned short getFramesPerDirection();
    unsigned int getVersion();
    unsigned short getActionFrame();
    char * getData();
    FrmDirection * getDirections();
    void setFramesPerSecond(unsigned short framesNumber);
    void setFramesPerDirection(unsigned short framesNumber);
    void setVersion(unsigned int version);
    void setActionFrame(unsigned short frameNumber);
    void setDirections(FrmDirection * directions);
};

}
#endif // FALLTERGEIST_FRMFILETYPE_H
