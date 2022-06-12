#pragma once

// Project includes
#include "../Input/Mouse.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib
#include <memory>
#include <vector>

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
        class CursorDropdown final : public State
        {
            public:
                CursorDropdown(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::vector<Input::Mouse::Icon>&& icons,
                    bool onlyIcon = false
                );

                virtual ~CursorDropdown() = default;

                void init() override;

                void think(const float &deltaTime) override;

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

                Graphics::Point _initialMousePosition;

                int _currentIcon = 0;

                std::vector<std::shared_ptr<UI::Base>> _activeIcons;

                std::vector<std::shared_ptr<UI::Base>> _inactiveIcons;

                std::shared_ptr<UI::Base> _cursor = nullptr;

                Graphics::Point _iconsPos;

                bool _deactivated = false;

                unsigned int _initialMouseStack;

                Event::MouseHandler _mouseDownHandler;
                Event::MouseHandler _mouseUpHandler;
                Event::MouseHandler _mouseMoveHandler;

                void showMenu();

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
