#ifndef FALLTERGEIST_SDLRENDERER_H
#define FALLTERGEIST_SDLRENDERER_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../../Engine/Graphics/Renderer.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

class SDLRenderer : public Renderer
{
protected:
    unsigned int _texturesCounter = 1;
    std::vector<SDL_Surface*> _surfaces;
public:
    SDLRenderer(unsigned int width, unsigned int height);

    virtual void init();

    virtual void beginFrame();
    virtual void endFrame();

    virtual void registerTexture(Texture* texture);
    virtual void drawTexture(unsigned int x, unsigned int y, Texture* texture);
};

}
#endif // FALLTERGEIST_SDLRENDERER_H
