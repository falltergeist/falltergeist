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

#ifndef FALLTERGEIST_FORMAT_ACM_FILE_H
#define FALLTERGEIST_FORMAT_ACM_FILE_H

// C++ standard includes
#include <cstdint>

// Falltergeist includes
#include "../../Base/Buffer.h"
#include "../Dat/Item.h"
#include "../Dat/Stream.h"

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
#endif // FALLTERGEIST_FORMAT_ACM_FILE_H
