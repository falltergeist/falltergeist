#ifndef FALLTERGEIST_VIRTUALFILE_H
#define FALLTERGEIST_VIRTUALFILE_H

namespace Falltergeist
{

class VirtualFile
{
protected:
    unsigned int _dataSize;
    unsigned int _position;
    char * _data;
    char * _filename;
public:
    VirtualFile();
    VirtualFile(const char * filename);
    VirtualFile(const char * filename, char * data, unsigned int dataLength);
    VirtualFile(char * data, unsigned int dataLength);
    ~VirtualFile();
    unsigned int getSize();
    char * getData();
    void writeBytes(char * buffer, unsigned int length);
    void readBytes(char * buffer, unsigned int length);
    void skipBytes(unsigned int length);
    void setPosition(unsigned int position);
    void setFilename(const char * filename);
    int getPosition();
    const char * getFilename();
};

}
#endif // FALLTERGEIST_VIRTUALFILE_H
