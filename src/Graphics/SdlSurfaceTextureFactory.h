#pragma once

#include "../Graphics/Texture.h"

namespace Falltergeist {
    namespace Graphics {
        /**
         * Create Texture from SDL_Surface
         */
        class SdlSurfaceTextureFactory final {
        public:
            static std::unique_ptr<Texture> createFromSurface(SDL_Surface* sdlSurface) ;
        private:
            static unsigned int NearestPowerOf2(unsigned int n);
        };
    }
}
