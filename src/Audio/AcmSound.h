#pragma once

#include "../Audio/ISound.h"

namespace Falltergeist {
    namespace Format {
        namespace Acm {
            class File;
        }
    }
    namespace Audio {
        class AcmSound : public ISound {
        public:
            AcmSound(Format::Acm::File *acmFile);
            ~AcmSound() override;
            uint32_t readSamples(uint8_t *audioBuffer, uint32_t bytes) override;
        private:
            Format::Acm::File* acmFile = nullptr; // TODO use smart pointer instead
        };
    }
}
