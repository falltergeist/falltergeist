// Project includes
#include "../../Format/Dat/Stream.h"
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"

// Third-party includes
#include "zlib.h"

// stdlib
#include <cstring>
#include <algorithm>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            Stream::Stream(Stream&& other) :
                    _buffer(std::move(other._buffer)),
                    _endianness(other._endianness)
            {
                auto cBuf = _buffer.data();
                setg(cBuf, cBuf, cBuf + _buffer.size());
            }

            Stream& Stream::operator= (Stream&& other)
            {
                _buffer = std::move(other._buffer);
                _endianness = other._endianness;
                auto cBuf = _buffer.data();
                setg(cBuf, cBuf, cBuf + _buffer.size());
                return *this;
            }

            Stream::Stream(std::ifstream& stream)
            {
                stream.seekg(0, std::ios::end);
                auto size = static_cast<size_t>(stream.tellg());
                stream.seekg(0, std::ios::beg);

                _buffer.resize(size);
                auto cBuf = _buffer.data();
                stream.read(cBuf, size);
                setg(cBuf, cBuf, cBuf + size);
            }

            Stream::Stream(Entry& datFileEntry)
            {
                auto size = datFileEntry.unpackedSize();
                _buffer.resize(size);
                auto cBuf = _buffer.data();

                auto datFile = datFileEntry.datFile();
                unsigned int oldPos = datFile->position();
                datFile->setPosition(datFileEntry.dataOffset());

                if (datFileEntry.compressed()) {
                    Base::Buffer<char> packedData(datFileEntry.packedSize());
                    datFile->readBytes(packedData.data(), datFileEntry.packedSize());

                    // unpacking
                    z_stream zStream;
                    zStream.total_in = datFileEntry.packedSize();
                    zStream.avail_in = datFileEntry.packedSize();
                    zStream.next_in = reinterpret_cast<unsigned char*>(packedData.data());
                    zStream.total_out = zStream.avail_out = static_cast<uint32_t>(_buffer.size());
                    zStream.next_out = reinterpret_cast<unsigned char*>(_buffer.data());
                    zStream.zalloc = Z_NULL;
                    zStream.zfree = Z_NULL;
                    zStream.opaque = Z_NULL;
                    inflateInit(&zStream);            // zlib function
                    inflate(&zStream, Z_FINISH);      // zlib function
                    inflateEnd(&zStream);             // zlib function
                } else {
                    datFile->readBytes(cBuf, size);
                }

                datFile->setPosition(oldPos);
                setg(cBuf, cBuf, cBuf + size);
            }

            size_t Stream::size() const
            {
                return _buffer.size();
            }

            std::streambuf::int_type Stream::underflow()
            {
                if (gptr() == egptr())
                {
                    return traits_type::eof();
                }
                return traits_type::to_int_type(*gptr());
            }

            Stream& Stream::setPosition(size_t pos)
            {
                auto cBuf = _buffer.data();
                setg(cBuf, cBuf + pos, cBuf + _buffer.size());
                return *this;
            }

            size_t Stream::position() const
            {
                return gptr() - eback();
            }

            Stream& Stream::skipBytes(size_t numberOfBytes)
            {
                auto cBuf = _buffer.data();
                setg(cBuf, gptr() + numberOfBytes, cBuf + _buffer.size());
                return *this;
            }

            Stream& Stream::readBytes(uint8_t* destination, size_t size)
            {
                sgetn((char*)destination, size);
                return *this;
            }

            Stream& Stream::operator>>(uint32_t &value)
            {
                char* buff = reinterpret_cast<char*>(&value);
                sgetn(buff, sizeof(value));
                if (endianness() == ENDIANNESS::BIG)
                {
                    std::reverse(buff, buff + sizeof(value));
                }
                return *this;
            }

            Stream& Stream::operator>>(int32_t &value)
            {
                return *this >> (uint32_t&) value;
            }

            Stream& Stream::operator>>(uint16_t &value)
            {
                char* buff = reinterpret_cast<char*>(&value);
                sgetn(buff, sizeof(value));
                if (endianness() == ENDIANNESS::BIG)
                {
                    std::reverse(buff, buff + sizeof(value));
                }
                return *this;
            }

            Stream& Stream::operator>>(int16_t &value)
            {
                return *this >> (uint16_t&) value;
            }

            Stream& Stream::operator>>(uint8_t &value)
            {
                sgetn(reinterpret_cast<char*>(&value), sizeof(value));
                return *this;
            }

            Stream& Stream::operator>>(int8_t &value)
            {
                return *this >> (uint8_t&) value;
            }

            ENDIANNESS Stream::endianness()
            {
                return _endianness;
            }

            void Stream::setEndianness(ENDIANNESS value)
            {
                _endianness = value;
            }

            size_t Stream::bytesRemains()
            {
                return size() - position();
            }

            uint32_t Stream::uint32()
            {
                uint32_t value = 0;
                *this >> value;
                return value;
            }

            int32_t Stream::int32()
            {
                return uint32();
            }

            uint16_t Stream::uint16()
            {
                uint16_t value = 0;
                *this >> value;
                return value;
            }

            int16_t Stream::int16()
            {
                return uint16();
            }

            uint8_t Stream::uint8()
            {
                uint8_t value = 0;
                *this >> value;
                return value;
            }

            int8_t Stream::int8()
            {
                return uint8();
            }
        }
    }
}
