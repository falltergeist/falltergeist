#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>
#include "../Format/Enums.h"
#include "../Graphics/Renderer.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class AnimatedPalette
        {
            public:
                AnimatedPalette();
                ~AnimatedPalette();

                std::vector<GLuint> counters();
                void think(const float &deltaTime);

            protected:

                float _slimeMillisecondsTracked = 0;
                unsigned int _slimeCounter = 0;
                float _fireSlowMillisecondsTracked = 0;
                unsigned int _fireSlowCounter = 0;
                float _fireFastMillisecondsTracked = 0;
                unsigned int _fireFastCounter = 0;
                float _monitorsMillisecondsTracked = 0;
                unsigned int _monitorsCounter = 0;
                float _shoreMillisecondsTracked = 0;
                unsigned int _shoreCounter = 0;
                float _blinkingRedMillisecondsTracked = 0;
                unsigned char _blinkingRedCounter = 0;
                short _blinkingRed = -1;
        };
    }
}
