#pragma once

#include <cstdint>

namespace Falltergeist {
    namespace Audio {
        class ISound {
        public:
            virtual ~ISound() = default;
            virtual uint32_t readSamples(uint8_t *audioBuffer, uint32_t bytes) = 0;
        };
    }
}