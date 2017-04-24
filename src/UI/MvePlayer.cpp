/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// Related headers
#include "../UI/MvePlayer.h"

// C++ standard includes
#include <bitset>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../Format/Mve/Chunk.h"
#include "../Format/Mve/File.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Exception.h"
#include "../Logger.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

static const int16_t audio_exp_table[256] =
{
         0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15,
        16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31,
        32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     47,     51,     56,     61,
        66,     72,     79,     86,     94,    102,    112,    122,    133,    145,    158,    173,    189,    206,    225,    245,
       267,    292,    318,    348,    379,    414,    452,    493,    538,    587,    640,    699,    763,    832,    908,    991,
      1081,   1180,   1288,   1405,   1534,   1673,   1826,   1993,   2175,   2373,   2590,   2826,   3084,   3365,   3672,   4008,
      4373,   4772,   5208,   5683,   6202,   6767,   7385,   8059,   8794,   9597,  10472,  11428,  12471,  13609,  14851,  16206,
     17685,  19298,  21060,  22981,  25078,  27367,  29864,  32589, -29973, -26728, -23186, -19322, -15105, -10503,  -5481,     -1,
         1,      1,   5481,  10503,  15105,  19322,  23186,  26728,  29973, -32589, -29864, -27367, -25078, -22981, -21060, -19298,
    -17685, -16206, -14851, -13609, -12471, -11428, -10472,  -9597,  -8794,  -8059,  -7385,  -6767,  -6202,  -5683,  -5208,  -4772,
     -4373,  -4008,  -3672,  -3365,  -3084,  -2826,  -2590,  -2373,  -2175,  -1993,  -1826,  -1673,  -1534,  -1405,  -1288,  -1180,
     -1081,   -991,   -908,   -832,   -763,   -699,   -640,   -587,   -538,   -493,   -452,   -414,   -379,   -348,   -318,   -292,
      -267,   -245,   -225,   -206,   -189,   -173,   -158,   -145,   -133,   -122,   -112,   -102,    -94,    -86,    -79,    -72,
       -66,    -61,    -56,    -51,    -47,    -43,    -42,    -41,    -40,    -39,    -38,    -37,    -36,    -35,    -34,    -33,
       -32,    -31,    -30,    -29,    -28,    -27,    -26,    -25,    -24,    -23,    -22,    -21,    -20,    -19,    -18,    -17,
       -16,    -15,    -14,    -13,    -12,    -11,    -10,     -9,     -8,     -7,     -6,     -5,     -4,     -3,     -2,     -1
};

static inline int16_t clip_int16(int a)
{
    if ((a+0x8000) & ~0xFFFF)
    {
        return (a>>31) ^ 0x7FFF;
    }
    else
    {
        return a;
    }
}

int16_t get_short(uint8_t *data)
{
    int16_t value;
    value = data[0] | (data[1] << 8);
    return value;
}

int32_t get_int(uint8_t *data)
{
    int32_t value;
    value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}


MvePlayer::MvePlayer(Format::Mve::File* mve) : Falltergeist::UI::Base()
{
    _movie = new Graphics::Movie();
    _mve = mve;
    _mve->setPosition(26);
    _chunk = _mve->getNextChunk();
    while(!_finished && !_timerStarted )
    {
        _processChunk();
    }
}

MvePlayer::~MvePlayer()
{
    delete [] _decodingMap;
    delete [] _audioBuf;
    delete _movie;

    SDL_FreeSurface(_currentBuf);
    SDL_FreeSurface(_backBuf);
}

void MvePlayer::render(bool eggTransparency)
{
    //we dont have data yet
    if (!_timerStarted)
    {
        return;
    }
    _movie->render(_position.x(),_position.y());
}

SDL_Rect relClose(uint32_t b, int8_t sign, uint32_t _x, uint32_t _y)
{
    SDL_Rect rect;
    rect.w=8;
    rect.h=8;
    if (b < 56)
    {
        rect.x = _x+sign*(8 + (b % 7));
        rect.y = _y+sign*(b / 7);
    }
    else
    {
        rect.x = _x+sign*(-14 + ((b - 56) % 29));
        rect.y = _y+sign*( 8 + ((b - 56) / 29));
    }
    return rect;
}

