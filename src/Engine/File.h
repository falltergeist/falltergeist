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

#ifndef FALLTERGEIST_FILE_H
#define FALLTERGEIST_FILE_H

#include <fstream>

namespace Falltergeist
{
class VirtualFile;

class File
{
protected:
    VirtualFile * _virtualFile;
    std::fstream _fstream;
    char * _filename;
    unsigned char _byteOrder;
public:
    enum { ORDER_LITTLE_ENDIAN = 0, ORDER_BIG_ENDIAN };
    File();
    File(VirtualFile * virtualFile);
    File(const char * filename);
    virtual ~File();
    virtual const char * getFilename();
    virtual unsigned int getSize();
    virtual int getPosition();
    virtual void readBytes(char * buffer, unsigned int length);
    virtual void writeBytes(char * buffer, unsigned int length);
    virtual void skipBytes(unsigned int length);
    virtual void setPosition(unsigned int position);
    virtual void setFilename(const char * filename);
    virtual void setByteOrder(unsigned char order);
    virtual unsigned char getByteOrder();
    virtual bool open();
    virtual bool save();
    virtual File& operator>> (unsigned int &value);
    virtual File& operator>> (int &value);
    virtual File& operator>> (unsigned short &value);
    virtual File& operator>> (short &value);
    virtual File& operator>> (unsigned char &value);
    virtual File& operator>> (char &value);
    virtual File& operator<< (unsigned int &value);
    virtual File& operator<< (int &value);
    virtual File& operator<< (unsigned short &value);
    virtual File& operator<< (short &value);
    virtual File& operator<< (unsigned char &value);
    virtual File& operator<< (char &value);
    virtual File& operator<< (unsigned int value);
    virtual File& operator<< (int value);
    virtual File& operator<< (unsigned short value);
    virtual File& operator<< (short value);
    virtual File& operator<< (unsigned char value);
    virtual File& operator<< (char value);

};

}
#endif // FALLTERGEIST_FILE_H
