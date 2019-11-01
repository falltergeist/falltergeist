#pragma once

#include <fstream>
#include <string>
#include <memory>
#include "../../Base/Buffer.h"
#include "../../Format/Enums.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Entry;

            // An abstract data stream for binary resource files loaded from either Dat file or a file system
            class Stream: public std::streambuf
            {
                public:
                    Stream(std::ifstream& stream);
                    Stream(Dat::Entry& datFileEntry);

                    Stream(Stream&& other);
                    Stream(const Stream&) = delete;
                    Stream& operator= (Stream&& other);
                    Stream& operator= (const Stream&) = delete;

                    virtual std::streambuf::int_type underflow();

                    Stream& readBytes(uint8_t* destination, size_t size);
                    Stream& skipBytes(size_t numberOfBytes);
                    Stream& setPosition(size_t position);
                    size_t position() const;
                    size_t size() const;

                    size_t bytesRemains();

                    ENDIANNESS endianness();
                    void setEndianness(ENDIANNESS value);

                    uint32_t uint32();
                    int32_t int32();
                    uint16_t uint16();
                    int16_t int16();
                    uint8_t uint8();
                    int8_t int8();

                    Stream& operator>>(uint32_t &value);
                    Stream& operator>>(int32_t &value);
                    Stream& operator>>(uint16_t &value);
                    Stream& operator>>(int16_t &value);
                    Stream& operator>>(uint8_t &value);
                    Stream& operator>>(int8_t &value);

                private:
                    Base::Buffer<char> _buffer;
                    ENDIANNESS _endianness = ENDIANNESS::BIG;
            };
        }
    }
}
