#include <cstring>
#include "../Audio/AcmSound.h"
#include "../Base/Buffer.h"
#include "../Format/Acm/File.h"

namespace Falltergeist {
    namespace Audio {
        AcmSound::AcmSound(Format::Acm::File *acmFile) : acmFile(acmFile) {
        }

        AcmSound::~AcmSound() {
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