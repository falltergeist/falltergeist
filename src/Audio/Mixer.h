#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

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

            private:
                void _init();
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