SDL_Rect relFar(uint8_t b, uint32_t _x, uint32_t _y)
{
    int32_t ma, mi;
    SDL_Rect rect;
    rect.w = 8;
    rect.h = 8;

    ma = b >> 4;
    mi = b & 0xf;

    rect.x = _x + mi - 8;
    rect.y = _y + ma - 8;

    return rect;
}


void MvePlayer::_drawRow(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask)
{
    std::bitset<8> bitmask(mask);
    SDL_Rect dstrect;
    for (uint32_t dx = 0; dx < 8; dx++)
    {
        dstrect.w = 1;
        dstrect.h = 1;
        dstrect.x = x + dx;
        dstrect.y = y;
        SDL_FillRect(_currentBuf, &dstrect, (bitmask.test(dx) ? c2 : c1));
    }
}

void MvePlayer::_drawRow2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask)
{
    std::bitset<8> bitmask(mask);
    SDL_Rect dstrect;
    for (uint32_t di = 0; di < 8; di++)
    {
        dstrect.w = 2;
        dstrect.h = 2;
        dstrect.x = x + (di % 4) * 2;
        dstrect.y = y + (di / 4) * 2;
        SDL_FillRect(_currentBuf, &dstrect, (bitmask.test(di) ? c2 : c1));
    }
}

void MvePlayer::_drawRow4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1,uint8_t mask2)
{
    std::bitset<8> bitmasks[2] = {mask1, mask2};
    SDL_Rect dstrect;
    for (uint32_t dx = 0;dx < 8; dx++)
    {
        dstrect.w = 1;
        dstrect.h = 1;
        dstrect.x = x + dx;
        dstrect.y = y;
        SDL_FillRect(_currentBuf,&dstrect, (bitmasks[dx/4].test((dx%4)*2+1) ? (bitmasks[dx/4].test((dx%4)*2) ? c4 : c3) : (bitmasks[dx/4].test((dx%4)*2) ? c2 : c1) ));
    }
}

void MvePlayer::_drawRow4colors2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask)
{
    std::bitset<8> bitmask(mask);
    SDL_Rect dstrect;
    for (uint32_t dx = 0; dx < 4; dx++)
    {
        dstrect.w = 2;
        dstrect.h = 2;
        dstrect.x = x + dx*2;
        dstrect.y = y;
        SDL_FillRect(_currentBuf,&dstrect, (bitmask.test(dx*2+1) ? (bitmask.test(dx*2) ? c4 : c3) : (bitmask.test(dx*2) ? c2 : c1) ));
    }
}

void MvePlayer::_drawRow4colors2x1(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask)
{
    std::bitset<8> bitmask(mask);
    SDL_Rect dstrect;
    for (uint32_t dx = 0; dx < 4; dx++)
    {
        dstrect.w = 2;
        dstrect.h = 1;
        dstrect.x = x + dx*2;
        dstrect.y = y;
        SDL_FillRect(_currentBuf,&dstrect, (bitmask.test(dx*2+1) ? (bitmask.test(dx*2) ? c4 : c3) : (bitmask.test(dx*2) ? c2 : c1) ));
    }
}

void MvePlayer::_drawRow4colors1x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2)
{
    std::bitset<8> bitmasks[2]={mask1,mask2};
    SDL_Rect dstrect;
    for (uint32_t dx = 0; dx < 8; dx++)
    {
        dstrect.w = 1;
        dstrect.h = 2;
        dstrect.x = x + dx;
        dstrect.y = y;
        SDL_FillRect(_currentBuf,&dstrect, (bitmasks[dx/4].test((dx%4)*2+1) ? (bitmasks[dx/4].test((dx%4)*2) ? c4 : c3) : (bitmasks[dx/4].test((dx%4)*2) ? c2 : c1) ));
    }

}


