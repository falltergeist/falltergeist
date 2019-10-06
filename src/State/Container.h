#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
    }
    namespace Game
    {
        class ContainerItemObject;
    }
    namespace State
    {
        class Container : public State
        {
            public:
                Container();
                ~Container() override;

                void init() override;

                Game::ContainerItemObject* object();
                void setObject(Game::ContainerItemObject* object);

                void onDoneButtonClick(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                Game::ContainerItemObject* _object = nullptr;
        };
    }
}
