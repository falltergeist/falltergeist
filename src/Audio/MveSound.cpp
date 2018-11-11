#include "../Audio/MveSound.h"
#include "../UI/MvePlayer.h"

namespace Falltergeist {
    namespace Audio {
        MveSound::MveSound(Falltergeist::UI::MvePlayer *mvePlayer) : mvePlayer(mvePlayer) {
        }

        MveSound::~MveSound() {
        }

        uint32_t MveSound::readSamples(uint8_t *audioBuffer, uint32_t bytes) {
            if (mvePlayer->samplesLeft() <= 0) {
                memset(audioBuffer, 0, bytes);
                return 0;
            }

            return mvePlayer->getAudio(audioBuffer, bytes);
        }
    }
}