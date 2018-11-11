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
#include "../Audio/AcmSound.h"

// C++ standard includes
#include <cstring>

// Falltergeist includes
#include "../Base/Buffer.h"
#include "../Format/Acm/File.h"

// Third party includes

namespace Falltergeist {
    namespace Audio {
        AcmSound::AcmSound(Format::Acm::File *acmFile) : acmFile(acmFile) {
        }

        uint32_t AcmSound::readSamples(uint8_t *audioBuffer, uint32_t bytes) {
            if (acmFile->samplesLeft() <= 0) {
                memset(audioBuffer, 0, bytes);
                return 0;
            }

            Base::Buffer<uint16_t> tmp(bytes / 2);
            uint16_t *sstr = (uint16_t *) audioBuffer;
            // TODO check if requested bytes cout is available
            acmFile->readSamples(tmp.data(), bytes / 4);
            for (size_t i = 0; i < bytes / 4; i++) {
                sstr[i * 2] = tmp[i];
                sstr[i * 2 + 1] = tmp[i];
            }

            return bytes;
        }
    }
}