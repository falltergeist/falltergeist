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

#pragma once

// C++ standard includes
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <unordered_map>

// Falltergeist includes
#include "../Audio/IMixer.h"

// Third party includes
#include <SDL_mixer.h>

namespace Falltergeist {
    namespace UI {
        class MvePlayer;
    }
    namespace Audio {
        class SdlMixer : public IMixer {
            public:
                SdlMixer();
                ~SdlMixer() override;

                void playLooped(Channel channel, const std::string& filename) override;
                void playOnce(Channel channel, const std::string& filename) override;
                void playLooped(Channel channel, std::shared_ptr<ISound> sound) override;
                void playOnce(Channel channel, std::shared_ptr<ISound> sound) override;
                void stopChannel(Channel channel) override;
                void pauseChannel(Channel channel) override;
                void resumeChannel(Channel channel) override;
                void setMasterVolume(double volume) override;
                double masterVolume() override;
                void setChannelVolume(Channel channel, double volume) override;
                double channelVolume(Channel channel) override;

            private:
                void _init();
                void _playACMMusic(const std::string& filename, bool loop);
                void _playACMSpeech(const std::string& filename);
                void _playACMSound(const std::string& filename);

                void _initChannels();
                double _masterVolume = 1.0;
                std::map<Channel, double> _volumes;
                std::map<Channel, std::list<std::shared_ptr<ISound>>> _sounds;
                SDL_AudioFormat _format;
                std::shared_ptr<ISound> _sound = nullptr;
                double _normalizeVolume(double volume);
        };
    }
}