void MvePlayer::_drawQuadrant(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask1, uint8_t mask2)
{
    std::bitset<8> bitmask1(mask1);
    std::bitset<8> bitmask2(mask2);
    SDL_Rect dstrect;
    for (uint32_t dy = 0; dy < 4; dy++)
    {
        for (uint32_t dx = 0; dx < 4; dx++)
        {
            dstrect.w = 1;
            dstrect.h = 1;
            dstrect.x = x + dx;
            dstrect.y = y + dy;
            if (dy < 2)
            {
                SDL_FillRect(_currentBuf,&dstrect, (bitmask1.test(4*(dy%2)+dx) ? c2 : c1));
            }
            else
            {
                SDL_FillRect(_currentBuf,&dstrect, (bitmask2.test(4*(dy%2)+dx) ? c2 : c1));
            }
        }
    }

}


void MvePlayer::_drawQuadrant4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2, uint8_t mask3, uint8_t mask4)
{
    std::bitset<8> bitmasks[4];
    bitmasks[0] = mask1;
    bitmasks[1] = mask2;
    bitmasks[2] = mask3;
    bitmasks[3] = mask4;
    SDL_Rect dstrect;
    for (uint32_t dy = 0; dy < 4; dy++)
    {
        for (uint32_t dx = 0; dx < 4; dx++)
        {
            dstrect.w = 1;
            dstrect.h = 1;
            dstrect.x = x + dx;
            dstrect.y = y + dy;
            SDL_FillRect(_currentBuf,&dstrect, (bitmasks[dy].test(dx*2+1) ? (bitmasks[dy].test(dx*2) ? c4 : c3) : (bitmasks[dy].test(dx*2) ? c2 : c1) ));
        }
    }
}

