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
#include "../Audio/MveSound.h"

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"
#include "../UI/MvePlayer.h"

// Third party includes

namespace Falltergeist {
    namespace Audio {
        MveSound::MveSound(Falltergeist::UI::MvePlayer *mvePlayer) : _mvePlayer(mvePlayer) {
        }

        uint8_t MveSound::channels() {
            return 2;
        }

        uint32_t MveSound::sampleRate() {
            return 22050;
        }

        void MveSound::rewind() {
            throw Exception("Not implemented");
        }

        uint32_t MveSound::samplesAvailable() {
            return _mvePlayer->samplesLeft();
        }

        uint32_t MveSound::readSamples(uint8_t *audioBuffer, uint32_t bytes) {
            if (_mvePlayer->samplesLeft() <= 0) {
                memset(audioBuffer, 0, bytes);
                return 0;
            }

            return _mvePlayer->getAudio(audioBuffer, bytes);
        }

        bool MveSound::looped() {
            return _looped;
        }

        void MveSound::setLooped(bool value) {
            _looped = value;
        }
    }
}