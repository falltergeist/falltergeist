#pragma once

// Project includes
#include "../Graphics/Rectangle.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist {
    namespace Graphics {
        class SdlDisplay {
        public:
            SdlDisplay(unsigned int number, const Rectangle& boundaries);

            unsigned int number() const;

            const Rectangle& boundaries() const;

            static std::vector<SdlDisplay> getAvailableDisplays();

        private:
            unsigned int _number;

            Rectangle _boundaries;
        };
    }
}
