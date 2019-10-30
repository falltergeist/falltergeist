#include "./WorldMap.h"

namespace Falltergeist
{
    namespace State
    {

        void WorldMap::travel()
        {
            if (!isTraveling)
            {
                return;
            }

            float speed = hasCar ? 1 : 0.5;

            nextWorldMapX += (1.0 * speed) * directionHorizontal;
            nextWorldMapY += (1.0 * speed) * directionVertical;

            preventTravelOutboundMin(&nextWorldMapX);
            preventTravelOutboundMax(&nextWorldMapX, worldMapX, (tilesNumberX * tileWidth) );
            preventTravelOutboundMin(&nextWorldMapY);
            preventTravelOutboundMax(&nextWorldMapY, worldMapY, (tilesNumberY * tileHeight) );

            worldMapX = nextWorldMapX;
            worldMapY = nextWorldMapY;

            isTraveling = false;
            directionHorizontal = 0;
            directionVertical = 0;

        }

        void WorldMap::preventTravelOutboundMin(float* nextPosition)
        {
            *nextPosition = *nextPosition < 0 ? 0 : *nextPosition;
        }

        void WorldMap::preventTravelOutboundMax(float* nextPosition, float currentPosition, int maxRange)
        {
            *nextPosition = *nextPosition > maxRange ? currentPosition : *nextPosition;
        }

        int WorldMap::setDestination(const char orientation, unsigned int clickPosition)
        {
            if (orientation == 'x')
            {
                return clickPosition + deltaX - mapMinX;
            }
            if(orientation == 'y')
            {
                return clickPosition + deltaY - mapMinY;
            }
        }

    } // namespace State
} // namespace Falltergeist
