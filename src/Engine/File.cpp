#include "../Engine/File.h"
#include "../Engine/Exception.h"
#include <cstring>
#include <string>

namespace Falltergeist
{

File::File()
{
    _filename = 0;
}

File::File(const char * filename)
{
    setFilename(filename);
}

File::~File()
{
    if (_filename != 0) delete [] _filename;
}

void File::setFilename(const char * filename)
{
    if (_filename != 0) delete [] _filename;
    _filename = new char[strlen(filename) + 1]();
    strcpy(_filename, filename);
    _fstream.open(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!_fstream.is_open())
    {
        std::string message = "Can`t open file: ";
        message.append(_filename);
        throw Exception(message);
    }
}

unsigned int File::getPosition()
{
    return _fstream.tellg();
}

void File::setPosition(unsigned int position)
{
    _fstream.seekg(position, std::ios_base::beg);
}

unsigned int File::getSize()
{
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

void File::readBytes(char * buffer, unsigned int length)
{
    _fstream.readsome(buffer,length);
}

void File::writeBytes(char * buffer, unsigned int length)
{
    _fstream.write(buffer,length);
}

void File::skipBytes(unsigned int length)
{
    setPosition(getPosition() + length);
}

}
