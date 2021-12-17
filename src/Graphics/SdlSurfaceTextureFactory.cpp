#include "../Graphics/SdlSurfaceTextureFactory.h"
#include <cstring>

namespace Falltergeist {
    namespace Graphics {
        std::unique_ptr<Texture> SdlSurfaceTextureFactory::createFromSurface(SDL_Surface* sdlSurface) {
            std::unique_ptr<Texture::RgbaPixels> pixels = std::make_unique<Texture::RgbaPixels>();
            pixels->resize(sdlSurface->w * sdlSurface->h);
            std::memcpy(pixels->data(), sdlSurface->pixels, pixels->size() * sizeof(uint32_t));
            return std::make_unique<Texture>(pixels, sdlSurface->w, sdlSurface->h);
        }

        unsigned int SdlSurfaceTextureFactory::NearestPowerOf2(unsigned int n) {
            if (!n) return n; //(0 == 2^0)
            int x = 1;
            while (x < n) {
                x <<= 1;
            }
            return x;
        }
    }
}
