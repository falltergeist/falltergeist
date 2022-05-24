// Project includes
#include "../Graphics/AnimatedPalette.h"

// Third-party includes

// stdlib

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

        void AnimatedPalette::think(const float &deltaTime)
        {
            _monitorsMillisecondsTracked += deltaTime;
            if (_monitorsMillisecondsTracked >= 100.0f) {
                _monitorsMillisecondsTracked -= 100.0f;
                _monitorsCounter++;
                if (_monitorsCounter >= 5) {
                    _monitorsCounter = 0;
                }
            }

            _slimeMillisecondsTracked += deltaTime;
            if (_slimeMillisecondsTracked >= 200.0f) {
                _slimeMillisecondsTracked -= 200.0f;
                _slimeCounter++;
                if (_slimeCounter >= 4) {
                    _slimeCounter = 0;
                }
            }

            _shoreMillisecondsTracked += deltaTime;
            if (_shoreMillisecondsTracked >= 200.0f) {
                _shoreMillisecondsTracked -= 200.0f;
                _shoreCounter++;
                if (_shoreCounter >= 6) {
                    _shoreCounter = 0;
                }
            }

            _fireSlowMillisecondsTracked += deltaTime;
            if (_fireSlowMillisecondsTracked >= 200.0f) {
                _fireSlowMillisecondsTracked -= 200.0f;
                _fireSlowCounter++;
                if (_fireSlowCounter >= 5) {
                    _fireSlowCounter = 0;
                }
            }

            _fireFastMillisecondsTracked += deltaTime;
            if (_fireFastMillisecondsTracked >= 142.0f) {
                _fireFastMillisecondsTracked -= 142.0f;
                _fireFastCounter++;
                if (_fireFastCounter >= 5) {
                    _fireFastCounter = 0;
                }
            }

            _blinkingRedMillisecondsTracked += deltaTime;
            if (_blinkingRedMillisecondsTracked >= 33.0f) {
                _blinkingRedMillisecondsTracked -= 33.0f;
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