void MvePlayer::_decodeFrame(uint8_t* data, uint32_t len)
{
    uint32_t h = (_currentBuf->h / 8);
    uint32_t w = (_currentBuf->w / 8);
    uint32_t curMap;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    uint8_t color;
    for (uint32_t y = 0; y < h;y++)
    {
        for (uint32_t x = 0; x < w;x++)
        {
            curMap = (y*w + x);
            switch (_decodingMap[curMap])
            {
                case 0x0:
                    //copy from backbuf
                    srcrect.w = 8;
                    srcrect.h = 8;
                    srcrect.x = x*8;
                    srcrect.y = y*8;
                    SDL_BlitSurface(_backBuf, &srcrect, _currentBuf, &srcrect);
                    break;
                case 0x1:
                    //copy from back-back buff -> copy from current frame -> do nothing
                    break;
                case 0x2:
                    srcrect = relClose(data[0], 1, x*8, y*8);
                    dstrect.w = 8;
                    dstrect.h = 8;
                    dstrect.x = x*8;
                    dstrect.y = y*8;
                    SDL_BlitSurface(_currentBuf, &srcrect, _currentBuf, &dstrect);
                    data++;
                    len--;
                    break;
                case 0x3:
                    srcrect = relClose(data[0], -1, x*8, y*8);
                    dstrect.w = 8;
                    dstrect.h = 8;
                    dstrect.x = x*8;
                    dstrect.y = y*8;
                    SDL_BlitSurface(_currentBuf, &srcrect, _currentBuf, &dstrect);
                    data++;
                    len--;
                    break;
                case 0x4:
                    srcrect = relFar(data[0], x*8, y*8);
                    dstrect.w = 8;
                    dstrect.h = 8;
                    dstrect.x = x*8;
                    dstrect.y = y*8;
                    SDL_BlitSurface(_backBuf, &srcrect, _currentBuf, &dstrect);
                    data++;
                    len--;
                    break;
                case 0x5:
                    srcrect.w = 8;
                    srcrect.h = 8;
                    dstrect.w = 8;
                    dstrect.h = 8;
                    dstrect.x = x*8;
                    dstrect.y = y*8;
                    srcrect.x = x*8 + (int8_t)data[0];
                    srcrect.y = y*8 + (int8_t)data[1];
                    SDL_BlitSurface(_backBuf, &srcrect, _currentBuf, &dstrect);
                    data += 2;
                    len -= 2;
                    break;
                case 0x6:
                    //skip 2 blocks
                    x++;
                    if (x >= w)
                    {
                        x = 0;
                        y++;
                    }
                    x++;
                    if (x >= w)
                    {
                        x = 0;
                        y++;
                    }
                    break;
                //hell
                case 0x7:
                    if (data[0]<=data[1])
                    {
                        _drawRow(x*8, y*8,     data[0], data[1], data[2] );
                        _drawRow(x*8, y*8 + 1, data[0], data[1], data[3] );
                        _drawRow(x*8, y*8 + 2, data[0], data[1], data[4] );
                        _drawRow(x*8, y*8 + 3, data[0], data[1], data[5] );
                        _drawRow(x*8, y*8 + 4, data[0], data[1], data[6] );
                        _drawRow(x*8, y*8 + 5, data[0], data[1], data[7] );
                        _drawRow(x*8, y*8 + 6, data[0], data[1], data[8]);
                        _drawRow(x*8, y*8 + 7, data[0], data[1], data[9]);
                        data += 10;
                        len -= 10;
                    }
                    else
                    {
                        _drawRow2x2(x*8, y*8,     data[0], data[1], data[2]);
                        _drawRow2x2(x*8, y*8 + 4, data[0], data[1], data[3]);
                        data += 4;
                        len -= 4;
                    }
                    break;
                case 0x8:
                    if (data[0] <= data[1])
                    {
                        // cross-split
                        // 0 | 2
                        // -----
                        // 1 | 3
                        _drawQuadrant(x*8,     y*8,     data[0],  data[1],  data[2],  data[3] );
                        _drawQuadrant(x*8,     y*8 + 4, data[4],  data[5],  data[6],  data[7] );
                        _drawQuadrant(x*8 + 4, y*8,     data[8],  data[9],  data[10], data[11]);
                        _drawQuadrant(x*8 + 4, y*8 + 4, data[12], data[13], data[14], data[15]);
                        data+=16;
                        len-=16;
                    }
                    else
                    {
                        if (data[6] <= data[7])
                        {
                            //left|right split. same as above, except uses 1 byte per 2 4x4 blocks
                            // 0 | 2
                            // 1 | 3
                            _drawQuadrant(x*8,     y*8,     data[0], data[1], data[2],  data[3] );
                            _drawQuadrant(x*8,     y*8 + 4, data[0], data[1], data[4],  data[5] );
                            _drawQuadrant(x*8 + 4, y*8,     data[6], data[7], data[8],  data[9] );
                            _drawQuadrant(x*8 + 4, y*8 + 4, data[6], data[7], data[10], data[11]);
                        }
                        else
                        {
                            //top|bottom split
                            // 0 1
                            //-----
                            // 2 3
                            _drawRow(x*8, y*8,     data[0], data[1], data[2] );
                            _drawRow(x*8, y*8 + 1, data[0], data[1], data[3] );
                            _drawRow(x*8, y*8 + 2, data[0], data[1], data[4] );
                            _drawRow(x*8, y*8 + 3, data[0], data[1], data[5] );
                            _drawRow(x*8, y*8 + 4, data[6], data[7], data[8] );
                            _drawRow(x*8, y*8 + 5, data[6], data[7], data[9] );
                            _drawRow(x*8, y*8 + 6, data[6], data[7], data[10]);
                            _drawRow(x*8, y*8 + 7, data[6], data[7], data[11]);
                        }
                        data += 12;
                        len -= 12;
                    }
                    break;
                case 0x9:
                    if (data[0] <= data[1] && data[2] <= data[3])
                    {
                        _drawRow4colors(x*8, y*8,     data[0], data[1], data[2], data[3], data[4],   data[5] );
                        _drawRow4colors(x*8, y*8 + 1, data[0], data[1], data[2], data[3], data[6],   data[7] );
                        _drawRow4colors(x*8, y*8 + 2, data[0], data[1], data[2], data[3], data[8],   data[9] );
                        _drawRow4colors(x*8, y*8 + 3, data[0], data[1], data[2], data[3], data[10],  data[11]);
                        _drawRow4colors(x*8, y*8 + 4, data[0], data[1], data[2], data[3], data[12],  data[13]);
                        _drawRow4colors(x*8, y*8 + 5, data[0], data[1], data[2], data[3], data[14],  data[15]);
                        _drawRow4colors(x*8, y*8 + 6, data[0], data[1], data[2], data[3], data[16],  data[17]);
                        _drawRow4colors(x*8, y*8 + 7, data[0], data[1], data[2], data[3], data[18],  data[19]);
                        data += 20;
                        len -= 20;
                    }
                    else if (data[0] <= data[1] && data[2] > data[3])
                    {
                        _drawRow4colors2x2(x*8, y*8,     data[0], data[1], data[2], data[3], data[4]);
                        _drawRow4colors2x2(x*8, y*8 + 2, data[0], data[1], data[2], data[3], data[5]);
                        _drawRow4colors2x2(x*8, y*8 + 4, data[0], data[1], data[2], data[3], data[6]);
                        _drawRow4colors2x2(x*8, y*8 + 6, data[0], data[1], data[2], data[3], data[7]);
                        data += 8;
                        len -= 8;
                    }
                    else if (data[0] > data[1] && data[2] <= data[3])
                    {
                        _drawRow4colors2x1(x*8, y*8,     data[0], data[1], data[2], data[3], data[4] );
                        _drawRow4colors2x1(x*8, y*8 + 1, data[0], data[1], data[2], data[3], data[5] );
                        _drawRow4colors2x1(x*8, y*8 + 2, data[0], data[1], data[2], data[3], data[6] );
                        _drawRow4colors2x1(x*8, y*8 + 3, data[0], data[1], data[2], data[3], data[7] );
                        _drawRow4colors2x1(x*8, y*8 + 4, data[0], data[1], data[2], data[3], data[8] );
                        _drawRow4colors2x1(x*8, y*8 + 5, data[0], data[1], data[2], data[3], data[9] );
                        _drawRow4colors2x1(x*8, y*8 + 6, data[0], data[1], data[2], data[3], data[10]);
                        _drawRow4colors2x1(x*8, y*8 + 7, data[0], data[1], data[2], data[3], data[11]);
                        data += 12;
                        len -= 12;
                    }
                    else if (data[0] > data[1] && data[2] > data[3])
                    {
                        _drawRow4colors1x2(x*8, y*8,     data[0], data[1], data[2], data[3], data[4],  data[5]);
                        _drawRow4colors1x2(x*8, y*8 + 2, data[0], data[1], data[2], data[3], data[6],  data[7]);
                        _drawRow4colors1x2(x*8, y*8 + 4, data[0], data[1], data[2], data[3], data[8],  data[9]);
                        _drawRow4colors1x2(x*8, y*8 + 6, data[0], data[1], data[2], data[3], data[10], data[11]);
                        data += 12;
                        len -= 12;
                    }
                    break;
                case 0xA:
                    if (data[0] <= data[1])
                    {
                        // quadrant. 4 colors per block, 2 bits of pattern per pixel
                        // 0 | 2
                        // -----
                        // 1 | 3
                        _drawQuadrant4colors(x*8,     y*8,     data[0],  data[1],  data[2],  data[3],  data[4],  data[5],  data[6],  data[7] );
                        _drawQuadrant4colors(x*8,     y*8 + 4, data[8],  data[9],  data[10], data[11], data[12], data[13], data[14], data[15]);
                        _drawQuadrant4colors(x*8 + 4, y*8,     data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23]);
                        _drawQuadrant4colors(x*8 + 4, y*8 + 4, data[24], data[25], data[26], data[27], data[28], data[29], data[30], data[31]);

                        data += 32;
                        len -= 32;
                    }
                    else
                    {
                        if (data[12] <= data[13])
                        {
                            //vertical split, 4 colors per half
                            // 0 | 2
                            // 1 | 3
                            _drawQuadrant4colors(x*8,     y*8,     data[0],  data[1],  data[2],  data[3],  data[4],  data[5],  data[6],  data[7] );
                            _drawQuadrant4colors(x*8,     y*8 + 4, data[0],  data[1],  data[2],  data[3],  data[8],  data[9],  data[10], data[11]);
                            _drawQuadrant4colors(x*8 + 4, y*8,     data[12], data[13], data[14], data[15], data[16], data[17], data[18], data[19]);
                            _drawQuadrant4colors(x*8 + 4, y*8 + 4, data[12], data[13], data[14], data[15], data[20], data[21], data[22], data[23]);
                        }
                        else
                        {
                            //horizontal split, 4 colors per half
                            // 0  1
                            //-----
                            // 2  3
                            _drawRow4colors(x*8, y*8,     data[0],  data[1],  data[2],  data[3],  data[4],   data[5] );
                            _drawRow4colors(x*8, y*8 + 1, data[0],  data[1],  data[2],  data[3],  data[6],   data[7] );
                            _drawRow4colors(x*8, y*8 + 2, data[0],  data[1],  data[2],  data[3],  data[8],   data[9] );
                            _drawRow4colors(x*8, y*8 + 3, data[0],  data[1],  data[2],  data[3],  data[10],  data[11]);
                            _drawRow4colors(x*8, y*8 + 4, data[12], data[13], data[14], data[15], data[16],  data[17]);
                            _drawRow4colors(x*8, y*8 + 5, data[12], data[13], data[14], data[15], data[18],  data[19]);
                            _drawRow4colors(x*8, y*8 + 6, data[12], data[13], data[14], data[15], data[20],  data[21]);
                            _drawRow4colors(x*8, y*8 + 7, data[12], data[13], data[14], data[15], data[22],  data[23]);
                        }
                        data += 24;
                        len -= 24;
                    }
                    break;
                //raw data
                case 0xB:
                    dstrect.w = 1;
                    dstrect.h = 1;
                    for (uint32_t fy = 0; fy < 8; fy++)
                    {
                        for (uint32_t fx = 0; fx < 8; fx++)
                        {
                            color=data[fy*8 + fx];
                            dstrect.x = x*8 + fx;
                            dstrect.y = y*8 + fy;
                            SDL_FillRect(_currentBuf, &dstrect, color);
                        }
                    }
                    data += 64;
                    len -= 64;
                    break;
                case 0xC:
                    dstrect.w = 2;
                    dstrect.h = 2;
                    for (uint32_t fy = 0; fy < 4; fy++)
                    {
                        for (uint32_t fx = 0; fx < 4; fx++)
                        {
                            color = data[fy*4 + fx];
                            dstrect.x = x*8 + fx*2;
                            dstrect.y = y*8 + fy*2;
                            SDL_FillRect(_currentBuf, &dstrect, color);
                        }
                    }
                    data += 16;
                    len -= 16;
                    break;
                case 0xD:
                    dstrect.w = 4;
                    dstrect.h = 4;
                    for (uint32_t fy = 0; fy < 2; fy++)
                    {
                        for (uint32_t fx = 0; fx < 2; fx++)
                        {
                            color = data[fy*2 + fx];
                            dstrect.x = x*8 + fx*4;
                            dstrect.y = y*8 + fy*4;
                            SDL_FillRect(_currentBuf, &dstrect, color);
                        }
                    }
                    data += 4;
                    len -= 4;
                    break;
                case 0xE:
                    dstrect.w = 8;
                    dstrect.h = 8;
                    color = data[0];
                    dstrect.x = x*8;
                    dstrect.y = y*8;
                    SDL_FillRect(_currentBuf, &dstrect, color);
                    data++;
                    len--;
                    break;
                //check-board
                case 0xF:
                    dstrect.w = 1;
                    dstrect.h = 1;
                    uint32_t even = 0;
                    for (uint32_t fy = 0; fy < 8; fy++)
                    {
                        for (uint32_t fx = 0; fx < 8; fx++)
                        {
                            color = data[even%2];
                            dstrect.x = x*8 + fx;
                            dstrect.y = y*8 + fy;
                            SDL_FillRect(_currentBuf, &dstrect, color);
                            even++;
                        }
                        even++;
                    }
                    data += 2;
                    len -= 2;
                    break;
            }
        }
    }
}

