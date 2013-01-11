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

#ifndef FALLTERGEIST_VIRTUALFILE_H
#define FALLTERGEIST_VIRTUALFILE_H

namespace Falltergeist
{

class VirtualFile
{
protected:
    unsigned char _byteOrder;
    unsigned int _dataSize;
    unsigned int _position;
    char * _data;
    char * _filename;

public:
    enum { ORDER_LITTLE_ENDIAN = 0, ORDER_BIG_ENDIAN };
    VirtualFile();
    VirtualFile(VirtualFile * virtualFile);
    VirtualFile(const char * filename);
    VirtualFile(const char * filename, char * data, unsigned int dataLength);
    VirtualFile(char * data, unsigned int dataLength);
    ~VirtualFile();
    virtual unsigned int getSize();
    virtual char * getData();
    virtual void writeBytes(char * buffer, unsigned int length);
    virtual void readBytes(char * buffer, unsigned int length);
    virtual void skipBytes(unsigned int length);
    virtual void setPosition(unsigned int position);
    virtual void setFilename(const char * filename);
    virtual void setByteOrder(unsigned char byteOrder);
    virtual int getPosition();
    virtual unsigned char getByteOrder();
    virtual bool eof();
    virtual const char * getFilename();
    virtual VirtualFile& operator>> (unsigned int &value);
    virtual VirtualFile& operator>> (int &value);
    virtual VirtualFile& operator>> (unsigned short &value);
    virtual VirtualFile& operator>> (short &value);
    virtual VirtualFile& operator>> (unsigned char &value);
    virtual VirtualFile& operator>> (char &value);
    virtual VirtualFile& operator<< (unsigned int &value);
    virtual VirtualFile& operator<< (int &value);
    virtual VirtualFile& operator<< (unsigned short &value);
    virtual VirtualFile& operator<< (short &value);
    virtual VirtualFile& operator<< (unsigned char &value);
    virtual VirtualFile& operator<< (char &value);
    virtual VirtualFile& operator<< (unsigned int value);
    virtual VirtualFile& operator<< (int value);
    virtual VirtualFile& operator<< (unsigned short value);
    virtual VirtualFile& operator<< (short value);
    virtual VirtualFile& operator<< (unsigned char value);
    virtual VirtualFile& operator<< (char value);
};

}
#endif // FALLTERGEIST_VIRTUALFILE_H
