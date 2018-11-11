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

// Falltergeist includes
#include "../Audio/ISound.h"

// Third party includes

namespace Falltergeist {
    namespace Format {
        namespace Acm {
            class File;
        }
    }
    namespace Audio {
        class AcmSound : public ISound {
        public:
            explicit AcmSound(Format::Acm::File *acmFile);
            ~AcmSound() override = default;
            uint8_t channels() override;
            uint32_t sampleRate() override;
            void rewind() override;
            uint32_t samplesAvailable() override;
            uint32_t readSamples(uint8_t *audioBuffer, uint32_t bytes) override;
        private:
            Format::Acm::File* acmFile = nullptr; // TODO use smart pointer instead
        };
    }
}
