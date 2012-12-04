#ifndef FALLTERGEIST_FPSCOUNTER_H
#define FALLTERGEIST_FPSCOUNTER_H

#include "src/UI/TextArea.h"

namespace Falltergeist
{

class FpsCounter : public TextArea
{
protected:
    unsigned int _lastTicks;
    unsigned int _frames;
public:
    void think();
    FpsCounter(int x = 598, int y = 2);
};

}
#endif // FALLTERGEIST_FPSCOUNTER_H
