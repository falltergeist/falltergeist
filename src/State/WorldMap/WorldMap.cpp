#include "./WorldMap.h"
#include "./../../Game/Game.h"
#include "./../../Audio/Mixer.h"

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

            setPanelOffset();

            if (hasCar) {
                Game::getInstance()->mixer()->playACMMusic("20car.acm",true);
            }else{
                Game::getInstance()->mixer()->playACMMusic("23world.acm",true);
            }

        }

        void WorldMap::render()
        {
            // MAP SHOW
            // calculating delta (shift of map to fit to screen)
            setDelta();
            // prevent negative delta values
            correctDelta();
            // render the tiles in visible area
            renderTiles();
            // render ui elements
            renderHotspot();
            renderPanel();
        }

        void WorldMap::exit()
        {
            Game::getInstance()->mixer()->stopMusic();
        }

    }
}
