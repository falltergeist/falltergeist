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
#include <iostream>

// Falltergeist includes
#include "../Audio/AcmSound.h"
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
            SDL_CloseAudio();
        }

        void SdlMixer::_init() {
            std::string message = "[AUDIO] - SDL_Init - ";
            if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
                Logger::critical() << message + "[FAIL]" << std::endl;
                throw Exception(SDL_GetError());
            }
            Logger::info() << message + "[OK]" << std::endl;

            message = "[AUDIO] - Sdl_OpenAudio - ";
            SDL_AudioSpec want, have;

            SDL_memset(&want, 0, sizeof(want));
            want.freq = 22050;
            want.format = AUDIO_S16LSB;
            want.channels = 2;
            want.samples = Game::getInstance()->settings()->audioBufferSize();
            want.callback = [](void* userdata, Uint8* stream, int len) {
                auto mixer = (SdlMixer*) userdata;
                mixer->_mixChannels(stream, (uint32_t)len);
            };
            want.userdata = (void*) this;

            if (SDL_OpenAudio(&want, &have) < 0) {
                Logger::critical() << message + "[FAIL]" << std::endl;
                throw Exception(SDL_GetError());
            }

            if (have.format != want.format) {
                Logger::critical() << message + "[FAIL]" << std::endl;
                throw Exception("We didn't get desired audio format.");
            }
            SDL_PauseAudio(0);
            Logger::info() << message + "[OK]" << std::endl;
            _initChannels();
        }

        void SdlMixer::_initChannels() {
            _volumes[Channel::Music] = 0.0f;
            _volumes[Channel::Speech] = 0.0f;
            _volumes[Channel::Effects] = 0.0f;
            _sounds[Channel::Music] = {};
            _sounds[Channel::Speech] = {};
            _sounds[Channel::Effects] = {};
        }

        void SdlMixer::_playACMMusic(const std::string &filename, bool loop) {
            auto acm = ResourceManager::getInstance()->acmFileType(Game::getInstance()->settings()->musicPath() + filename);
            if (!acm) {
                return;
            }
            auto sound = std::make_shared<AcmSound>(acm);
            sound->setLooped(loop);
            play(Channel::Music, sound);
        }

        void SdlMixer::_playACMSpeech(const std::string &filename) {
            auto acm = ResourceManager::getInstance()->acmFileType("sound/speech/" + filename);
            if (!acm) {
                return;
            }
            play(Channel::Speech, std::make_shared<AcmSound>(acm));
        }

        void SdlMixer::_playACMSound(const std::string &filename) {
            auto acm = ResourceManager::getInstance()->acmFileType(filename);
            if (!acm) {
                return;
            }
            play(Channel::Effects, std::make_shared<AcmSound>(acm));
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

        void SdlMixer::play(Channel channel, std::shared_ptr<ISound> sound) {
            _sounds.at(channel).push_back(sound);
        }

        void SdlMixer::stopChannel(Channel channel) {
            // TODO
        }

        void SdlMixer::pauseChannel(Channel channel) {
            // TODO
        }

        void SdlMixer::resumeChannel(Channel channel) {
            // TODO
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
            _volumes[channel] = volume;
        }

        double SdlMixer::channelVolume(Channel channel) {
            std::cout << _volumes[channel] << std::endl;
            return _volumes[channel];
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

        void SdlMixer::_mixChannels(uint8_t *stream, uint32_t bytes)
        {
            auto master = new uint8_t[bytes]{0};
            for (auto &map : _sounds) {

                auto channel = map.first;
                // Mix each sound from the channel to master channel
                for (auto &sound : map.second) {
                    auto buffer = new uint8_t[bytes]{0};
                    sound->readSamples(buffer, bytes);
                    _mixBuffers(channelVolume(channel), (int16_t*) buffer, (int16_t*) master, bytes/2);
                    delete [] buffer;
                }

                // Remove sounds that are finished
                map.second.remove_if([](std::shared_ptr<ISound> sound) {
                    if (sound->samplesAvailable() == 0) {
                        if (sound->looped()) {
                            sound->rewind();
                            return false;
                        }
                        return true;
                    }
                    return false;
                });
            }
            memset(stream, 0, bytes);
            _mixBuffers(masterVolume(), (int16_t*) master, (int16_t*) stream, bytes/2);
            delete [] master;
        }

        void SdlMixer::_mixBuffers(double volume, int16_t *source, int16_t *destination, uint32_t samples) {
            // adjust volume and put to destination
            for (uint32_t i = 0; i < samples; i++) {
                int16_t adjusted = source[i] * volume;
                destination[i] += adjusted;
            }
        }
    }
}
