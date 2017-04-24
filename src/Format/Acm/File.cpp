/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for Falltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

// C++ standard includes

// Falltergeist includes
#include "../Acm/File.h"
#include "../Acm/Decoder.h"
#include "../Acm/General.h"
#include "../Acm/Unpacker.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Acm
{

constexpr int HEADER_SIZE = 14;

File::File(Dat::Stream&& stream) : _stream(std::move(stream))
{
    _stream.setPosition(0);
    _stream.setEndianness(ENDIANNESS::LITTLE);
    _samplesReady = 0;

    Header hdr;
    _stream >> hdr.signature;
    _stream >> hdr.samples;
    _stream >> hdr.channels;
    _stream >> hdr.rate;

    int16_t tmpword;
    _stream.readBytes((uint8_t*)&tmpword, 2);
    _subblocks = (int32_t) (tmpword >> 4);
    _levels = (int32_t) (tmpword&15);

    if (hdr.signature != IP_ACM_SIG)
    {
        throw Exception("Not an ACM file - invalid signature");
    }

    _samplesLeft = _samples = hdr.samples;
    _channels = hdr.channels;
    _bitrate = hdr.rate;
    _blockSize = ( 1 << _levels) * _subblocks;

    _block.resize(_blockSize);

    _unpacker = std::make_unique<ValueUnpacker>(_levels, _subblocks, &_stream);
    if (!_unpacker || !_unpacker->init())
    {
        throw Exception("Cannot create or init unpacker");
    }
    _decoder = std::make_unique<Decoder>(_levels);
    if (!_decoder || !_decoder->init())
    {
        throw Exception("Cannot create or init decoder");
    }
}

File::~File()
{
}

void File::rewind()
{
    _stream.setPosition(HEADER_SIZE);
    _samplesReady = 0;
    _samplesLeft = _samples;
    _unpacker->reset();
}

int32_t File::_makeNewSamples()
{
    // TODO: maybe use fixed-size ints in Unpacker?
    if (!_unpacker->getOneBlock(reinterpret_cast<int*>(_block.data())))
    {
        // FIXME: is it an error or the end of the stream?
        return 0;
    }
    // TODO: maybe use fixed-size ints in Decoder?
    _decoder->decodeData(reinterpret_cast<int*>(_block.data()), _subblocks);
    _values = _block.data();
    _samplesReady = ( _blockSize > _samplesLeft) ? _samplesLeft : _blockSize;
    _samplesLeft -= _samplesReady;
    return 1;
}

size_t File::readSamples(uint16_t* buffer, size_t count)
{
    size_t res = 0;
    while (res < count) {
        if (_samplesReady == 0) {
            if (_samplesLeft == 0)
                break;
            if (!_makeNewSamples())
                break;
        }
        *buffer = ( short ) ( (*_values) >> _levels);
        _values++;
        buffer++;
        res += 1;
        _samplesReady--;
    }
    return res;
}

int32_t File::samples() const
{
    return _samples;
}

int32_t File::channels() const
{
    return _channels;
}

int32_t File::bitrate() const
{
    return _bitrate;
}

int32_t File::samplesLeft() const
{
    return _samplesLeft;
}

}
}
}
