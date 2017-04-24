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

#ifndef FALLTERGEIST_UI_MVEPLAYER_H
#define FALLTERGEIST_UI_MVEPLAYER_H

// C++ standard includes
#include <ctime>

// Falltergeist includes
#include "../UI/Base.h"
#include "../Graphics/Movie.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{
namespace Format
{
namespace Mve
{
    class Chunk;
    class File;
}
}
namespace UI
{

// MVE Movie Player
class MvePlayer : public Falltergeist::UI::Base
{
public:
    MvePlayer(Format::Mve::File* mve);
    ~MvePlayer() override;

    void think() override;
    void render(bool eggTransparency = false) override;
    bool finished();
    uint32_t getAudio(uint8_t* data, uint32_t len);
    uint32_t samplesLeft();
    // Current frame number
    uint32_t frame();

private:
    Format::Mve::File* _mve = nullptr;
    std::unique_ptr<Format::Mve::Chunk> _chunk;

    Graphics::Movie* _movie;

    bool _timerStarted = false;
    bool _finished = false;

    uint8_t* _decodingMap = nullptr;
    int16_t* _audioBuf = nullptr;

    uint32_t  _frame = 0;
    uint32_t _delay = 0;
    uint32_t _audioBufHead = 0;
    uint32_t _audioBufTail = 0;
    uint32_t _audioBufSize = 0;
    uint32_t _samplesReady = 0;

    uint32_t _lastts;
    SDL_Surface* _currentBuf = NULL;
    SDL_Surface* _backBuf = NULL;

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
    enum class Chunk: uint16_t
    {
        INIT_AUDIO = 0,
        AUDIO,
        INIT_VIDEO,
        VIDEO,
        SHUTDOWN,
        END
    };
    enum class Opcode
    {
        END_STREAM = 0,
        END_CHUNK,
        CREATE_TIMER,
        INIT_AUDIO_BUF,
        START_AUDIO,
        INIT_VIDIO_BUF,
        UNKNOWN_0x06,
        SEND_BUFFER,
        AUDIO_DATA,
        AUDIO_SILENCE,
        INIT_VIDEO,
        CREATE_GRADIENT,
        SET_PALETTE,
        SET_PALETTE_COMPRESSED,
        UNKNOWN_0xe,
        SET_DECODING_MAP,
        UNKNOWN_0x10,
        VIDEO_DATA,
        UNKNOWN_0x12,
        UNKNOWN_0x13,
        UNKNOWN_0x14,
        UNKNOWN_0x15
    };
    //drawing helpers
    void _drawRow(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask);
    void _drawRow2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask);
    void _drawRow4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2);
    void _drawRow4colors2x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask);
    void _drawRow4colors2x1(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask);
    void _drawRow4colors1x2(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2);
    void _drawQuadrant(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t mask1, uint8_t mask2);
    void _drawQuadrant4colors(uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t mask1, uint8_t mask2, uint8_t mask3, uint8_t mask4);

};

}
}
#endif // FALLTERGEIST_UI_MVEPLAYER_H
