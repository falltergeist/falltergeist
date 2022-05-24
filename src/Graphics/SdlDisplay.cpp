// Project includes
#include "../Graphics/SdlDisplay.h"
#include "../Exception.h"

// Third-party includes
#include <SDL.h>

// stdlib

namespace Falltergeist::Graphics {
    SdlDisplay::SdlDisplay(unsigned int number, const Rectangle& boundaries) : _number(number), _boundaries(boundaries) {
    }

    unsigned int SdlDisplay::number() const {
        return _number;
    }

    const Rectangle& SdlDisplay::boundaries() const {
        return _boundaries;
    }

    std::vector<SdlDisplay> SdlDisplay::getAvailableDisplays() {
        int displays = SDL_GetNumVideoDisplays();
        if (displays < 0) {
            throw Exception(std::string("Could not get displays number: ") + SDL_GetError());
        }

        std::vector<SdlDisplay> result;

        SDL_Rect displayBounds = {};
        for(unsigned int i = 0; i < displays; i++ ) {
            if (SDL_GetDisplayBounds(i, &displayBounds) < 0) {
                throw Exception(std::string("Could not get display '") + std::to_string(i) + "' bounds: " + SDL_GetError());
            }

            result.push_back(SdlDisplay(i, Rectangle(Point(displayBounds.x, displayBounds.y), Size(displayBounds.w, displayBounds.h))));
        }

        return result;
    }
}
