// C++ standard includes
#include <string>

// Falltergeist includes
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"
#include "../../Engine/Graphics/SDLRenderer.h"

//Third party includes
#include "SDL.h"

namespace Falltergeist
{

SDLRenderer::SDLRenderer(unsigned int width, unsigned int height) : Renderer(width, height)
{
    std::string message = "[VIDEO] - SDL Renderer initialization - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        debug(message + "[FAIL]", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
    debug(message + "[OK]", DEBUG_INFO);
}

void SDLRenderer::init()
{
    Renderer::init();

    std::string message =  "[VIDEO] - SDL_SetVideoMode " + std::to_string(_width) + "x" + std::to_string(_height) + "x" +std::to_string(32)+ " - ";
    if (!SDL_SetVideoMode(_width, _height, 32, SDL_SWSURFACE|SDL_DOUBLEBUF))
    {
        throw Exception(message + "[FAIL]");
    }
    debug(message + "[OK]", DEBUG_INFO);
}

void SDLRenderer::beginFrame()
{
    SDL_FillRect(SDL_GetVideoSurface(), NULL, 0x000000FF);
    Renderer::beginFrame();

}

void SDLRenderer::endFrame()
{
    Renderer::endFrame();
    SDL_Flip(SDL_GetVideoSurface());

}

void SDLRenderer::registerTexture(Texture* texture)
{
    Renderer::registerTexture(texture);
    if (texture->id()) return; // if registered

    // Creating SDL surface                                                                            //red       //green     //blue      //alpha
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SRCALPHA, texture->width(), texture->height(), 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if (surface == 0) throw Exception(SDL_GetError());
    // Copying data from texture to surface
    unsigned int* pixels = (unsigned int*) surface->pixels;
    for (unsigned int i = 0; i != texture->width()*texture->height(); ++i)
    {
        pixels[i] = texture->data()[i];
    }
    // Saving pointer to surface
    _surfaces.push_back(surface);

    texture->setId(_texturesCounter);
    _texturesCounter++;
}

void SDLRenderer::drawTexture(unsigned int x, unsigned int y, Texture* texture)
{
    Renderer::drawTexture(x, y, texture);

    if (!texture->id()) registerTexture(texture);

    SDL_Rect dest = {x, y, texture->width(), texture->height()};
    SDL_BlitSurface(_surfaces.at(texture->id() - 1), NULL, SDL_GetVideoSurface(), &dest);
}

}