void MvePlayer::_decodeVideo( uint8_t* data, uint32_t len )
{
/*
    int16_t nFrameHot, nFrameCold;
    int16_t nXoffset, nYoffset;
    int16_t nXsize, nYsize;
*/
    int16_t nFlags;

/*
    nFrameHot  = get_short(data);
    nFrameCold = get_short(data+2);
    nXoffset   = get_short(data+4);
    nYoffset   = get_short(data+6);
    nXsize     = get_short(data+8);
    nYsize     = get_short(data+10);
*/
    nFlags     = get_short(data+12);

    if (nFlags & 1)
    {
        SDL_Surface* temp;
        temp = _currentBuf;
        _currentBuf = _backBuf;
        _backBuf = temp;
    }
    _decodeFrame(data + 14, len - 14);

    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_BGR888);
    SDL_Surface *temp = SDL_ConvertSurface(_currentBuf, format, 0);
    _movie->loadFromSurface(temp);
    SDL_FreeSurface(temp);
    SDL_FreeFormat(format);
}

void MvePlayer::_setDecodingMap(uint8_t* data)
{
    uint32_t w = _currentBuf->w / 8;
    uint32_t h = _currentBuf->h / 8;

    for (uint32_t i = 0; i < w*h/2; i++)
    {
      _decodingMap[i*2] = data[i] & 0x0F;
      _decodingMap[i*2 + 1] = (data[i] >> 4) & 0x0F;
    }
}

