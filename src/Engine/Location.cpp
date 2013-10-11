#include "../Engine/Location.h"
#include <cmath>

namespace Falltergeist
{

Location::Location(unsigned int cols = 100, unsigned int rows = 100) : InteractiveSurface()
{
    _cols = cols;
    _rows = rows;
}

void Location::init()
{
    //Surface()
}

int Location::hexagonToX(unsigned int hexagon)
{
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerX = 48*(_cols-1) + 48 + 16*(hexagon%200) - 24*y;

        if (((unsigned int)ceil(hexagon/200))%2 == 1)
        {
            centerX += 8;
        }
    return centerX;
}

int Location::hexagonToY(unsigned int hexagon)
{
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerY = (hexagon%200)*12 + 6*y ;

        if (((unsigned int)ceil(hexagon/200))%2 == 1)
        {
            centerY += 6;
        }
    return centerY;

}

}
