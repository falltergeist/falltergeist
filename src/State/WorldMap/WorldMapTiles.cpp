#include "./WorldMap.h"
#include "../../UI/ImageList.h"
#include "../../UI/Image.h"

namespace Falltergeist
{
    namespace State
    {

        void WorldMap::initTiles()
        {
            _tiles = new UI::ImageList(_worldMapTiles, 0, 0);
        }

        void WorldMap::setDelta(signed int* deltaX, signed int* deltaY){
            *deltaX = worldMapX - mapWidth/2;
            *deltaY = worldMapY - mapHeight/2;
        }

        void WorldMap::correctDelta(signed int* deltaX, signed int* deltaY){
            unsigned int worldMapSizeX = tilesNumberX*tileWidth;
            unsigned int worldMapSizeY = tilesNumberY*tileHeight;
            if (*deltaX<0)
            {
                *deltaX = 0;
            }
            if (*deltaY<0)
            {
                *deltaY = 0;
            }
            if (worldMapSizeX-*deltaX < mapWidth)
            {
                *deltaX = worldMapSizeX - mapWidth;
            }
            if (worldMapSizeY-*deltaY < mapHeight)
            {
                *deltaY = worldMapSizeY - mapHeight;
            }
        }

        void WorldMap::renderTiles()
        {
            signed int worldTileMinX; // start X coordinate of current tile on world map
            signed int worldTileMinY; // start Y coordinate of current tile on world map
            // NB: can be unsigned, but it compared with signed deltaX and deltaY, so...

            // copy tiles to screen if needed
            for (unsigned int y=0; y<tilesNumberY; y++)
            {
                for (unsigned int x=0; x<tilesNumberX; x++)
                {
                    _tiles->setCurrentImage(y*tilesNumberX+x);
                    worldTileMinX = x*tileWidth;
                    worldTileMinY = y*tileHeight;
                    // checking if tile is visible on screenMap
                    // checking current tile borders
                    // either xmin or xmax SHOULD belongs to map area AND
                    // either ymin or ymax SHOULD belongs to map area
                    if(

                        (((deltaX<=worldTileMinX) &&
                        (worldTileMinX<=deltaX+(signed int)mapWidth)) ||
                        ((deltaX<=worldTileMinX+(signed int)tileWidth) &&
                        (worldTileMinX+(signed int)tileWidth<=deltaX+(signed int)mapWidth)))

                        &&

                        (((deltaY<=worldTileMinY) && (worldTileMinY<=deltaY+(signed int)mapHeight)) ||
                        ((deltaY<=worldTileMinY+(signed int)tileHeight) &&
                        (worldTileMinY+(signed int)tileHeight<=deltaY+(signed int)mapHeight)))

                        )
                    {
                        _tiles->images().at(y*tilesNumberX+x)->setPosition(Point(x*tileWidth-deltaX, y*tileHeight-deltaY));
                        _tiles->images().at(y*tilesNumberX+x)->render();
                    }
                }
            }
        }

    }
}
