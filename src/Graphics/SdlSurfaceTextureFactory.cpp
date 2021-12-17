#include "../Graphics/SdlSurfaceTextureFactory.h"
#include <cstring>

namespace Falltergeist {
    namespace Graphics {
        std::unique_ptr<Texture> SdlSurfaceTextureFactory::createFromSurface(SDL_Surface* sdlSurface) {
            int bytesPerPixel;
            uint32_t redMask, greenMask, blueMask, alphaMask;
            SDL_PixelFormatEnumToMasks(
                    SDL_PIXELFORMAT_ABGR8888,
                    &bytesPerPixel,
                    &redMask,
                    &greenMask,
                    &blueMask,
                    &alphaMask
            );

            unsigned int newWidth = NearestPowerOf2(sdlSurface->w);
            unsigned int newHeight = NearestPowerOf2(sdlSurface->h);

            SDL_Surface* resizedSurface = SDL_CreateRGBSurface(
                    0,
                    (int) newWidth,
                    (int) newHeight,
                    bytesPerPixel,
                    redMask,
                    greenMask,
                    blueMask,
                    alphaMask
            );

            SDL_Rect area;
            area.x = 0;
            area.y = 0;
            area.w = sdlSurface->w;
            area.h = sdlSurface->h;

            SDL_SetSurfaceAlphaMod(sdlSurface, 0xFF);
            SDL_SetSurfaceBlendMode(sdlSurface, SDL_BLENDMODE_NONE);
            SDL_BlitSurface(sdlSurface, &area, resizedSurface, &area);

            std::unique_ptr<Texture::RgbaPixels> pixels = std::make_unique<Texture::RgbaPixels>();
            pixels->resize(resizedSurface->w * resizedSurface->h);
            std::memcpy(pixels->data(), resizedSurface->pixels, pixels->size() * sizeof(uint32_t));

            SDL_FreeSurface(resizedSurface);

            return std::make_unique<Texture>(pixels, sdlSurface->w, sdlSurface->h, newWidth, newHeight);
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
