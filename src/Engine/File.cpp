#include "../Engine/File.h"
#include "../Engine/VirtualFile.h"
#include "../Engine/Exception.h"
#include <cstring>
#include <string>
#include <algorithm>

#include <iostream>

namespace Falltergeist
{

File::File()
{
    _virtualFile = 0;
    _filename = 0;
    _byteOrder = ORDER_BIG_ENDIAN;
}

File::File(const char * filename)
{
    _virtualFile = 0;
    _byteOrder = ORDER_BIG_ENDIAN;
    setFilename(filename);
}

File::File(VirtualFile * virtualFile)
{
    _virtualFile = virtualFile;
    _byteOrder = ORDER_BIG_ENDIAN;
    setFilename(_virtualFile->getFilename());
}

File::~File()
{
    if (_fstream.is_open())
    {
        _fstream << std::flush;
        _fstream.close();
    }
    if (_filename != 0) delete [] _filename;

}

void File::setFilename(const char * filename)
{
    if (_filename != 0) delete [] _filename;
    std::string fname(filename);
    std::replace(fname.begin(),fname.end(),'\\','/');
    std::transform(fname.begin(),fname.end(),fname.begin(), ::tolower);

    _filename = new char[strlen(fname.c_str()) + 1]();
    strcpy(_filename, fname.c_str());
}

bool File::open()
{
    if (_fstream.is_open()) return true;
    _fstream.open(getFilename(), std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!_fstream.is_open())
    {
        _fstream.open(getFilename(), std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (!_fstream.is_open())
        {
            return false;
        }
    }
    return true;
}

int File::getPosition()
{
    if (_virtualFile != 0)
    {
        return _virtualFile->getPosition();
    }
    open();
    return _fstream.tellg();
}

void File::setPosition(unsigned int position)
{
    if (_virtualFile != 0)
    {
        _virtualFile->setPosition(position);
        return;
    }
    open();
    _fstream.seekg(position, std::ios_base::beg);
    _fstream.seekp(position, std::ios_base::beg);
}

unsigned int File::getSize()
{
    if (_virtualFile != 0)
    {
        return _virtualFile->getSize();
    }
    open();
    unsigned int oldPosition = getPosition();
    _fstream.seekg(0, std::ios_base::end);
    unsigned int size = _fstream.tellg();
    setPosition(oldPosition);
    return size;
}

const char * File::getFilename()
{
    return _filename;
}

void File::setByteOrder(unsigned char byteOrder)
{
    if (_virtualFile != 0) _virtualFile->setByteOrder(byteOrder);
    if (byteOrder == ORDER_LITTLE_ENDIAN)
    {
        _byteOrder = ORDER_LITTLE_ENDIAN;
    }
    else
    {
        _byteOrder = ORDER_BIG_ENDIAN;
    }
}

unsigned char File::getByteOrder()
{
    if (_virtualFile != 0) return _virtualFile->getByteOrder();
    return _byteOrder;
}

void File::readBytes(char * buffer, unsigned int length)
{
    if (_virtualFile != 0)
    {
        _virtualFile->readBytes(buffer, length);
        return;
    }
    open();
    _fstream.readsome(buffer,length);
    setPosition(_fstream.tellg());
}

void File::writeBytes(char * buffer, unsigned int length)
{
    if (_virtualFile != 0)
    {
        _virtualFile->writeBytes(buffer, length);
        return;
    }
    open();
    _fstream.write(buffer, length);
    setPosition(_fstream.tellp());
}

void File::skipBytes(unsigned int length)
{
    if (_virtualFile != 0)
    {
        _virtualFile->skipBytes(length);
        return;
    }
    setPosition(getPosition() + length);
}

bool File::save()
{
    if (_virtualFile == 0) return false;
    if (!open())
    {
        std::string message = "Save failed. Can't open file: ";
        message.append(getFilename());
        throw Exception(message);
    }
    VirtualFile * virtualFile = _virtualFile;
    _virtualFile = 0;

    setPosition(0);
    virtualFile->setPosition(0);
    writeBytes(virtualFile->getData(), virtualFile->getSize());
    return true;
}

File& File::operator >> (unsigned int &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }
    open();
    unsigned char * data = new unsigned char[4]();
    _fstream.readsome((char *)data, 4);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value = ( data[3] << 24) | (data[2] << 16) | ( data[1] << 8) | data[0];
    }
    else
    {
        value = ( data[0] << 24) | (data[1] << 16) | ( data[2] << 8) | data[3];
    }
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator >> (int &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }

