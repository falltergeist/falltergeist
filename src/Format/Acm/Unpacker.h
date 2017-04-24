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

#ifndef FALLTERGEIST_FORMAT_ACM_VALUEUNPACKER_H
#define FALLTERGEIST_FORMAT_ACM_VALUEUNPACKER_H

// C++ standard includes

// Falltergeist includes
#include "../Dat/Item.h"

// Third party includes

#define UNPACKER_BUFFER_SIZE 16384

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Acm
{

class ValueUnpacker
{

public:

    ValueUnpacker(int levCnt, int sbCount, Dat::Stream* stream);
    virtual ~ValueUnpacker();

    // These functions are used to fill the buffer with the amplitude values
    int return0(int pass, int ind);
    int zeroFill(int pass, int ind);
    int linearFill(int pass, int ind);
    int k1_3bits(int pass, int ind);
    int k1_2bits(int pass, int ind);
    int t1_5bits(int pass, int ind);
    int k2_4bits(int pass, int ind);
    int k2_3bits(int pass, int ind);
    int t2_7bits(int pass, int ind);
    int k3_5bits(int pass, int ind);
    int k3_4bits(int pass, int ind);
    int k4_5bits(int pass, int ind);
    int k4_4bits(int pass, int ind);
    int t3_7bits(int pass, int ind);

    int init();
    void reset();
    int getOneBlock(int *block);

protected:
    // Parameters of ACM stream
    int _levels, _subblocks;
    Dat::Stream *stream;
    // Bits
    unsigned int _nextBits; // new bits
    int _availBits; // count of new bits
    unsigned char _bitsBuffer[UNPACKER_BUFFER_SIZE];
    size_t _bufferBitOffset;

    int _sbSize;
    short *_ampBuffer, *_buffMiddle;
    int *_blockPtr;

    // Reading routines
    void _prepareBits(int bits); // request bits
    int _getBits(int bits); // request and return next bits

};

typedef int (ValueUnpacker::*FillerProc)(int pass, int ind);

}
}
}
#endif // FALLTERGEIST_FORMAT_ACM_VALUEUNPACKER_H
