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

// Falltergeist includes

// Third party includes

namespace Falltergeist {
    namespace Audio {
        class ISound {
        public:
            virtual ~ISound() = default;
            virtual uint8_t channels() = 0;
            virtual uint32_t sampleRate() = 0;
            virtual void rewind() = 0;
            virtual uint32_t samplesAvailable() = 0;
            virtual uint32_t readSamples(uint8_t *audioBuffer, uint32_t bytes) = 0;
            virtual bool looped() = 0;
            virtual void setLooped(bool value) = 0;
        };
    }
}