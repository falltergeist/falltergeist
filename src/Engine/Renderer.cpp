#include "../Engine/Renderer.h"

namespace Falltergeist
{

Renderer::Renderer()
{
    _frameLimit = 60;
}

Renderer::~Renderer()
{
}

unsigned int Renderer::frameLimit()
{
    return _frameLimit;
}

}
