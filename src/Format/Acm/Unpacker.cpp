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
#include <cstdio>
#include <cstdlib>

// Falltergeist includes
#include "../../Format/Dat/Stream.h"
#include "Unpacker.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Acm
{

static char Table1[27] = {
        0, 1, 2, 4, 5, 6, 8, 9, 10, 16, 17, 18, 20, 21, 22, 24, 25, 26, 32, 33,
        34, 36, 37, 38, 40, 41, 42
};
// in base-4 system it is:
//		000 001 002  010 011 012  020 021 022
//		100 101 102  110 111 112  120 121 122
//		200 201 202  210 211 212  220 221 222
static short Table2[125] = {
        0, 1, 2, 3, 4, 8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 24, 25, 26, 27, 28,
        32, 33, 34, 35, 36, 64, 65, 66, 67, 68, 72, 73, 74, 75, 76, 80, 81, 82,
        83, 84, 88, 89, 90, 91, 92, 96, 97, 98, 99, 100, 128, 129, 130, 131, 132,
        136, 137, 138, 139, 140, 144, 145, 146, 147, 148, 152, 153, 154, 155, 156,
        160, 161, 162, 163, 164, 192, 193, 194, 195, 196, 200, 201, 202, 203, 204,
        208, 209, 210, 211, 212, 216, 217, 218, 219, 220, 224, 225, 226, 227, 228,
        256, 257, 258, 259, 260, 264, 265, 266, 267, 268, 272, 273, 274, 275, 276,
        280, 281, 282, 283, 284, 288, 289, 290, 291, 292
};
// in base-8 system:
//		000 001 002 003 004  010 011 012 013 014 ...
//		100 101 102 103 104 ...
//		200 ...
//		...
static unsigned char Table3[121] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x20, 0x21,
        0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x30, 0x31, 0x32,
        0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x40, 0x41, 0x42, 0x43,
        0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x50, 0x51, 0x52, 0x53, 0x54,
        0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
        0x66, 0x67, 0x68, 0x69, 0x6A, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
        0x77, 0x78, 0x79, 0x7A, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8A, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
        0x99, 0x9A, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xAA
};

static FillerProc Fillers[32] = {
        &ValueUnpacker::zeroFill, &ValueUnpacker::return0,
        &ValueUnpacker::return0, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::linearFill,
        &ValueUnpacker::linearFill, &ValueUnpacker::k1_3bits,
        &ValueUnpacker::k1_2bits, &ValueUnpacker::t1_5bits,
        &ValueUnpacker::k2_4bits, &ValueUnpacker::k2_3bits,
        &ValueUnpacker::t2_7bits, &ValueUnpacker::k3_5bits,
        &ValueUnpacker::k3_4bits, &ValueUnpacker::return0,
        &ValueUnpacker::k4_5bits, &ValueUnpacker::k4_4bits,
        &ValueUnpacker::return0, &ValueUnpacker::t3_7bits,
        &ValueUnpacker::return0, &ValueUnpacker::return0
};

inline void ValueUnpacker::_prepareBits(int bits)
{
    while (bits > _availBits)
    {
        unsigned char one_byte;
        if (_bufferBitOffset == UNPACKER_BUFFER_SIZE)
        {
            auto remains = stream->bytesRemains();
            if (remains > UNPACKER_BUFFER_SIZE)
                remains = UNPACKER_BUFFER_SIZE;
            _bufferBitOffset = UNPACKER_BUFFER_SIZE - remains;
            if (_bufferBitOffset != UNPACKER_BUFFER_SIZE)
                stream->readBytes((uint8_t*) (_bitsBuffer + _bufferBitOffset), remains);
        }
        //our stream read returns -1 instead of 0 on failure
        //comparing with 1 will solve annoying interface changes
        if (_bufferBitOffset < UNPACKER_BUFFER_SIZE)
        {
            one_byte = _bitsBuffer[_bufferBitOffset];
            _bufferBitOffset++;
        }
        else
        {
            one_byte = 0;
        }
        _nextBits |= ((unsigned int) one_byte << _availBits);
        _availBits += 8;
    }
}

