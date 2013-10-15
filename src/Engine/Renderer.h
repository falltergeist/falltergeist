#ifndef FALLTERGEIST_RENDERER_H
#define FALLTERGEIST_RENDERER_H

namespace Falltergeist
{

class Renderer
{
protected:
    unsigned int _frameLimit;

public:
    Renderer();
    ~Renderer();
    unsigned int frameLimit();
};

}
#endif // FALLTERGEIST_RENDERER_H
