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

#ifndef FALLTERGEIST_AUDIOMIXER_H
#define FALLTERGEIST_AUDIOMIXER_H

// C++ standard includes
#include <cstdint>

// Falltergeist includes
#include <libfalltergeist.h>

// Third party includes
#include <SDL_mixer.h>

namespace Falltergeist
{
class MvePlayer;
class AudioMixer
{
protected:
    void _init();
public:
    AudioMixer();
    ~AudioMixer();
    void stopMusic();
    void stopSounds();
    void playACMMusic(std::shared_ptr<libfalltergeist::AcmFileType> acm, bool loop = false);
    void playACMSound(std::shared_ptr<libfalltergeist::AcmFileType> acm);
    void playMovieMusic(MvePlayer* mve);
    void pauseMusic();
    void resumeMusic();
private:
    void _musicCallback(void *udata, uint8_t *stream, uint32_t len);
    void _movieCallback(void *udata, uint8_t *stream, uint32_t len);
    std::map<std::string,Mix_Chunk*> _sfx;
    bool _paused = false;
    bool _loop = false;
};

}
#endif // FALLTERGEIST_AUDIOMIXER_H
