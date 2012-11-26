#include "Fallout/DatFileItem.h"
#include "Fallout/DatFile.h"
#include "zlib.h"
#include <algorithm>

namespace Falltergeist
{

DatFileItem::DatFileItem(DatFile * datFile)
{
    _data = 0;
    _dataPosition = 0;
    _datFile = datFile;
    _initialized = false;
}

DatFileItem::~DatFileItem()
{
    if (_initialized) delete _data;
}

void DatFileItem::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

void DatFileItem::setFilename(std::string filename)
{
    _filename = filename;
    std::replace(_filename.begin(),_filename.end(),'\\','/');
    std::transform(_filename.begin(),_filename.end(),_filename.begin(), ::tolower);
}

void DatFileItem::setPackedSize(unsigned int size)
{
    _packedSize = size;
}

void DatFileItem::setUnpackedSize(unsigned int size)
{
    _unpackedSize = size;
}

std::string DatFileItem::getFilename()
{
    return _filename;
}

unsigned int DatFileItem::getDataOffset()
{
    return _dataOffset;
}

unsigned int DatFileItem::getPackedSize()
{
    return _packedSize;
}

/**
 * Returns unpacked size of the item
 * @brief DatFileItem::size
 * @return
 */
unsigned int DatFileItem::size()
{
    return _unpackedSize;
}

void DatFileItem::isCompressed(bool isCompressed)
{
    _isCompressed = isCompressed;
}

bool DatFileItem::isCompressed()
{
    return _isCompressed;
}

void DatFileItem::_init()
{
    if (_initialized) return;
    std::fstream * stream = _datFile->getStream();
    // unpacked data buffer
    _data = new unsigned char[this->size()]();
    _datFile->seek(getDataOffset());

    if (!isCompressed())
    {
        stream->read((char * )_data, this->size());
        _initialized = true;
        return;
    }

    // packed data buffer
    unsigned char * packed = new unsigned char[getPackedSize()];
    stream->read((char *) packed, getPackedSize());

    z_stream zStream;
    zStream.total_in  = zStream.avail_in  = getPackedSize();
    zStream.avail_in = getPackedSize();
    zStream.next_in  = packed;
    zStream.total_out = zStream.avail_out = this->size();
    zStream.next_out = _data;
    zStream.zalloc = Z_NULL;
    zStream.zfree = Z_NULL;
    zStream.opaque = Z_NULL;

    inflateInit( &zStream );            // zlib function
    inflate( &zStream, Z_FINISH );      // zlib function
    inflateEnd( &zStream );             // zlib function
    _initialized = true;
    delete [] packed;
}

unsigned char * DatFileItem::getData()
{
    if (_initialized) return _data;
    _init();
    return _data;
}

unsigned int DatFileItem::pos()
{
    return _dataPosition;
}

void DatFileItem::seek(unsigned int pos)
{
    _dataPosition = pos;
}

void DatFileItem::skip(unsigned int numberOfBytes)
{
    _dataPosition += numberOfBytes;
}

DatFileItem& DatFileItem::operator >>(unsigned char& value)
{
    _init();
    value = (unsigned char) _data[_dataPosition];
    _dataPosition++;
    return *this;
}

DatFileItem& DatFileItem::operator >>(char& value)
{
    _init();
    value = (char) _data[_dataPosition];
    _dataPosition++;
    return *this;
}

DatFileItem& DatFileItem::operator >>(unsigned short& value)
{
    _init();
    value = (unsigned short) ((_data[_dataPosition] << 8) | _data[_dataPosition + 1]);
    _dataPosition += 2;
    return *this;
}

DatFileItem& DatFileItem::operator >>(short& value)
{
    _init();
    value = (short) ((_data[_dataPosition] << 8) | _data[_dataPosition + 1]);
    _dataPosition += 2;
    return *this;
}

DatFileItem& DatFileItem::operator >>(unsigned int& value)
{
    _init();
    value = (_data[_dataPosition] << 24) | (_data[_dataPosition+1] << 16) | (_data[_dataPosition+2] << 8) | _data[_dataPosition + 3];
    _dataPosition += 4;
    return *this;
}

DatFileItem& DatFileItem::operator >>(int& value)
{
    _init();
    value = (_data[_dataPosition] << 24) | (_data[_dataPosition+1] << 16) | (_data[_dataPosition+2] << 8) | _data[_dataPosition + 3];
    _dataPosition += 4;
    return *this;
}


}


