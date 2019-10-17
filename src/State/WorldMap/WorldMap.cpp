#include "./WorldMap.h"

namespace Falltergeist
{
    namespace State
    {
        WorldMap::WorldMap() : State()
        {
        }

        WorldMap::~WorldMap()
        {
        }

        void WorldMap::init()
        {
            if (_initialized) return;
            State::init();
            initTiles();
            initHotspot();
            initPanel();
        }

        void WorldMap::render()
        {
            // MAP SHOW
            // calculating delta (shift of map to fit to screen)
            setDelta(&deltaX, &deltaY);
            // prevent negative delta values
            correctDelta(&deltaX, &deltaY);
            // render the tiles in visible area
            renderTiles();
            // render ui elements
            renderHotspot();
            renderPanel();
        }

    }
}
