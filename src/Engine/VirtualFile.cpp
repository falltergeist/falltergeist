#include "../Engine/VirtualFile.h"
#include <cstring>

#include <iostream>

namespace Falltergeist
{

VirtualFile::VirtualFile()
{
    _byteOrder = ORDER_BIG_ENDIAN;
    _dataSize = 0;
    _position = 0;
    _data = 0;
    _filename = 0;
}

VirtualFile::VirtualFile(const char * filename)
{
    _byteOrder = ORDER_BIG_ENDIAN;
    _dataSize = 0;
    _position = 0;
    _data = 0;
    _filename = 0;
    setFilename(filename);
}

VirtualFile::VirtualFile(char * data, unsigned int dataLength)
{
    _byteOrder = ORDER_BIG_ENDIAN;
    _dataSize = 0;
    _position = 0;
    _data = 0;
    _filename = 0;
    _data = new char[dataLength];
    memcpy(_data, data, dataLength);
}

VirtualFile::VirtualFile(const char * filename, char * data, unsigned int dataLength)
{
    _byteOrder = ORDER_BIG_ENDIAN;
    _dataSize = 0;
    _position = 0;
    _data = 0;
    _filename = 0;
    setFilename(filename);
    _data = new char[dataLength];
    memcpy(_data, data, dataLength);
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

bool VirtualFile::eof()
{
    if (_position == -1)
    {
        return true;
    }
    return false;
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
    if (_position + length > _dataSize)
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

void VirtualFile::setByteOrder(unsigned char byteOrder)
{
    if (byteOrder == ORDER_LITTLE_ENDIAN)
    {
        _byteOrder = ORDER_LITTLE_ENDIAN;
    }
    else
    {
        _byteOrder = ORDER_BIG_ENDIAN;
    }
}

unsigned char VirtualFile::getByteOrder()
{
    return _byteOrder;
}

VirtualFile& VirtualFile::operator >> (unsigned int &value)
{
    if (_position + 4 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (_data[_position + 3] << 24) | (_data[_position + 2] << 16) | (_data[_position + 1] << 8) | _data[_position];
    }
    else
    {
        value =  (_data[_position] << 24) | (_data[_position + 1] << 16) | (_data[_position + 2] << 8) | _data[_position + 3];
    }
    _position += 4;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator >> (int &value)
{
    if (_position + 4 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (_data[_position + 3] << 24) | (_data[_position + 2] << 16) | (_data[_position + 1] << 8) | _data[_position];
    }
    else
    {
        value =  (_data[_position] << 24) | (_data[_position + 1] << 16) | (_data[_position + 2] << 8) | _data[_position + 3];
    }
    _position += 4;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator >> (unsigned short &value)
{
    if (_position + 2 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (_data[_position + 1] << 8) | _data[_position];
    }
    else
    {
        value =  (_data[_position] << 8) | (_data[_position + 1]);
    }
    _position += 2;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator >> (short &value)
{
    if (_position + 2 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (_data[_position + 1] << 8) | _data[_position];
    }
    else
    {
        value =  (_data[_position] << 8) | (_data[_position + 1]);
    }
    _position += 2;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator >> (unsigned char &value)
{
    if (_position + 1 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    value = _data[_position];
    _position += 1;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator >> (char &value)
{
    if (_position + 1 > _dataSize)
    {
        _position = -1;
        return *this;
    }
    value = _data[_position];
    _position += 1;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned int &value)
{
    char * buffer = new char[4];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] = value & 0x000000FF;
        buffer[1] = (value & 0x0000FF00) >> 8;
        buffer[2] = (value & 0x00FF0000) >> 16;
        buffer[3] = (value & 0xFF000000) >> 24;
    }
    else
    {
        buffer[3] = value & 0x000000FF;
        buffer[2] = (value & 0x0000FF00) >> 8;
        buffer[1] = (value & 0x00FF0000) >> 16;
        buffer[0] = (value & 0xFF000000) >> 24;
    }
    writeBytes(buffer, 4);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (int &value)
{
    char * buffer = new char[4];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] = value & 0x000000FF;
        buffer[1] = (value & 0x0000FF00) >> 8;
        buffer[2] = (value & 0x00FF0000) >> 16;
        buffer[3] = (value & 0xFF000000) >> 24;
    }
    else
    {
        buffer[3] = value & 0x000000FF;
        buffer[2] = (value & 0x0000FF00) >> 8;
        buffer[1] = (value & 0x00FF0000) >> 16;
        buffer[0] = (value & 0xFF000000) >> 24;
    }
    writeBytes(buffer, 4);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned short &value)
{
    char * buffer = new char[2];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] =  value & 0x00FF;
        buffer[1] = (value & 0xFF00) >> 8;
    }
    else
    {
        buffer[1] =  value & 0x00FF;
        buffer[0] = (value & 0xFF00) >> 8;
    }
    writeBytes(buffer, 2);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (short &value)
{
    char * buffer = new char[2];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] =  value & 0x00FF;
        buffer[1] = (value & 0xFF00) >> 8;
    }
    else
    {
        buffer[1] =  value & 0x00FF;
        buffer[0] = (value & 0xFF00) >> 8;
    }
    writeBytes(buffer, 2);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned char &value)
{
    char * buffer = new char[1];
    buffer[0] =  value;
    writeBytes(buffer, 1);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (char &value)
{
    char * buffer = new char[1];
    buffer[0] =  value;
    writeBytes(buffer, 1);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned int value)
{
    char * buffer = new char[4];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] = value & 0x000000FF;
        buffer[1] = (value & 0x0000FF00) >> 8;
        buffer[2] = (value & 0x00FF0000) >> 16;
        buffer[3] = (value & 0xFF000000) >> 24;
    }
    else
    {
        buffer[3] = value & 0x000000FF;
        buffer[2] = (value & 0x0000FF00) >> 8;
        buffer[1] = (value & 0x00FF0000) >> 16;
        buffer[0] = (value & 0xFF000000) >> 24;
    }
    writeBytes(buffer, 4);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (int value)
{
    char * buffer = new char[4];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] = value & 0x000000FF;
        buffer[1] = (value & 0x0000FF00) >> 8;
        buffer[2] = (value & 0x00FF0000) >> 16;
        buffer[3] = (value & 0xFF000000) >> 24;
    }
    else
    {
        buffer[3] = value & 0x000000FF;
        buffer[2] = (value & 0x0000FF00) >> 8;
        buffer[1] = (value & 0x00FF0000) >> 16;
        buffer[0] = (value & 0xFF000000) >> 24;
    }
    writeBytes(buffer, 4);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned short value)
{
    char * buffer = new char[2];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] =  value & 0x00FF;
        buffer[1] = (value & 0xFF00) >> 8;
    }
    else
    {
        buffer[1] =  value & 0x00FF;
        buffer[0] = (value & 0xFF00) >> 8;
    }
    writeBytes(buffer, 2);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (short value)
{
    char * buffer = new char[2];
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        buffer[0] =  value & 0x00FF;
        buffer[1] = (value & 0xFF00) >> 8;
    }
    else
    {
        buffer[1] =  value & 0x00FF;
        buffer[0] = (value & 0xFF00) >> 8;
    }
    writeBytes(buffer, 2);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned char value)
{
    char * buffer = new char[1];
    buffer[0] =  value;
    writeBytes(buffer, 1);
    delete [] buffer;
    return *this;
}

VirtualFile& VirtualFile::operator << (char value)
{
    char * buffer = new char[1];
    buffer[0] =  value;
    writeBytes(buffer, 1);
    delete [] buffer;
    return *this;
}


}
