#pragma once

#include <memory>
#include <vector>
#include "../Input/Mouse.h"
#include "../State/State.h"

namespace Falltergeist
{
    namespace Event
    {
        class Event;
        class Mouse;
    }
    namespace Game
    {
        class Object;
    }
    namespace State
    {
        class CursorDropdown : public State
        {
            public:
                CursorDropdown(std::vector<Input::Mouse::Icon>&& icons, bool onlyIcon = false);
                ~CursorDropdown() override;

                void init() override;
                void think() override;
                void handle(Event::Event* event) override;
                void render() override;

                void onLeftButtonUp(Event::Mouse* event);

                Game::Object* object();
                void setObject(Game::Object* object);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;

            protected:
                Game::Object* _object = nullptr;
                bool _onlyShowIcon;
                std::vector<Input::Mouse::Icon> _icons;
                int _initialX;
                int _initialY;
                int _currentIcon = 0;
                std::vector<std::unique_ptr<UI::Base>> _activeIcons;
                std::vector<std::unique_ptr<UI::Base>> _inactiveIcons;
                UI::Base* _cursor = nullptr;
                Point _iconsPos;
                bool _deactivated = false;
                unsigned int _initialMouseStack;

                Event::MouseHandler _mouseDownHandler, _mouseUpHandler, _mouseMoveHandler;

                void showMenu();
        };
    }
}
