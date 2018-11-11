/*
 * Copyright 2012-2018 Falltergeist Developers.
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
#include "../Audio/SdlMixer.h"

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Base/Buffer.h"
#include "../Exception.h"
#include "../Format/Acm/File.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../UI/MvePlayer.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist {
    namespace Audio {
        SdlMixer::SdlMixer() {
            _init();
        }

        SdlMixer::~SdlMixer() {
            for (auto &x: _sfx) {
                Mix_FreeChunk(x.second);
            }
            Mix_HookMusic(NULL, NULL);
            Mix_CloseAudio();
        }

        void SdlMixer::_init() {
            std::string message = "[AUDIO] - SDL_Init - ";
            if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
                Logger::critical() << message + "[FAIL]" << std::endl;
                throw Exception(SDL_GetError());
            }
            Logger::info() << message + "[OK]" << std::endl;

            message = "[AUDIO] - Mix_OpenAudio - ";
            if (Mix_OpenAudio(22050, AUDIO_S16LSB, 2, Game::getInstance()->settings()->audioBufferSize()) < 0) {
                Logger::critical() << message + "[FAIL]" << std::endl;
                throw Exception(Mix_GetError());
            }
            Logger::info() << message + "[OK]" << std::endl;
            int frequency, channels;
            Mix_QuerySpec(&frequency, &_format, &channels);
            _volumes.insert(std::make_pair<Channel, double>(Channel::Music, 1.0f));
            _volumes.insert(std::make_pair<Channel, double>(Channel::Speech, 1.0f));
            _volumes.insert(std::make_pair<Channel, double>(Channel::Effects, 1.0f));
        }

        std::function<void(void *, uint8_t *, uint32_t)> musicCallback;

        void myMusicPlayer(void *udata, uint8_t *stream, int len) {
            musicCallback(udata, stream, len);
        }

        void SdlMixer::_musicCallback(void *udata, uint8_t *stream, uint32_t len) {
            if (_paused) return;

            auto pacm = (Format::Acm::File *) (udata);
            if (pacm->samplesLeft() <= 0) {
                if (_loop) {
                    pacm->rewind();
                } else {
                    Mix_HookMusic(NULL, NULL);
                    return;
                }
            }

            // music is stereo. just fetch
            Base::Buffer<uint16_t> tmp(len / 2);
            pacm->readSamples(tmp.data(), len / 2);
            SDL_memset(stream, 0, len);
            SDL_MixAudioFormat(
                stream,
                (uint8_t *) tmp.data(),
                _format,
                len,
                static_cast<int>(SDL_MIX_MAXVOLUME * channelVolume(Channel::Music))
            );
        }

        void SdlMixer::_playACMMusic(const std::string &filename, bool loop) {
            Mix_HookMusic(NULL, NULL);
            auto acm = ResourceManager::getInstance()->acmFileType(
                    Game::getInstance()->settings()->musicPath() + filename);
            if (!acm) return;
            _loop = loop;
            musicCallback = std::bind(&SdlMixer::_musicCallback, this, std::placeholders::_1, std::placeholders::_2,
                                      std::placeholders::_3);
            acm->rewind();
            Mix_HookMusic(myMusicPlayer, (void *) acm);
        }

        void SdlMixer::_speechCallback(void *udata, uint8_t *stream, uint32_t len) {
            if (_paused) return;

            auto pacm = (Format::Acm::File *) (udata);
            if (pacm->samplesLeft() <= 0) {
                Mix_HookMusic(NULL, NULL);
                return;
            }

            Base::Buffer<uint16_t> tmp(len / 2);
            uint16_t *sstr = (uint16_t *) stream;
            pacm->readSamples(tmp.data(), len / 4);
            for (size_t i = 0; i < len / 4; i++) {
                sstr[i * 2] = tmp[i];
                sstr[i * 2 + 1] = tmp[i];
            }
        }

        void SdlMixer::_playACMSpeech(const std::string &filename) {
            Mix_HookMusic(NULL, NULL);
            auto acm = ResourceManager::getInstance()->acmFileType("sound/speech/" + filename);
            if (!acm) return;
            musicCallback = std::bind(&SdlMixer::_speechCallback, this, std::placeholders::_1, std::placeholders::_2,
                                      std::placeholders::_3);
            acm->rewind();
            Mix_HookMusic(myMusicPlayer, (void *) acm);
        }

        void SdlMixer::_playACMSound(const std::string &filename) {
            auto acm = ResourceManager::getInstance()->acmFileType(filename);
            if (!acm) return;
            Logger::debug("Mixer") << "playing: " << acm->filename() << std::endl;
            Mix_Chunk *chunk = NULL;

            auto it = _sfx.find(acm->filename());
            if (it != _sfx.end()) {
                chunk = it->second;
            }

            if (!chunk) {
                auto samples = acm->samples();

                Base::Buffer<uint16_t> tmpSamples(samples);
                auto cnt = acm->readSamples(tmpSamples.data(), samples) * 2;

                SDL_AudioCVT cvt;
                SDL_BuildAudioCVT(&cvt, AUDIO_S16LSB, 1, 22050, AUDIO_S16LSB, 2, 22050); //convert from mono to stereo

                cvt.buf = (Uint8 *) malloc(cnt * cvt.len_mult);
                memcpy(cvt.buf, tmpSamples.data(), cnt);
                cvt.len = static_cast<int>(cnt);
                SDL_ConvertAudio(&cvt);

                // make SDL_mixer chunk
                chunk = Mix_QuickLoad_RAW(cvt.buf, static_cast<uint32_t>(cvt.len * cvt.len_ratio));
                if (_sfx.size() > 100) // TODO: make this configurable
                {
                    Mix_FreeChunk(_sfx.begin()->second);
                    _sfx.erase(_sfx.begin());
                }
                _sfx.insert(std::pair<std::string, Mix_Chunk *>(acm->filename(), chunk));
            }
            Mix_PlayChannel(-1, chunk, 0);
        }

        void SdlMixer::playLooped(Channel channel, const std::string& filename) {
            if (channel == Channel::Music) {
                _playACMMusic(filename, true);
            }
            // TODO implement for different extensions(filetypes) and channels
        }

        void SdlMixer::playOnce(Channel channel, const std::string& filename) {
            if (channel == Channel::Music) {
                _playACMMusic(filename, false);
            }
            if (channel == Channel::Speech) {
                _playACMSpeech(filename);
            }
            if (channel == Channel::Effects) {
                _playACMSound(filename);
            }
            // TODO implement for different extensions(filetypes)
        }

        void SdlMixer::playOnce(Channel channel, std::shared_ptr<ISound> sound) {
            // TODO replace with placing sound to given channel map
            _sound = sound;
            Mix_HookMusic([](void *udata, Uint8 *stream, int len) {
                auto sound = (ISound*)(udata);
                sound->readSamples(stream, (uint32_t)len);
            }, reinterpret_cast<void *>(sound.get()));
        }

        void SdlMixer::stopChannel(Channel channel) {
            // TODO
            Mix_HookMusic(NULL, NULL);
            //Mix_HaltChannel(-1);
        }

        void SdlMixer::pauseChannel(Channel channel) {
            // TODO
            _paused = true;
        }

        void SdlMixer::resumeChannel(Channel channel) {
            // TODO
            _paused = false;
        }

        void SdlMixer::setMasterVolume(double volume) {
            volume = _normalizeVolume(volume);
            _masterVolume = volume;
        }

        double SdlMixer::masterVolume() {
            return _masterVolume;
        }

        void SdlMixer::setChannelVolume(Channel channel, double volume) {
            volume = _normalizeVolume(volume);
            _volumes.at(channel) = volume;
        }

        double SdlMixer::channelVolume(Channel channel) {
            return _volumes.at(channel);
        }

        double SdlMixer::_normalizeVolume(double volume) {
            if (volume < 0.0f) {
                volume = 0.0f;
            }
            if (volume > 1.0f) {
                volume = 1.0f;
            }
            return volume;
        }
    }
}
