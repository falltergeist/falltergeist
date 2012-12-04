#ifndef FALLTERGEIST_DATFILEITEM_H
#define FALLTERGEIST_DATFILEITEM_H

#include <string>

namespace Falltergeist
{
class DatFile;

class DatFileItem
{
protected:
    unsigned char * _data;
    unsigned int _dataPosition;
    bool _initialized;
    void _init();
    DatFile * _datFile;
    std::string _filename;
    bool _isCompressed;
    unsigned int _unpackedSize;
    unsigned int _packedSize;
    unsigned int _dataOffset;

public:
    DatFileItem(DatFile * datFile);
    DatFileItem(std::string filename, DatFile * datFile);
    ~ DatFileItem();
    std::string getFilename();
    void setFilename(std::string filename);
    void setUnpackedSize(unsigned int size);
    void setPackedSize(unsigned int size);
    void setDataOffset(unsigned int offset);
    void isCompressed(bool isCompressed);
    unsigned int getPackedSize();
    unsigned int getDataOffset();
    bool isCompressed();
    unsigned char * getData();
    unsigned int size();
    unsigned int pos();
    void skip(unsigned int numberOfBytes);
    void seek(unsigned int pos);
    DatFileItem& operator>> (unsigned int &value);
    DatFileItem& operator>> (int &value);
    DatFileItem& operator>> (unsigned short &value);
    DatFileItem& operator>> (short &value);
    DatFileItem& operator>> (unsigned char &value);
    DatFileItem& operator>> (char &value);
};

}
#endif // FALLTERGEIST_DATFILEITEM_H
