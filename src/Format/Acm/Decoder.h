/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist Developers
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

#ifndef FALLTERGEIST_FORMAT_ACM_DECODER_H
#define FALLTERGEIST_FORMAT_ACM_DECODER_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Acm
{

class Decoder
{

public:
    Decoder(int lev_cnt);
    virtual ~Decoder();

    int init();

    void decodeData(int *buffer, int blocks);

private:
    int _levels, _blockSize;
    int *_memoryBuffer;

    void _sub4d3fcc(short *memory, int *buffer, int sbSize, int blocks);

    void _sub4d420c(int *memory, int *buffer, int sbSize, int blocks);

};

}
}
}
#endif // FALLTERGEIST_FORMAT_ACM_DECODER_H
