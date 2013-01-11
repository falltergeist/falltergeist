/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Engine/Exception.h"
#include "../Fallout/DatFile.h"
#include "../Fallout/FrmFileType.h"
#include "../Fallout/PalFileType.h"
#include "../Fallout/LstFileType.h"
#include "../Fallout/FonFileType.h"
#include "../Fallout/AafFileType.h"
#include "../Fallout/GcdFileType.h"
#include "../Fallout/MsgFileType.h"
#include "../Fallout/BioFileType.h"
#include <algorithm>
#include <zlib.h>

namespace Falltergeist
{

DatFile::DatFile(const char * filename) : File(filename)
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
    _byteOrder = ORDER_LITTLE_ENDIAN;
}

DatFile::~DatFile()
{
    delete _items;
    delete _frmFiles, _palFiles, _lstFiles, _fonFiles, _aafFiles, _gcdFiles, _msgFiles, _bioFiles;
}

/**
 * Returns std::list of DAT file items
 * @brief DatFile::getItems
 * @return
 */
std::list<VirtualFile *> * DatFile::getItems()
{
    if (_items != 0) return _items;

    unsigned int datFileSize, dirTreeSize, itemsTotal;

    // 4 bytes Dat file size
    setPosition(getSize() - 4);
    (*this) >> datFileSize;

    // 4 bytes Directory tree size
    setPosition(datFileSize - 8);
    (*this) >> dirTreeSize;

    // 4 bytes Items count in DAT file
    setPosition(datFileSize - dirTreeSize - 8);
    (*this) >> itemsTotal;

    // for each entries...
    _items = new std::list<VirtualFile *>;
    for (unsigned int i = 0; i < itemsTotal; i++)
    {
        VirtualFile * item = new VirtualFile();
        // 4 bytes item name length;
        unsigned int nameLength; (*this) >> nameLength;

        // item name
        char * filename = new char[nameLength + 1]();
        this->readBytes(filename,nameLength);
        item->setFilename(filename);
        delete [] filename;

        // is compressed?
        unsigned char isCompressed;
        (*this) >> isCompressed;

        // unpacked size
        unsigned int unpackedSize;
        (*this) >> unpackedSize;

        // packed size
        unsigned int packedSize;
        (*this) >> packedSize;

        // data offset
        unsigned int dataOffset;
        (*this) >> dataOffset;

        unsigned int oldPosition = getPosition();
        setPosition(dataOffset);
        if (!isCompressed)
        {
            char * unpackedData = new char[packedSize]();
            readBytes(unpackedData, packedSize);
            item->writeBytes(unpackedData,packedSize);
        }
        else
        {
            char * packedData = new char[packedSize]();
            char * unpackedData = new char[unpackedSize]();
            readBytes(packedData, packedSize);

            z_stream zStream;
            zStream.total_in  = zStream.avail_in  = packedSize;
            zStream.avail_in = packedSize;
            zStream.next_in  = (unsigned char *) packedData;
            zStream.total_out = zStream.avail_out = unpackedSize;
            zStream.next_out = (unsigned char *) unpackedData;
            zStream.zalloc = Z_NULL;
            zStream.zfree = Z_NULL;
            zStream.opaque = Z_NULL;

            inflateInit( &zStream );            // zlib function
            inflate( &zStream, Z_FINISH );      // zlib function
            inflateEnd( &zStream );             // zlib function

            item->writeBytes(unpackedData,unpackedSize);
            delete [] packedData;
        }
        setPosition(oldPosition);
        _items->push_back(item);
    }

    return _items;
}


/**
 * Returns single item or null
 * @param std::string filename
 * @return VirtualFile*
 */
VirtualFile * DatFile::getItem(std::string filename)
{
    std::replace(filename.begin(),filename.end(),'\\','/');
    std::transform(filename.begin(),filename.end(),filename.begin(), ::tolower);
    std::list<VirtualFile *>::iterator it;
    for (it = this->getItems()->begin(); it != this->getItems()->end(); ++it)
    {
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
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
    VirtualFile * item = this->getItem(filename);
    if (!item) return 0;

    // create new bio file type
    BioFileType * bio = new BioFileType(item);
    // insert into bio files map
    _bioFiles->insert(std::make_pair(filename,bio));
    return _bioFiles->at(filename);
}


}