int ValueUnpacker::_getBits(int bits)
{
    _prepareBits(bits);
    int res = _nextBits;
    _availBits -= bits;
    _nextBits >>= bits;
    return res;
}

int ValueUnpacker::init()
{
    //using malloc, supposed to be faster
    _ampBuffer = (short *) malloc(sizeof(short) * 0x10000);
    if (!_ampBuffer)
    {
        return 0;
    }
    _buffMiddle = _ampBuffer + 0x8000;
    return 1;
}

int ValueUnpacker::getOneBlock(int *block)
{
    _blockPtr = block;
    int pwr = _getBits(4) & 0xF, val = _getBits(16) & 0xFFFF,
            count = 1 << pwr, v = 0;
    int i;
    for (i = 0; i < count; i++)
    {
        _buffMiddle[i] = (short) v;
        v += val;
    }
    v = -val;
    for (i = 0; i < count; i++)
    {
        _buffMiddle[-i - 1] = (short) v;
        v -= val;
    }

    for (int pass = 0; pass < _sbSize; pass++)
    {
        int ind = _getBits(5) & 0x1F;
        if (!((this->*Fillers[ind])(pass, ind)))
        {
            return 0;
        }
    }
    return 1;
}


// Filling functions:
// int ValueUnpacker::FillerProc (int pass, int ind)
int ValueUnpacker::return0(int /*pass*/, int /*ind*/)
{
    return 0;
}

int ValueUnpacker::zeroFill(int pass, int /*ind*/)
{
    // used when the whole column #pass is zero-filled
    int *sb_ptr = &_blockPtr[pass], step = _sbSize, i = _subblocks;
    do
    {
        *sb_ptr = 0;
        sb_ptr += step;
    }
    while ((--i) != 0);
    return 1;
}

int ValueUnpacker::linearFill(int pass, int ind)
{
    int mask = (1 << ind) - 1;
    short *lb_ptr = _buffMiddle + ((-1l) << (ind - 1));

    for (int i = 0; i < _subblocks; i++)
        _blockPtr[i * _sbSize + pass] = lb_ptr[_getBits(ind) & mask];
    return 1;
}

int ValueUnpacker::k1_3bits(int pass, int /*ind*/)
{
    // column with number pass is filled with zeros, and also +/-1, zeros are repeated frequently
    // efficiency (bits per value): 3-p0-2.5*p00, p00 - cnt of paired zeros, p0 - cnt of single zeros.
    // it makes sense to use, when the freqnecy of paired zeros (p00) is greater than 2/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(3);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
            if ((++i) == _subblocks)
                break;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
            if ((_nextBits & 2) == 0)
            {
                _availBits -= 2;
                _nextBits >>= 2;
                _blockPtr[i * _sbSize + pass] = 0;
            }
            else
            {
                _blockPtr[i * _sbSize + pass] = (_nextBits & 4) ?
                        _buffMiddle[1] :
                        _buffMiddle[-1];
                _availBits -= 3;
                _nextBits >>= 3;
            }
    }
    return 1;
}

int ValueUnpacker::k1_2bits(int pass, int /*ind*/)
{
    // column is filled with zero and +/-1
    // efficiency: 2-P0. P0 - cnt of any zero (P0 = p0 + p00)
    // use it when P0 > 1/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(2);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
        {
            _blockPtr[i * _sbSize + pass] = (_nextBits & 2) ?
                    _buffMiddle[1] :
                    _buffMiddle[-1];
            _availBits -= 2;
            _nextBits >>= 2;
        }
    }
    return 1;
}

int ValueUnpacker::t1_5bits(int pass, int /*ind*/)
{
    // all the -1, 0, +1 triplets
    // efficiency: always 5/3 bits per value
    // use it when P0 <= 1/3
    for (int i = 0; i < _subblocks; i++)
    {
        int bits = (int) (_getBits(5) & 0x1f);
        bits = (int) Table1[bits];

        _blockPtr[i * _sbSize + pass] = _buffMiddle[-1 + (bits & 3)];
        if ((++i) == _subblocks)
            break;
        bits >>= 2;
        _blockPtr[i * _sbSize + pass] = _buffMiddle[-1 + (bits & 3)];
        if ((++i) == _subblocks)
            break;
        bits >>= 2;
        _blockPtr[i * _sbSize + pass] = _buffMiddle[-1 + bits];
    }
    return 1;
}

