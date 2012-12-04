#ifndef FALLTERGEIST_BIGCOUNTER_H
#define FALLTERGEIST_BIGCOUNTER_H

#include "../Engine/InteractiveSurface.h"
#include <vector>

namespace Falltergeist
{

class BigCounter : public InteractiveSurface
{
protected:
    unsigned int _number;
    unsigned int _length;
    std::vector<Surface *> * _numbersWhite;
    std::vector<Surface *> * _numbersRed;
public:
    BigCounter(int x = 0, int y = 0);
    ~BigCounter();
    void draw();
    void setNumber(unsigned int number);
};

}
#endif // FALLTERGEIST_BIGCOUNTER_H