    open();
    unsigned char * data = new unsigned char[4]();
    _fstream.readsome((char *)data, 4);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value = ( data[3] << 24) | (data[2] << 16) | ( data[1] << 8) | data[0];
    }
    else
    {
        value = ( data[0] << 24) | (data[1] << 16) | ( data[2] << 8) | data[3];
    }
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator >> (unsigned short &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }

    open();
    unsigned char * data = new unsigned char[2]();
    _fstream.readsome((char *)data, 2);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value = ( data[1] << 8) | data[0];
    }
    else
    {
        value = ( data[0] << 8) | data[1];
    }
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator >> (short &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }

    open();
    unsigned char * data = new unsigned char[2]();
    _fstream.readsome((char *)data, 2);
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        value = ( data[1] << 8) | data[0];
    }
    else
    {
        value = ( data[0] << 8) | data[1];
    }
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator >> (unsigned char &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }

    open();
    unsigned char * data = new unsigned char[1]();
    _fstream.readsome((char *)data, 1);
    value = data[0];
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator >> (char &value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) >> value;
        return *this;
    }

    open();
    unsigned char * data = new unsigned char[1]();
    _fstream.readsome((char *)data, 1);
    value = data[0];
    delete [] data;
    setPosition(_fstream.tellg());
    return *this;
}

File& File::operator << (unsigned int &value)
{
    (*this) << (unsigned int) value;
    return *this;
}

File& File::operator << (int &value)
{
    (*this) << (int) value;
    return *this;
}

File& File::operator << (unsigned short &value)
{
    (*this) << (unsigned short) value;
    return *this;
}

File& File::operator << (short &value)
{
    (*this) << (short) value;
    return *this;
}

File& File::operator << (unsigned char &value)
{
    (*this) << (unsigned char) value;
    return *this;
}

File& File::operator << (char &value)
{
    (*this) << (char) value;
    return *this;
}

File& File::operator << (unsigned int value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (unsigned int) value;
        return *this;
    }

    open();
    char * data = new char[4]();
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        data[0] = (value&0x000000FF);
        data[1] = (value&0x0000FF00) >> 8;
        data[2] = (value&0x00FF0000) >> 16;
        data[3] = (value&0xFF000000) >> 16;
    }
    else
    {
        data[3] = (value&0x000000FF);
        data[2] = (value&0x0000FF00) >> 8;
        data[1] = (value&0x00FF0000) >> 16;
        data[0] = (value&0xFF000000) >> 16;
    }
    writeBytes(data, 4);
    delete [] data;
    return *this;
}

File& File::operator << (int value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (int) value;
        return *this;
    }

    (*this) << (unsigned int) value;
    return *this;
}

File& File::operator << (unsigned short value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (unsigned short) value;
        return *this;
    }

    open();
    char * data = new char[2]();
    if (_byteOrder == ORDER_LITTLE_ENDIAN)
    {
        data[0] = (value&0x00FF);
        data[1] = (value&0xFF00) >> 8;
    }
    else
    {
        data[1] = (value&0x00FF);
        data[0] = (value&0xFF00) >> 8;
    }
    writeBytes(data, 2);
    delete [] data;
    return *this;
}

File& File::operator << (short value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (short) value;
        return *this;
    }
    (*this) << (unsigned short) value;
    return *this;
}

File& File::operator << (unsigned char value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (unsigned char) value;
        return *this;
    }

    open();
    char * data = new char[1]();
    data[0] = value;
    writeBytes(data, 1);
    delete [] data;
    return *this;
}

File& File::operator << (char value)
{
    if (_virtualFile != 0)
    {
        (*_virtualFile) << (char) value;
        return *this;
    }
    (*this) << (unsigned char) value;
    return *this;
}


}
