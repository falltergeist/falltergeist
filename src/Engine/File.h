#ifndef FALLTERGEIST_FILE_H
#define FALLTERGEIST_FILE_H

#include <fstream>

namespace Falltergeist
{

class File
{
protected:
    char * _filename;
    std::fstream _fstream;
public:
    File();
    File(const char * filename);
    virtual ~File();
    const char * getFilename();
    unsigned int getSize();
    unsigned int getPosition();
    void readBytes(char * buffer, unsigned int length);
    void writeBytes(char * buffer, unsigned int length);
    void skipBytes(unsigned int length);
    void setPosition(unsigned int position);
    void setFilename(const char * filename);
};

}
#endif // FALLTERGEIST_FILE_H
