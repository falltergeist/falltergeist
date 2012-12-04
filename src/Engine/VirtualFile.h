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
    void setByteOrder(unsigned char byteOrder);
    int getPosition();
    bool eof();
    const char * getFilename();
    VirtualFile& operator>> (unsigned int &value);
    VirtualFile& operator>> (int &value);
    VirtualFile& operator>> (unsigned short &value);
    VirtualFile& operator>> (short &value);
    VirtualFile& operator>> (unsigned char &value);
    VirtualFile& operator>> (char &value);
    VirtualFile& operator<< (unsigned int &value);
    VirtualFile& operator<< (int &value);
    VirtualFile& operator<< (unsigned short &value);
    VirtualFile& operator<< (short &value);
    VirtualFile& operator<< (unsigned char &value);
    VirtualFile& operator<< (char &value);
};

}
#endif // FALLTERGEIST_VIRTUALFILE_H
