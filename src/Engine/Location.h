#ifndef FALLTERGEIST_LOCATION_H
#define FALLTERGEIST_LOCATION_H

#include "../Engine/InteractiveSurface.h"

namespace Falltergeist
{

class Location : public InteractiveSurface
{
protected:
    unsigned int _cols;
    unsigned int _rows;
public:
    Location(unsigned int cols, unsigned int rows);
    void init();
    int hexagonToX(unsigned int hexagon);
    int hexagonToY(unsigned int hexagon);
};


}

#endif // FALLTERGEIST_LOCATION_H