void MvePlayer::_setPalette(uint8_t* data)
{
    uint16_t start = get_short(data);
    uint16_t count = get_short(data+2);
    SDL_Color palette[256];
    palette[0].r = 0;
    palette[0].g = 0;
    palette[0].b = 0;
    palette[0].a = 0;
    uint8_t* pal = data;
    pal+=4;

    for (uint16_t i = start; i <= count; i++)
    {
        palette[i].r = *(pal++) << 2;
        palette[i].g = *(pal++) << 2;
        palette[i].b = *(pal++) << 2;
        palette[i].a = 0;
    }
    int ret = 1;
    if (_currentBuf)
    {
        ret = SDL_SetPaletteColors(_currentBuf->format->palette, palette, 0, 256);
    }
    if (_backBuf)
    {
        ret = SDL_SetPaletteColors(_backBuf->format->palette, palette, 0, 256);
    }
    if (ret != 0)
    {
        throw new Exception(SDL_GetError());
    }
}

void MvePlayer::_sendVideoBuffer(uint8_t* data)
{
    _frame++;
}

void MvePlayer::_initVideoBuffer(uint8_t* data)
{
    uint16_t width  = 0;
    uint16_t height = 0;
    // size, apparently in 8x8 pixel blocks
    width = get_short(data) * 8;
    height = get_short(data+2) * 8;

    if (_currentBuf != nullptr) return;
    if (_backBuf != nullptr) return;

    _currentBuf = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);
    if (!_currentBuf)
    {
        throw new Exception(SDL_GetError());
    }

    _backBuf = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);
    if (!_backBuf)
    {
        throw new Exception(SDL_GetError());
    }

    if (_decodingMap != nullptr) return;
    // decoding map is 4 bits per 8x8 block
    _decodingMap = new uint8_t [(width*height / (8*8))];

}


