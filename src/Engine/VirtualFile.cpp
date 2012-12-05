#include "../Engine/VirtualFile.h"
#include <cstring>
#include <algorithm>

#include <iostream>

namespace Falltergeist
{

VirtualFile::VirtualFile()
{
    _byteOrder = ORDER_BIG_ENDIAN;
    _dataSize = 0;
    _position = 0;
    _filename = 0;
    _data = 0;
}

VirtualFile::VirtualFile(VirtualFile * virtualFile)
{
    _byteOrder = virtualFile->_byteOrder;
    _dataSize= virtualFile->_dataSize;
    _position = virtualFile->_position;
    _filename = virtualFile->_filename;
    _data = virtualFile->_data;
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

    std::string fname(filename);
    std::replace(fname.begin(),fname.end(),'\\','/');
    std::transform(fname.begin(),fname.end(),fname.begin(), ::tolower);

    _filename = new char[strlen(fname.c_str()) + 1]();
    strcpy(_filename, fname.c_str());
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

    unsigned char * data = new unsigned char[4]();
    readBytes((char *)data, 4);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    }
    else
    {
        value =  (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }
    delete [] data;
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

    unsigned char * data = new unsigned char[4]();
    readBytes((char *)data, 4);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    }
    else
    {
        value =  (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }
    delete [] data;
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
    unsigned char * data = new unsigned char[2]();
    readBytes((char *)data, 2);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (data[1] << 8) | data[0];
    }
    else
    {
        value =  (data[0] << 8) | data[1];
    }
    delete [] data;
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
    unsigned char * data = new unsigned char[2]();
    readBytes((char *)data, 2);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value =  (data[1] << 8) | data[0];
    }
    else
    {
        value =  (data[0] << 8) | data[1];
    }
    delete [] data;
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
    unsigned char * data = new unsigned char[1]();
    readBytes((char *)data, 1);
    value =  data[0];
    delete [] data;
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
    unsigned char * data = new unsigned char[1]();
    readBytes((char *)data, 1);
    value =  data[0];
    delete [] data;
    if (_position == _dataSize) _position = -1;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned int &value)
{
    (*this) << (unsigned int) value;
    return *this;
}

VirtualFile& VirtualFile::operator << (int &value)
{
    (*this) << (int) value;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned short &value)
{
    (*this) << (unsigned short) value;
    return *this;
}

VirtualFile& VirtualFile::operator << (short &value)
{
    (*this) << (short) value;
    return *this;
}

VirtualFile& VirtualFile::operator << (unsigned char &value)
{
    (*this) << (unsigned char) value;
    return *this;
}

VirtualFile& VirtualFile::operator << (char &value)
{
    (*this) << (char) value;
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
        buffer[3] =  value & 0x000000FF;
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
    (*this) << (unsigned int) value;
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
    (*this) << (unsigned short) value;
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
    (*this) << (unsigned char) value;
    return *this;
}


}