int ValueUnpacker::k2_4bits(int pass, int /*ind*/)
{
    // -2, -1, 0, 1, 2, and repeating zeros
    // efficiency: 4-2*p0-3.5*p00, p00 - cnt of paired zeros, p0 - cnt of single zeros.
    //  makes sense to use when p00>2/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(4);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
            if ((++i) == _subblocks)
                break;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
            if ((_nextBits & 2) == 0)
            {
                _availBits -= 2;
                _nextBits >>= 2;
                _blockPtr[i * _sbSize + pass] = 0;
            }
            else
            {
                _blockPtr[i * _sbSize + pass] = (_nextBits & 8) ?
                        ((_nextBits & 4) ? _buffMiddle[2] : _buffMiddle[1]) :
                        ((_nextBits & 4) ? _buffMiddle[-1] : _buffMiddle[-2]);
                _availBits -= 4;
                _nextBits >>= 4;
            }
    }
    return 1;
}

int ValueUnpacker::k2_3bits(int pass, int /*ind*/)
{
    // -2, -1, 0, 1, 2
    // efficiency: 3-2*P0, P0 - cnt of any zero (P0 = p0 + p00)
    // use when P0>1/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(3);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
        {
            _blockPtr[i * _sbSize + pass] = (_nextBits & 4) ?
                    ((_nextBits & 2) ? _buffMiddle[2] : _buffMiddle[1]) :
                    ((_nextBits & 2) ? _buffMiddle[-1] : _buffMiddle[-2]);
            _availBits -= 3;
            _nextBits >>= 3;
        }
    }
    return 1;
}

int ValueUnpacker::t2_7bits(int pass, int /*ind*/)
{
    // all the +/-2, +/-1, 0  triplets
    // efficiency: always 7/3 bits per value
    // use it when p0 <= 1/3
    for (int i = 0; i < _subblocks; i++)
    {
        int bits = (int) (_getBits(7) & 0x7f);
        short val = Table2[bits];

        _blockPtr[i * _sbSize + pass] = _buffMiddle[-2 + (val & 7)];
        if ((++i) == _subblocks)
            break;
        val >>= 3;
        _blockPtr[i * _sbSize + pass] = _buffMiddle[-2 + (val & 7)];
        if ((++i) == _subblocks)
            break;
        val >>= 3;
        _blockPtr[i * _sbSize + pass] = _buffMiddle[-2 + val];
    }
    return 1;
}

int ValueUnpacker::k3_5bits(int pass, int /*ind*/)
{
    // fills with values: -3, -2, -1, 0, 1, 2, 3, and double zeros
    // efficiency: 5-3*p0-4.5*p00-p1, p00 - cnt of paired zeros, p0 - cnt of single zeros, p1 - cnt of +/- 1.
    // can be used when frequency of paired zeros (p00) is greater than 2/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(5);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
            if ((++i) == _subblocks)
                break;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
            if ((_nextBits & 2) == 0)
            {
                _availBits -= 2;
                _nextBits >>= 2;
                _blockPtr[i * _sbSize + pass] = 0;
            }
            else
                if ((_nextBits & 4) == 0)
                {
                    _blockPtr[i * _sbSize + pass] = (_nextBits & 8) ?
                            _buffMiddle[1] :
                            _buffMiddle[-1];
                    _availBits -= 4;
                    _nextBits >>= 4;
                }
                else
                {
                    _availBits -= 5;
                    int val = (_nextBits & 0x18) >> 3;
                    _nextBits >>= 5;
                    if (val >= 2)
                        val += 3;
                    _blockPtr[i * _sbSize + pass] = _buffMiddle[-3 + val];
                }
    }
    return 1;
}