void MvePlayer::_initAudioBuffer(uint8_t version, uint8_t* data)
{
//  uint16_t flags=get_short(data+2);
//  std::bitset<16> bit(flags);
//  uint16_t sample_rate=get_short(data+4); //always 22050
    uint32_t buflen = get_int(data + 6);
    _audioBuf = (int16_t*)malloc(buflen*2);
    _audioBufHead = 0;
    _audioBufTail = 0;
    _audioBufSize = buflen;
}

void MvePlayer::_playAudio()
{
}


uint32_t MvePlayer::samplesLeft()
{
    return _samplesReady;
}

uint32_t MvePlayer::getAudio(uint8_t* data, uint32_t len)
{
    if (!_timerStarted)
    {
        return 0;
    }
    uint32_t res = 0;
    int16_t *buf = (int16_t*)data;
    while (res < len / 2)
    {
        if (_samplesReady <= 0) break;
        *buf = _audioBuf[_audioBufHead];
        buf++;
        _audioBufHead++;
        if (_audioBufHead >= _audioBufSize) _audioBufHead = 0;
        res++;
        _samplesReady--;
    }
    return res;
}

void MvePlayer::_decodeAudio(uint8_t* data, uint32_t len)
{
    uint16_t strlen = get_short(data + 4);
    data += 6;
    int16_t left = get_short(data);
    int16_t right = get_short(data + 2);
    data += 4;

    _audioBuf[_audioBufTail] = left;
    _audioBufTail++;
    _samplesReady++;
    if (_audioBufTail >= _audioBufSize) _audioBufTail = 0;
    _audioBuf[_audioBufTail] = right;
    _audioBufTail++;
    _samplesReady++;
    if (_audioBufTail >= _audioBufSize) _audioBufTail = 0;

    for (int32_t i = 0; i < strlen/2-2; i++)
    {
        if (i%2 == 0)
        {
            left += audio_exp_table[data[i]];
            left = clip_int16(left);
            _audioBuf[_audioBufTail] = left;
        }
        else
        {
            right += audio_exp_table[data[i]];
            right = clip_int16(right);
            _audioBuf[_audioBufTail] = right;
        }
        _audioBufTail++;
        _samplesReady++;
        if (_audioBufTail >= _audioBufSize) _audioBufTail = 0;
    }
}

