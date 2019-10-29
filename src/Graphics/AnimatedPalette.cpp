#include "../Graphics/AnimatedPalette.h"

namespace Falltergeist
{
    namespace Graphics
    {
        AnimatedPalette::AnimatedPalette()
        {
        }

        AnimatedPalette::~AnimatedPalette()
        {
        }

        void AnimatedPalette::think(uint32_t nanosecondsPassed)
        {
            _monitorsNanosecondsTracked += nanosecondsPassed;
            if (_monitorsNanosecondsTracked >= 1e8) { // 100 ms
                _monitorsNanosecondsTracked -= 1e8;
                _monitorsCounter++;
                if (_monitorsCounter >= 5) {
                    _monitorsCounter = 0;
                }
            }

            _slimeNanosecondsTracked += nanosecondsPassed;
            if (_slimeNanosecondsTracked >= 2e8) { // 200 ms
                _slimeNanosecondsTracked -= 2e8;
                _slimeCounter++;
                if (_slimeCounter >= 4) {
                    _slimeCounter = 0;
                }
            }

            _shoreNanosecondsTracked += nanosecondsPassed;
            if (_shoreNanosecondsTracked >= 2e8) { // 200 ms
                _shoreNanosecondsTracked -= 2e8;
                _shoreCounter++;
                if (_shoreCounter >= 6) {
                    _shoreCounter = 0;
                }
            }

            _fireSlowNanosecondsTracked += nanosecondsPassed;
            if (_fireSlowNanosecondsTracked >= 2e8) { // 200 ms
                _fireSlowNanosecondsTracked -= 2e8;
                _fireSlowCounter++;
                if (_fireSlowCounter >= 5) {
                    _fireSlowCounter = 0;
                }
            }

            _fireFastNanosecondsTracked += nanosecondsPassed;
            if (_fireFastNanosecondsTracked >= 142 * 1e6) { // 142 ms
                _fireFastNanosecondsTracked -= 142 * 1e6;
                _fireFastCounter++;
                if (_fireFastCounter >= 5) {
                    _fireFastCounter = 0;
                }
            }

            _blinkingRedNanosecondsTracked += nanosecondsPassed;
            if (_blinkingRedNanosecondsTracked >= 33 * 1e6){ // 33 ms
                _blinkingRedNanosecondsTracked -= 33 * 1e6;
                if ((_blinkingRedCounter == 0) || (_blinkingRedCounter == 15)) {
                    _blinkingRed = -_blinkingRed;
                }

                _blinkingRedCounter = _blinkingRed + _blinkingRedCounter;
            }
        }

        std::vector<GLuint> AnimatedPalette::counters()
        {
            std::vector<GLuint> cnt;
            cnt.reserve(6);
            cnt.push_back(_slimeCounter);
            cnt.push_back(_monitorsCounter);
            cnt.push_back(_fireSlowCounter);
            cnt.push_back(_fireFastCounter);
            cnt.push_back(_shoreCounter);
            cnt.push_back(_blinkingRedCounter);
            return cnt;
        }
    }
}