int ValueUnpacker::k3_4bits(int pass, int /*ind*/)
{
    // fills with values: -3, -2, -1, 0, 1, 2, 3.
    // efficiency: 4-3*P0-p1, P0 - cnt of all zeros (P0 = p0 + p00), p1 - cnt of +/- 1.
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(4);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
            if ((_nextBits & 2) == 0)
            {
                _availBits -= 3;
                _blockPtr[i * _sbSize + pass] = (_nextBits & 4) ?
                        _buffMiddle[1] :
                        _buffMiddle[-1];
                _nextBits >>= 3;
            }
            else
            {
                int val = (_nextBits & 0xC) >> 2;
                _availBits -= 4;
                _nextBits >>= 4;
                if (val >= 2)
                    val += 3;
                _blockPtr[i * _sbSize + pass] = _buffMiddle[-3 + val];
            }
    }
    return 1;
}

int ValueUnpacker::k4_5bits(int pass, int /*ind*/)
{
    // fills with values: +/-4, +/-3, +/-2, +/-1, 0, and double zeros
    // efficiency: 5-3*p0-4.5*p00, p00 - cnt of paired zeros, p0 - cnt of single zeros.
    // makes sense to use when p00>2/3
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(5);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
            if ((++i) == _subblocks)
                break;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
            if ((_nextBits & 2) == 0)
            {
                _availBits -= 2;
                _nextBits >>= 2;
                _blockPtr[i * _sbSize + pass] = 0;
            }
            else
            {
                int val = (_nextBits & 0x1C) >> 2;
                if (val >= 4)
                    val++;
                _blockPtr[i * _sbSize + pass] = _buffMiddle[-4 + val];
                _availBits -= 5;
                _nextBits >>= 5;
            }
    }
    return 1;
}

int ValueUnpacker::k4_4bits(int pass, int /*ind*/)
{
    // fills with values: +/-4, +/-3, +/-2, +/-1, 0, and double zeros
    // efficiency: 4-3*P0, P0 - cnt of all zeros (both single and paired).
    for (int i = 0; i < _subblocks; i++)
    {
        _prepareBits(4);
        if ((_nextBits & 1) == 0)
        {
            _availBits--;
            _nextBits >>= 1;
            _blockPtr[i * _sbSize + pass] = 0;
        }
        else
        {
            int val = (_nextBits & 0xE) >> 1;
            _availBits -= 4;
            _nextBits >>= 4;
            if (val >= 4)
                val++;
            _blockPtr[i * _sbSize + pass] = _buffMiddle[-4 + val];
        }
    }
    return 1;
}

int ValueUnpacker::t3_7bits(int pass, int /*ind*/)
{
    // all the pairs of values from -5 to +5
    // efficiency: 7/2 bits per value
    for (int i = 0; i < _subblocks; i++)
    {
        int bits = (int) (_getBits(7) & 0x7f);
        unsigned char val = Table3[bits];

        _blockPtr[i * _sbSize + pass] = _buffMiddle[-5 + (val & 0xF)];
        if ((++i) == _subblocks)
            break;
        val >>= 4;
        _blockPtr[i * _sbSize + pass] = _buffMiddle[-5 + val];
    }
    return 1;
}

ValueUnpacker::ValueUnpacker(int levCnt, int sbCount, Dat::Stream *stream)
{
    _levels = levCnt;
    _subblocks = sbCount;
    _nextBits = 0;
    _availBits = 0;
    _bufferBitOffset = UNPACKER_BUFFER_SIZE;
    _sbSize = 1 << _levels;
    _ampBuffer = nullptr;
    _buffMiddle = nullptr;
    _blockPtr = nullptr;
    this->stream = stream;
}

ValueUnpacker::~ValueUnpacker()
{
    if (_ampBuffer)
    {
        free(_ampBuffer);
        _ampBuffer = nullptr;
    }
}

void ValueUnpacker::reset()
{
    _nextBits = 0;
    _availBits = 0;
    _bufferBitOffset = UNPACKER_BUFFER_SIZE;
    _buffMiddle = _ampBuffer + 0x8000;
    _blockPtr = nullptr;
}

}
}
}
