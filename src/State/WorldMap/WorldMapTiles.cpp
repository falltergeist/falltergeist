#include "./WorldMap.h"
#include "../../UI/ImageList.h"
#include "../../UI/Image.h"
#include "../../Game/Game.h"
#include "../../Logger.h"

namespace Falltergeist
{
    namespace State
    {

        void WorldMap::initTiles()
        {
            _tiles = new UI::ImageList(_worldMapTiles, 0, 0);
        }

        void WorldMap::setDelta()
        {
            deltaX = worldMapX - mapWidth/2;
            deltaY = worldMapY - mapHeight/2;
        }

        void WorldMap::correctDelta()
        {
            deltaNegativeToZero(&deltaX);
            deltaToMax('x', &deltaX, tilesNumberX, tileWidth, mapWidth);
            deltaNegativeToZero(&deltaY);
            deltaToMax('y', &deltaY, tilesNumberY, tileHeight, mapHeight);
        }

        void WorldMap::deltaNegativeToZero(signed int* delta)
        {
            *delta = *delta < 0 ?  0 - panelBorder : *delta;
        };

        void WorldMap::deltaToMax(const char orientation, signed int* delta, signed int tilesNumber, signed int tileDimension, signed int mapDimension)
        {
            signed int worldMapSize = (tilesNumber * tileDimension) - panelBorder;
            if (worldMapSize - *delta < mapDimension)
            {
                *delta = worldMapSize - mapDimension;
            }
        };

        bool WorldMap::inRenderView(const char orientation, signed int worldTileMin){
            if (orientation == 'x')
            {
                bool inXmin = (
                    (deltaX <= worldTileMin) &&
                    (worldTileMin <= deltaX + (signed int)mapWidth)
                );
                bool inXmax = ((deltaX<=worldTileMin+(signed int)tileWidth) &&
                        (worldTileMin+(signed int)tileWidth<=deltaX+(signed int)mapWidth));
                return  inXmin || inXmax;
            }
            else
            {
                bool inYmin = ((deltaY<=worldTileMin) &&
                        (worldTileMin<=deltaY+(signed int)mapHeight));
                bool inYmax = ((deltaY<=worldTileMin+(signed int)tileHeight) &&
                        (worldTileMin+(signed int)tileHeight<=deltaY+(signed int)mapHeight));
                return  inYmin || inYmax;
            }
        };

        void WorldMap::renderTiles()
        {
            signed int tileMinX; // start X coordinate of current tile on world map
            signed int tileMinY; // start Y coordinate of current tile on world map
            // NB: can be unsigned, but it compared with signed deltaX and deltaY, so...

            // copy tiles to screen if needed
            for (unsigned int y=0; y<tilesNumberY; y++)
            {
                for (unsigned int x=0; x<tilesNumberX; x++)
                {
                    _tiles->setCurrentImage(y*tilesNumberX+x);
                    tileMinX = x*tileWidth;
                    tileMinY = y*tileHeight;
                    // checking if tile is visible on screenMap
                    // checking current tile borders
                    // either xmin or xmax SHOULD belongs to map area AND
                    // either ymin or ymax SHOULD belongs to map area
                    // if(inRenderView('x', tileMinX) && inRenderView('y', tileMinY) )
                    // {
                        _tiles->images().at(y*tilesNumberX+x)->setPosition(Point(x*tileWidth-deltaX + offsetX, y*tileHeight-deltaY + offsetY));
                        _tiles->images().at(y*tilesNumberX+x)->render();
                    // }
                }
            }
        }

    }
}
