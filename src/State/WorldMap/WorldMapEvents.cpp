#include "./WorldMap.h"

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
                    int mouseX = mouse->x();
                    int mouseY = mouse->y();
                    // check if point clicked belongs to the screen
                    if ((mapMinX<=(unsigned int)mouseX) && ((unsigned int)mouseX<=(mapMinX+mapWidth)) &&
                        (mapMinY<=(unsigned int)mouseY) && ((unsigned int)mouseY<=(mapMinY+mapHeight)))
                    {
                        destinationX = setDestination('x', (unsigned int)mouseX);
                        destinationY = setDestination('y', (unsigned int)mouseY);
                        isTraveling = true;
                    }
                }
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                if (keyboardEvent->name() == "keydown")
                {
                    onKeyDown(keyboardEvent);
                }
            }
        }

        void WorldMap::processInput()
        {
            SDL_PumpEvents();
            if(keystate[SDL_GetScancodeFromKey(SDLK_LEFT)])
            {
                isTraveling = true;
                directionHorizontal = -1;
            }
            if(keystate[SDL_GetScancodeFromKey(SDLK_RIGHT)])
            {
                isTraveling = true;
                directionHorizontal = 1;
            }
            if(keystate[SDL_GetScancodeFromKey(SDLK_UP)])
            {
                isTraveling = true;
                directionVertical = -1;
            }
            if(keystate[SDL_GetScancodeFromKey(SDLK_DOWN)])
            {
                isTraveling = true;
                directionVertical = 1;
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
                    exit();
                    Game::getInstance()->popState();
                }
            }
        }
    }
}
