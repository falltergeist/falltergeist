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
// and then adapted for libfalltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

// C++ standard includes
#include <cstdlib>

// libfalltergeist includes
#include "../Acm/Decoder.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Acm
{

int Decoder::init()
{
    int memory_size = (_levels == 0) ? 0 : (3 * (_blockSize >> 1) - 2);
    if (memory_size)
    {
        _memoryBuffer = (int *) calloc(memory_size, sizeof(int));
        if (!_memoryBuffer)
            return 0;
    }
    return 1;
}

void Decoder::decodeData(int *buffer, int blocks)
{
    if (!_levels)
    {
        return;
    } // no levels - no work

    int *buffPtr = buffer, *memPtr = _memoryBuffer;
    int sbSize = _blockSize >> 1; // current subband size

    blocks <<= 1;
    _sub4d3fcc((short *) memPtr, buffPtr, sbSize, blocks);
    memPtr += sbSize;

    for (int i = 0; i < blocks; i++)
        buffPtr[i * sbSize]++;

    sbSize >>= 1;
    blocks <<= 1;

    while (sbSize != 0)
    {
        _sub4d420c(memPtr, buffPtr, sbSize, blocks);
        memPtr += sbSize << 1;
        sbSize >>= 1;
        blocks <<= 1;
    }
}

void Decoder::_sub4d3fcc(short *memory, int *buffer, int sbSize,
        int blocks)
{
    int row0, row1, row2 = 0, row3 = 0, db0, db1;
    int i;
    int sbSize2 = sbSize * 2, sbSize3 = sbSize * 3;
    if (blocks == 2)
    {
        for (i = 0; i < sbSize; i++)
        {
            row0 = buffer[0];
            row1 = buffer[sbSize];
            buffer[0] = buffer[0] + memory[0] + 2 * memory[1];
            buffer[sbSize] = 2 * row0 - memory[1] - buffer[sbSize];
            memory[0] = (short) row0;
            memory[1] = (short) row1;

            memory += 2;
            buffer++;
        }
    }
    else
        if (blocks == 4)
        {
            for (i = 0; i < sbSize; i++)
            {
                row0 = buffer[0];
                row1 = buffer[sbSize];
                row2 = buffer[sbSize2];
                row3 = buffer[sbSize3];

                buffer[0] = memory[0] + 2 * memory[1] + row0;
                buffer[sbSize] = -memory[1] + 2 * row0 - row1;
                buffer[sbSize2] = row0 + 2 * row1 + row2;
                buffer[sbSize3] = -row1 + 2 * row2 - row3;

                memory[0] = (short) row2;
                memory[1] = (short) row3;

                memory += 2;
                buffer++;
            }
        }
        else
        {
            for (i = 0; i < sbSize; i++)
            {
                int *buffPtr = buffer;
                if ((blocks >> 1) & 1)
                {
                    row0 = buffPtr[0];
                    row1 = buffPtr[sbSize];

                    buffPtr[0] = memory[0] + 2 * memory[1] + row0;
                    buffPtr[sbSize] = -memory[1] + 2 * row0 - row1;
                    buffPtr += sbSize2;

                    db0 = row0;
                    db1 = row1;
                }
                else
                {
                    db0 = memory[0];
                    db1 = memory[1];
                }

                for (int j = 0; j < (blocks >> 2); j++)
                {
                    row0 = buffPtr[0];
                    buffPtr[0] = db0 + 2 * db1 + row0;
                    buffPtr += sbSize;
                    row1 = buffPtr[0];
                    buffPtr[0] = -db1 + 2 * row0 - row1;
                    buffPtr += sbSize;
                    row2 = buffPtr[0];
                    buffPtr[0] = row0 + 2 * row1 + row2;
                    buffPtr += sbSize;
                    row3 = buffPtr[0];
                    buffPtr[0] = -row1 + 2 * row2 -
                            row3;
                    buffPtr += sbSize;

                    db0 = row2;
                    db1 = row3;
                }
                memory[0] = (short) row2;
                memory[1] = (short) row3;
                memory += 2;
                buffer++;
            }
        }
}

void Decoder::_sub4d420c(int *memory, int *buffer, int sbSize,
        int blocks)
{
    int row0, row1, row2 = 0, row3 = 0, db0, db1;
    int i;
    int sbSize2 = sbSize * 2, sbSize3 = sbSize * 3;
    if (blocks == 4)
    {
        for (i = 0; i < sbSize; i++)
        {
            row0 = buffer[0];
            row1 = buffer[sbSize];
            row2 = buffer[sbSize2];
            row3 = buffer[sbSize3];

            buffer[0] = memory[0] + 2 * memory[1] + row0;
            buffer[sbSize] = -memory[1] + 2 * row0 - row1;
            buffer[sbSize2] = row0 + 2 * row1 + row2;
            buffer[sbSize3] = -row1 + 2 * row2 - row3;

            memory[0] = row2;
            memory[1] = row3;

            memory += 2;
            buffer++;
        }
    }
    else
    {
        for (i = 0; i < sbSize; i++)
        {
            int *buffPtr = buffer;
            db0 = memory[0];
            db1 = memory[1];
            for (int j = 0; j < (blocks >> 2); j++)
            {
                row0 = buffPtr[0];
                buffPtr[0] = db0 + 2 * db1 + row0;
                buffPtr += sbSize;
                row1 = buffPtr[0];
                buffPtr[0] = -db1 + 2 * row0 - row1;
                buffPtr += sbSize;
                row2 = buffPtr[0];
                buffPtr[0] = row0 + 2 * row1 + row2;
                buffPtr += sbSize;
                row3 = buffPtr[0];
                buffPtr[0] = -row1 + 2 * row2 -
                        row3;
                buffPtr += sbSize;

                db0 = row2;
                db1 = row3;
            }
            memory[0] = row2;
            memory[1] = row3;

            memory += 2;
            buffer++;
        }
    }
}

Decoder::Decoder(int lev_cnt) : _levels(lev_cnt), _blockSize(1 << lev_cnt), _memoryBuffer(NULL)
{
}

Decoder::~Decoder()
{
    if (_memoryBuffer)
    {
        free(_memoryBuffer);
    }
}

}
}
}
