#pragma once

// Project includes
#include "../../Base/Buffer.h"
#include "../Dat/Item.h"
#include "../Dat/Stream.h"

// Third-party includes

// stdlib
#include <cstdint>

namespace Falltergeist
{
    namespace Format
    {
        namespace Acm
        {
            class Decoder;
            class ValueUnpacker;

            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    ~File();

                    void init();
                    void rewind();

                    int samples() const;
                    int channels() const;
                    int bitrate() const;

                    size_t readSamples(uint16_t* buffer, size_t count);

                    int samplesLeft() const;

                private:
                    Dat::Stream _stream;
                    int _samplesLeft; // count of unread samples
                    int _levels, _subblocks;
                    int _blockSize;
                    Base::Buffer<uint32_t> _block;
                    uint32_t* _values;
                    int _samplesReady;
                    std::unique_ptr<ValueUnpacker> _unpacker; // ACM-stream unpacker
                    std::unique_ptr<Decoder> _decoder; // IP's subband decoder
                    int _samples; // total count of sound samples
                    int _channels;
                    int _bitrate;

                    int _makeNewSamples();
            };
        }
    }
}
