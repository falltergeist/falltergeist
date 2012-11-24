#include "DatFile.h"
#include "DatFileItem.h"
#include "Exception.h"
#include <algorithm>
#include "Fallout/FrmFileType.h"

namespace Falltergeist
{

DatFile::DatFile(std::string filename)
{
    _filename = filename;
    _stream = new std::fstream(filename.c_str(),std::ios::in|std::ios::binary);
    if (!_stream->is_open())
    {
        std::string message = "Can't open DAT file: ";
        message.append(filename);
        throw Exception(message);
    }

}

DatFile::~DatFile()
{
    delete _stream;
}

std::fstream * DatFile::getStream()
{
    return _stream;
}

std::list<DatFileItem*> * DatFile::getItems()
{
    if (_items != 0) return _items;

    unsigned int datFileSize, dirTreeSize, itemsTotal;
    // 4 bytes Dat file size
    this->seek(this->size() - 4);
    (*this) >> datFileSize;

    // 4 bytes Directory tree size
    this->seek(this->size() - 8);
    (*this) >> dirTreeSize;

    // 4 bytes Items count in DAT file
    this->seek(this->size() - dirTreeSize - 8);
    (*this) >> itemsTotal;

    // for each entries...
    _items = new std::list<DatFileItem*>;
    for (unsigned int i = 0; i < itemsTotal; i++)
    {
        DatFileItem * item = new DatFileItem(this);
        (*this) >> *item;
        //std::cout << item.filename << std::endl;
        _items->push_back(item);
    }

    return _items;
}


unsigned int DatFile::size()
{
    unsigned int begin, end, currentPosition, size;
    currentPosition = _stream->tellg();
    _stream->seekg(0,std::ios::beg);
    begin = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    end = _stream->tellg();
    size = end - begin;
    _stream->seekg(currentPosition,std::ios::beg);
    return size;
}


DatFile& DatFile::operator >> (unsigned int &value)
{
    unsigned char byte1,byte2,byte3,byte4;
    _stream->read((char *)&byte1,1);
    _stream->read((char *)&byte2,1);
    _stream->read((char *)&byte3,1);
    _stream->read((char *)&byte4,1);
    value =  (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
    return *this;
}

DatFile& DatFile::operator >> (int &value)
{
    unsigned char byte1,byte2,byte3,byte4;
    _stream->read((char *)&byte1,1);
    _stream->read((char *)&byte2,1);
    _stream->read((char *)&byte3,1);
    _stream->read((char *)&byte4,1);
    value =  (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
    return *this;
}

DatFile& DatFile::operator >> (unsigned char &value)
{
    unsigned char byte1;
    _stream->read((char *)&byte1,1);
    value =  byte1;
    return *this;
}

DatFile& DatFile::operator >> (char &value)
{
    char byte1;
    _stream->read((char *)&byte1,1);
    value =  byte1;
    return *this;
}

DatFile& DatFile::operator >> (DatFileItem &item)
{
    // 4 bytes item name length;
    unsigned int nameLength;
    (*this) >> nameLength;

    // item name
    char * buffer = new char[nameLength + 1]();
    _stream->read(buffer,nameLength);
    std::string itemName(buffer);
    delete [] buffer;
    item.setFilename(itemName);

    // is compressed?
    unsigned char isCompressed;
    (*this) >> isCompressed;
    item.isCompressed((bool) isCompressed);

    // unpacked size
    unsigned int unpackedSize;
    (*this) >> unpackedSize;
    item.setUnpackedSize(unpackedSize);

    // packed size
    unsigned int packedSize;
    (*this) >> packedSize;
    item.setPackedSize(packedSize);

    // data offset
    unsigned int dataOffset;
    (*this) >> dataOffset;
    item.setDataOffset(dataOffset);

    return *this;
}

unsigned int DatFile::pos()
{
    return (unsigned int) _stream->tellg();
}

DatFile& DatFile::seek(unsigned int uint)
{
    _stream->seekg(uint,std::ios::beg);
    return *this;
}

/**
 * Returns single item or null
 * @param std::string filename
 * @return DatFileItem*
 */
DatFileItem * DatFile::getItem(std::string filename)
{
    std::replace(filename.begin(),filename.end(),'\\','/');
    std::transform(filename.begin(),filename.end(),filename.begin(), ::tolower);
    std::list<DatFileItem*>::iterator it;
    for (it = this->getItems()->begin(); it != this->getItems()->end(); ++it)
    {
        //std::cout << (*it)->getFilename() << " : " << (*it)->getDataOffset() <<  std::endl;
        if ((*it)->getFilename() == filename)
        {
            return *it;
        }
    }
    return 0;
}

FrmFileType * DatFile::getFrmFileType(std::string filename)
{
    FrmFileType * frm = new FrmFileType(filename, this);
    return frm;
}


}
