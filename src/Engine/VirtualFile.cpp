#include "../Engine/VirtualFile.h"
#include <cstring>
#include <iostream>

namespace Falltergeist
{

VirtualFile::VirtualFile()
{
    _dataSize = 0;
    _position = 0;
    _data = 0;
    _filename = 0;
}

VirtualFile::~VirtualFile()
{
    if (_data != 0) delete [] _data;
    if (_filename != 0) delete [] _filename;
}

void VirtualFile::setFilename(const char * filename)
{
    if (_filename != 0) delete [] _filename;
    _filename = new char[strlen(filename) + 1]();
    strcpy(_filename, filename);
}

const char * VirtualFile::getFilename()
{
    return _filename;
}

void VirtualFile::setPosition(unsigned int position)
{
    if (position >= _dataSize)
    {
        _position = -1;
        return;
    }
    _position = position;
}

int VirtualFile::getPosition()
{
    return _position;
}

unsigned int VirtualFile::getSize()
{
    return _dataSize;
}

void VirtualFile::skipBytes(unsigned int length)
{
    if (_position + length >= _dataSize)
    {
        _position = -1;
        return;
    }
    _position += length;
}

void VirtualFile::readBytes(char * buffer, unsigned int length)
{
    if (_position + length >= _dataSize)
    {
        _position = -1;
        return;
    }
    memcpy(buffer, &_data[_position], length);
    _position += length;
}

void VirtualFile::writeBytes(char * buffer, unsigned int length)
{
    if (_position + length >= _dataSize)
    {
        if (_data == 0)
        {
            _data = new char[length];
            _dataSize = length;
        }
        else
        {
            char * newData = new char[_position + length];
            memcpy( newData, _data, _dataSize);
            delete [] _data;
            _dataSize = _position + length;
            _data = newData;
        }
    }
    memcpy(&_data[_position], buffer, length);
    _position += length;
}

char * VirtualFile::getData()
{
    return _data;
}

}
