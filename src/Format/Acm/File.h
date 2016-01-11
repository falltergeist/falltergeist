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

// Falltergeist includes

#include "../Dat/Item.h"

namespace Falltergeist
{
namespace Format
{
namespace Acm
{

class ValueUnpacker;
class Decoder;

class File : public Dat::Item
{

public:
    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    ~File();
    void init();
    void rewind();

    int samples() const;
    int channels() const;
    int bitrate() const;

    int readSamples(short* buffer, int count);

    int samplesLeft() const;

protected:
    virtual void _initialize();
    int _samplesLeft; // count of unread samples
    int _levels, _subblocks;
    int _blockSize;
    int* _block = nullptr;
    int* _values = nullptr;
    int _samplesReady;
    std::shared_ptr<ValueUnpacker> _unpacker; // ACM-stream unpacker
    std::shared_ptr<Decoder> _decoder; // IP's subband decoder
    int _samples; // total count of sound samples
    int _channels;
    int _bitrate;
    int _makeNewSamples();

};

}
}
}
#endif // FALLTERGEIST_FORMAT_ACM_FILE_H
