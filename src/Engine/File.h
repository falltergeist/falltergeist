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
