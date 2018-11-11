#pragma once

#include <memory>

#include "../Audio/ISound.h"

namespace Falltergeist {
    namespace UI {
        class MvePlayer;
    }
    namespace Audio {
        class MveSound : public ISound {
        public:
            MveSound(UI::MvePlayer *mvePlayer);
            ~MveSound() override;
            uint32_t readSamples(uint8_t *audioBuffer, uint32_t bytes) override;
        private:
            UI::MvePlayer *mvePlayer = nullptr; // TODO replace with smart pointer
        };
    }
}
