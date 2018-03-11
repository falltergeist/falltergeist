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

#ifndef FALLTERGEIST_AUDIO_MIXER_H
#define FALLTERGEIST_AUDIO_MIXER_H

#include <SDL_mixer.h>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace Falltergeist
{
    namespace UI
    {
        class MvePlayer;
    }
    namespace Audio
    {
        class Mixer
        {
            public:
                Mixer();
                ~Mixer();
                void stopMusic();
                void stopSounds();
                void playACMMusic(const std::string& filename, bool loop = false);
                void playACMSpeech(const std::string& filename);
                void playACMSound(const std::string& filename);
                void playMovieMusic(UI::MvePlayer* mve);
                void pauseMusic();
                void resumeMusic();
                std::string& lastMusic();
                /**
                 * @return current music volume
                 */
                double musicVolume();
                /**
                 * @brief Sets volume of music
                 * @param volume from 0.0 to 1.0
                 */
                void setMusicVolume(double volume);

            protected:
                void _init();

            private:
                void _musicCallback(void* udata, uint8_t* stream, uint32_t len);
                void _speechCallback(void* udata, uint8_t* stream, uint32_t len);
                void _movieCallback(void* udata, uint8_t* stream, uint32_t len);
                std::unordered_map<std::string, Mix_Chunk*> _sfx;
                bool _paused = false;
                bool _loop = false;

                double _musicVolume = 1.0;
                SDL_AudioFormat _format;
                std::string _lastMusic = "";
        };
    }
}
#endif // FALLTERGEIST_AUDIO_MIXER_H
