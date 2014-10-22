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
 */

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../../Engine/Audio/AudioMixer.h"
#include "../../Engine/Exception.h"
#include "../../Engine/Logger.h"
#include "../../UI/MvePlayer.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{

AudioMixer::AudioMixer()
{
    _init();
}

AudioMixer::~AudioMixer()
{
    for (auto& x: _sfx)
    {
        Mix_FreeChunk(x.second);
    }
    Mix_HookMusic(NULL,NULL);
    Mix_CloseAudio();
}

void AudioMixer::_init()
{
    std::string message = "[AUDIO] - SDL_Init - ";
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        Logger::critical() << message + "[FAIL]" << std::endl;
        throw Exception(SDL_GetError());
    }
    Logger::info() << message + "[OK]" << std::endl;

    message = "[AUDIO] - Mix_OpenAudio - ";
    if (Mix_OpenAudio(22050, AUDIO_S16LSB, 2, 4096) < 0)
    {
        Logger::critical() << message + "[FAIL]" << std::endl;
        throw Exception(Mix_GetError());
    }
    Logger::info() << message + "[OK]" << std::endl;
}

void AudioMixer::stopMusic()
{
    Mix_HookMusic(NULL, NULL);
}

std::function<void(void*, uint8_t*, int)> musicCallback;

void myMusicPlayer(void *udata, uint8_t *stream, int len)
{
    musicCallback(udata,stream,len);
}

void AudioMixer::_musicCallback(void *udata, uint8_t *stream, uint32_t len)
{
    if (_paused) return;

    auto pacm = *reinterpret_cast<std::shared_ptr<libfalltergeist::AcmFileType>*>(udata);
    if (pacm->samplesLeft() <= 0)
    {
        if (_loop)
        {
            pacm->rewind();
        }
        else
        {
            Mix_HookMusic(NULL,NULL);
            return;
        }
    }

    if (pacm->filename().find("music") != std::string::npos)
    {
        // music is stereo. just fetch
        pacm->readSamples((short int*)stream, len/2);
    }
    else
    {
        //all other files are mono. double it
        uint16_t* tmp = new uint16_t[len/2];
        uint16_t* sstr = (uint16_t*)stream;
        pacm->readSamples((short int*)tmp, len/4);
        for (uint32_t i = 0; i < len/4; i++)
        {
            sstr[i*2] = tmp[i];
            sstr[i*2+1] = tmp[i];
        }
        delete [] tmp;
    }
}

void AudioMixer::playACMMusic(std::shared_ptr<libfalltergeist::AcmFileType> acm, bool loop)
{
    _loop = loop;
    musicCallback = std::bind(&AudioMixer::_musicCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    acm->init();
    Mix_HookMusic(myMusicPlayer, reinterpret_cast<void *>(&acm));
}

void AudioMixer::_movieCallback(void *udata, uint8_t *stream, uint32_t len)
{
    //  std::cout << "playing " << len << std::endl;
    auto pmve = (MvePlayer*)(udata);
    if (pmve->samplesLeft() <= 0)
    {
        Logger::debug("AUDIO") << "buffer underrun?" << std::endl;
        Mix_HookMusic(NULL, NULL);
        return;
    }

    pmve->getAudio(stream, len);
}

void AudioMixer::playMovieMusic(MvePlayer* mve)
{
    musicCallback = std::bind(&AudioMixer::_movieCallback,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Mix_HookMusic(myMusicPlayer, reinterpret_cast<void *>(mve));
}

void AudioMixer::playACMSound(std::shared_ptr<libfalltergeist::AcmFileType> acm)
{
    Logger::debug("AudioMixer") << "playing: " << acm->filename() << std::endl;
    Mix_Chunk *chunk = NULL;

    auto it = _sfx.find(acm->filename());
    if (it != _sfx.end())
    {
        chunk=it->second;
    }

    if (!chunk)
    {
        acm->init();
        auto samples = acm->samples();

        uint8_t *memory = new uint8_t [samples * 2];
        auto cnt = acm->readSamples((short*)memory, samples)*2;

        SDL_AudioCVT cvt;
        SDL_BuildAudioCVT(&cvt, AUDIO_S16LSB, 1, 22050, AUDIO_S16LSB, 2, 22050); //convert from mono to stereo

        cvt.buf = (Uint8*)malloc(cnt*cvt.len_mult);
        memcpy(cvt.buf, (uint8_t*)memory, cnt);
        cvt.len = cnt;
        SDL_ConvertAudio(&cvt);
        // free old buffer
        delete [] memory;

        // make SDL_mixer chunk
        chunk = Mix_QuickLoad_RAW(cvt.buf, cvt.len*cvt.len_ratio);
        if (_sfx.size() > 100) // TODO: make this configurable
        {
            Mix_FreeChunk(_sfx.begin()->second);
            _sfx.erase(_sfx.begin());
        }
        _sfx.insert(std::pair<std::string, Mix_Chunk*>(acm->filename(), chunk));
    }
    Mix_PlayChannel(-1, chunk, 0);
}

void AudioMixer::stopSounds()
{
    Mix_HaltChannel(-1);
}

void AudioMixer::pauseMusic()
{
    _paused = true;
}

void AudioMixer::resumeMusic()
{
    _paused = false;
}

}
