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
                void think(uint32_t nanosecondsPassed);

            protected:

                unsigned int _slimeNanosecondsTracked = 0;
                unsigned int _slimeCounter = 0;
                unsigned int _fireSlowNanosecondsTracked = 0;
                unsigned int _fireSlowCounter = 0;
                unsigned int _fireFastNanosecondsTracked = 0;
                unsigned int _fireFastCounter = 0;
                unsigned int _monitorsNanosecondsTracked = 0;
                unsigned int _monitorsCounter = 0;
                unsigned int _shoreNanosecondsTracked = 0;
                unsigned int _shoreCounter = 0;
                unsigned int _blinkingRedNanosecondsTracked = 0;
                unsigned char _blinkingRedCounter = 0;
                short _blinkingRed = -1;
        };
    }
}
