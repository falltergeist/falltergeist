#include "src/Fallout/DatFile.h"
#include "src/Fallout/DatFileItem.h"
#include "src/Engine/Exception.h"
#include <algorithm>
#include "src/Fallout/FrmFileType.h"
#include "src/Fallout/PalFileType.h"
#include "src/Fallout/LstFileType.h"
#include "src/Fallout/FonFileType.h"
#include "src/Fallout/AafFileType.h"
#include "src/Fallout/GcdFileType.h"
#include "src/Fallout/MsgFileType.h"
#include "src/Fallout/BioFileType.h"

namespace Falltergeist
{

DatFile::DatFile(std::string filename)
{
    _items = 0;
    _frmFiles = new std::map<std::string, FrmFileType *>;
    _palFiles = new std::map<std::string, PalFileType *>;
    _lstFiles = new std::map<std::string, LstFileType *>;
    _fonFiles = new std::map<std::string, FonFileType *>;
    _aafFiles = new std::map<std::string, AafFileType *>;
    _gcdFiles = new std::map<std::string, GcdFileType *>;
    _msgFiles = new std::map<std::string, MsgFileType *>;
    _bioFiles = new std::map<std::string, BioFileType *>;
    _filename = filename;
    _stream = new std::fstream(_filename.c_str(),std::ios::in|std::ios::binary);
    if (!_stream->is_open())
    {
        std::string message = "Can't open DAT file: ";
        message.append(_filename);
        throw Exception(message);
    }
}

DatFile::~DatFile()
{
    delete _stream; _stream = 0;
}

/**
 * Returns DAT file stream
 * @brief DatFile::getStream
 * @return
 */
std::fstream * DatFile::getStream()
{
    return _stream;
}

/**
 * Sets DAT file stream
 * @brief DatFile::setStream
 * @param stream
 */
void DatFile::setStream(std::fstream * stream)
{
    delete _stream;
    _stream = stream;
}

/**
 * Returns std::list of DAT file items
 * @brief DatFile::getItems
 * @return
 */
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

/**
 * Returns size file
 * @brief DatFile::size
 * @return
 */
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

/**
 * Returns FrmFileType object
 * @brief DatFile::getFrmFileType
 * @param filename
 * @return
 */
FrmFileType * DatFile::getFrmFileType(std::string filename)
{
    // if frm file already loaded
    if (_frmFiles->count(filename))
    {
        return _frmFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new frm file type
    FrmFileType * frm = new FrmFileType(item);
    // insert into frm files map
    _frmFiles->insert(std::make_pair(filename,frm));
    return frm;
}

/**
 * Returns PalFileType object
 * @brief DatFile::getPalFileType
 * @param filename
 * @return
 */
PalFileType * DatFile::getPalFileType(std::string filename)
{
    // if pal file already loaded
    if (_palFiles->count(filename))
    {
        return _palFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new pal file type
    PalFileType * pal = new PalFileType(item);
    // insert into pal files map
    _palFiles->insert(std::make_pair(filename,pal));
    return pal;
}

/**
 * Returns LstFileType object
 * @brief DatFile::getLstFileType
 * @param filename
 * @return
 */
LstFileType * DatFile::getLstFileType(std::string filename)
{
    // if lst file already loaded
    if (_lstFiles->count(filename))
    {
        return _lstFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new lst file type
    LstFileType * lst = new LstFileType(item);
    // insert into lst files map
    _lstFiles->insert(std::make_pair(filename,lst));
    return lst;
}

/**
 * Returns FonFileType object
 * @brief DatFile::getFonFileType
 * @param filename
 * @return
 */
FonFileType * DatFile::getFonFileType(std::string filename)
{
    // if fon file already loaded
    if (_fonFiles->count(filename))
    {
        return _fonFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new fon file type
    FonFileType * fon = new FonFileType(item);
    // insert into fon files map
    _fonFiles->insert(std::make_pair(filename,fon));
    return fon;
}

/**
 * Returns AafFileType object
 * @brief DatFile::getAafFileType
 * @param filename
 * @return
 */
AafFileType * DatFile::getAafFileType(std::string filename)
{
    // if aaf file already loaded
    if (_aafFiles->count(filename))
    {
        return _aafFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new aaf file type
    AafFileType * aaf = new AafFileType(item);
    // insert into aaf files map
    _aafFiles->insert(std::make_pair(filename,aaf));
    return aaf;
}

/**
 * Returns GcdFileType object
 * @brief DatFile::getGcdFileType
 * @param filename
 * @return
 */
GcdFileType * DatFile::getGcdFileType(std::string filename)
{
    // if gcd file already loaded
    if (_gcdFiles->count(filename))
    {
        return _gcdFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new gcd file type
    GcdFileType * gcd = new GcdFileType(item);
    // insert into gcd files map
    _gcdFiles->insert(std::make_pair(filename,gcd));
    return gcd;
}

/**
 * Returns MsgFileType object
 * @brief DatFile::getMsgFileType
 * @param filename
 * @return
 */
MsgFileType * DatFile::getMsgFileType(std::string filename)
{
    // if msg file already loaded
    if (_msgFiles->count(filename))
    {
        return _msgFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new msg file type
    MsgFileType * msg = new MsgFileType(item);
    // insert into msg files map
    _msgFiles->insert(std::make_pair(filename,msg));
    return msg;
}

/**
 * Returns BioFileType object
 * @brief DatFile::getBioFileType
 * @param filename
 * @return
 */
BioFileType * DatFile::getBioFileType(std::string filename)
{
    // if bio file already loaded
    if (_bioFiles->count(filename))
    {
        return _bioFiles->at(filename);
    }

    // seek for filename
    DatFileItem * item = this->getItem(filename);
    if (!item) return 0;

    // create new bio file type
    BioFileType * bio = new BioFileType(item);
    // insert into bio files map
    _bioFiles->insert(std::make_pair(filename,bio));
    return _bioFiles->at(filename);
}


}
