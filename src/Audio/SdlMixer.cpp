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
            _initChannels();
        }

        void SdlMixer::_initChannels() {
            _volumes.insert(std::make_pair<Channel, double>(Channel::Music, 1.0f));
            _volumes.insert(std::make_pair<Channel, double>(Channel::Speech, 1.0f));
            _volumes.insert(std::make_pair<Channel, double>(Channel::Effects, 1.0f));
            _sounds.insert(
                std::make_pair<Channel, std::list<std::shared_ptr<ISound>>>(
                    Channel::Music,
                    {}
                )
            );
            _sounds.insert(
                std::make_pair<Channel, std::list<std::shared_ptr<ISound>>>(
                    Channel::Speech,
                    {}
                )
            );
            _sounds.insert(
                std::make_pair<Channel, std::list<std::shared_ptr<ISound>>>(
                    Channel::Effects,
                    {}
                )
            );
        }

        void SdlMixer::_playACMMusic(const std::string &filename, bool loop) {
            auto acm = ResourceManager::getInstance()->acmFileType(Game::getInstance()->settings()->musicPath() + filename);
            if (!acm) {
                return;
            }
            if (loop) {
                playOnce(Channel::Music, std::make_shared<AcmSound>(acm));
            } else {
                playLooped(Channel::Music, std::make_shared<AcmSound>(acm));
            }
        }

        void SdlMixer::_playACMSpeech(const std::string &filename) {
            auto acm = ResourceManager::getInstance()->acmFileType("sound/speech/" + filename);
            if (!acm) {
                return;
            }
            playOnce(Channel::Speech, std::make_shared<AcmSound>(acm));
        }

        void SdlMixer::_playACMSound(const std::string &filename) {
            auto acm = ResourceManager::getInstance()->acmFileType(filename);
            if (!acm) {
                return;
            }
            playOnce(Channel::Effects, std::make_shared<AcmSound>(acm));
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
            Mix_HookMusic(NULL, NULL);
            Mix_HookMusic([](void *udata, Uint8 *stream, int len) {
                auto sound = (ISound*)(udata);
                sound->readSamples(stream, (uint32_t)len);
            }, reinterpret_cast<void *>(sound.get()));
        }

        void SdlMixer::playLooped(Channel channel, std::shared_ptr<ISound> sound) {
            // TODO implement looping
            playOnce(channel, sound);
        }

        void SdlMixer::stopChannel(Channel channel) {
            // TODO
            Mix_HookMusic(NULL, NULL);
            //Mix_HaltChannel(-1);
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
