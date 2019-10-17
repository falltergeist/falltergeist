#include "./WorldMap.h"
#include "../../Game/Game.h"
#include "../../Input/Mouse.h"

namespace Falltergeist
{
    namespace State
    {

        void WorldMap::handle(Event::Event* event)
        {
            auto game = Game::getInstance();

            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                auto mouse = game->mouse();

                // Left button down
                if (mouseEvent->name() == "mousedown" && mouseEvent->leftButton())
                {
                    // check if point clicked belongs to the screen
                    if ((mapMinX<=(unsigned int)mouse->x()) && ((unsigned int)mouse->x()<=(mapMinX+mapWidth)) &&
                        (mapMinY<=(unsigned int)mouse->y()) && ((unsigned int)mouse->y()<=(mapMinY+mapHeight)))
                    {
                        // change destination point
                        worldMapX = mouse->x()+deltaX-mapMinX;
                        worldMapY = mouse->y()+deltaY-mapMinY;
                    }
                }
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                if (keyboardEvent->name() == "keydown")
                    onKeyDown(keyboardEvent);
            }
        }

        void WorldMap::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void WorldMap::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }

        void WorldMap::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                {
                    Game::getInstance()->popState();
                }
            }
        }
    }
}
