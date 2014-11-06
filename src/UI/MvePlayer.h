/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */
#ifndef FALLTERGEIST_MVEPLAYER_H
#define FALLTERGEIST_MVEPLAYER_H

// C++ standard includes
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#endif

// Falltergeist includes
#include "../Engine/Graphics/UI.h"

// Third party includes
#include <libfalltergeist.h>
#include <SDL.h>

namespace Falltergeist
{

class MvePlayer : public UI
{
public:
  MvePlayer(libfalltergeist::MveFileType* mve);
 ~MvePlayer();
private:
    libfalltergeist::MveFileType* _mve;

    bool _timerStarted = false;
    bool _finished = false;
    uint32_t  _frame = 0;
    uint32_t _delay;
    #ifdef _WIN32
    LARGE_INTEGER _lastts;
    #else
    struct timespec _lastts;
    #endif // _WIN32
    uint8_t* _decodingMap=NULL;
    int16_t* _audioBuf=NULL;
    uint32_t _audioBufHead=0;
    uint32_t _audioBufTail=0;
    uint32_t _audioBufSize=0;
    uint32_t _samplesReady=0;
    std::shared_ptr<libfalltergeist::MveChunk> _chunk;
    SDL_Surface* _currentBuf=NULL;
    SDL_Surface* _backBuf=NULL;
    void _processChunk();
    void _decodeVideo(uint8_t* data, uint32_t len);
    void _decodeFrame(uint8_t* data, uint32_t len);
    void _initVideoBuffer(uint8_t* data);
    void _sendVideoBuffer(uint8_t* data);
    void _setPalette(uint8_t* data);
    void _setDecodingMap(uint8_t* data);
    void _initAudioBuffer(uint8_t version, uint8_t* data);
    void _playAudio();
    void _decodeAudio(uint8_t* data, uint32_t len);
    enum { CHUNK_INIT_AUDIO = 0, CHUNK_AUDIO, CHUNK_INIT_VIDEO, CHUNK_VIDEO, CHUNK_SHUTDOWN, CHUNK_END };
    enum { OPCODE_END_STREAM = 0, OPCODE_END_CHUNK, OPCODE_CREATE_TIMER, OPCODE_INIT_AUDIO_BUF,
           OPCODE_START_AUDIO, OPCODE_INIT_VIDIO_BUF, OPCODE_UNKNOWN_0x06, OPCODE_SEND_BUFFER, OPCODE_AUDIO_DATA,
           OPCODE_AUDIO_SILENCE, OPCODE_INIT_VIDEO, OPCODE_CREATE_GRADIENT, OPCODE_SET_PALETTE, OPCODE_SET_PALETTE_COMPRESSED,
           OPCODE_UNKNOWN_0xe, OPCODE_SET_DECODING_MAP, OPCODE_UNKNOWN_0x10, OPCODE_VIDEO_DATA,
           OPCODE_UNKNOWN_0x12, OPCODE_UNKNOWN_0x13, OPCODE_UNKNOWN_0x14, OPCODE_UNKNOWN_0x15 };
    //drawing helpers
    void _drawRow(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask);
    void _drawRow2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask);
    void _drawRow4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2);
    void _drawRow4colors2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask);
    void _drawRow4colors2x1(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask);
    void _drawRow4colors1x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2);
    void _drawQuadrant(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask1, uint8_t mask2);
    void _drawQuadrant4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2, uint8_t mask3, uint8_t mask4);
public:
    void think();
    void render();
    bool finished();
    uint32_t getAudio(uint8_t* data, uint32_t len);
    uint32_t samplesLeft();
    uint32_t frame();
};

}

#endif // FALLTERGEIST_MVEPLAYER_H