void MvePlayer::_processChunk()
{
    if (static_cast<Chunk>(_chunk->type()) == Chunk::END)
    {
        _finished = true;
        return;
    }

    auto& opcodes = _chunk->opcodes();
    for (auto& opcode : opcodes)
    {
        switch (static_cast<Opcode>(opcode.type()))
        {
            case Opcode::END_CHUNK:
                break;
            case Opcode::CREATE_TIMER:
                _delay = get_int(opcode.data()) * get_short(opcode.data() + 4);
                _timerStarted = true;
                _lastts = CrossPlatform::microtime();
                break;
            case Opcode::END_STREAM:
                _finished = true;
                return;
                break;
            case Opcode::INIT_AUDIO_BUF:
                _initAudioBuffer(opcode.version(), opcode.data());
                break;
            case Opcode::START_AUDIO:
                _playAudio();
                break;
            case Opcode::INIT_VIDIO_BUF:
                //can be called multiple times (intro and tanker)
                _initVideoBuffer(opcode.data());
                break;
            case Opcode::SEND_BUFFER:
                _sendVideoBuffer(opcode.data());
                //copy buffer to texture (with palette)
                break;
            case Opcode::AUDIO_DATA:
                _decodeAudio(opcode.data(), opcode.length());
                break;
            case Opcode::AUDIO_SILENCE:
                break;
            case Opcode::INIT_VIDEO:
                // we don't care about it
                break;
            case Opcode::CREATE_GRADIENT:
                break;
            case Opcode::SET_PALETTE:
                //can be called several times (intro and tanker)
                _setPalette(opcode.data());
                break;
            case Opcode::SET_PALETTE_COMPRESSED:
                break;
            case Opcode::SET_DECODING_MAP:
                _setDecodingMap(opcode.data());
                break;
            case Opcode::VIDEO_DATA:
                _decodeVideo(opcode.data(), opcode.length());
                //set (buffer) texture
                break;
            case Opcode::UNKNOWN_0x06:
            case Opcode::UNKNOWN_0xe:
            case Opcode::UNKNOWN_0x10:
            case Opcode::UNKNOWN_0x12:
            case Opcode::UNKNOWN_0x13:
            case Opcode::UNKNOWN_0x14:
                break;
            case Opcode::UNKNOWN_0x15:
                break;
        }
    }
    _chunk = _mve->getNextChunk();
}

void MvePlayer::think()
{
    if (!_timerStarted) return;

    uint32_t nsec = CrossPlatform::microtime() - _lastts;

    if (nsec >= _delay*1000) // 66728
    {
        _lastts = CrossPlatform::microtime();
        _processChunk();
    }
}

bool MvePlayer::finished()
{
    return _finished;
}

uint32_t MvePlayer::frame()
{
    return _frame;
}

}
}
