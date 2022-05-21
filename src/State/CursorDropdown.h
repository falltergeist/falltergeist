#pragma once

#include <memory>
#include <vector>
#include "../Input/Mouse.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
                    std::shared_ptr<Input::Mouse> mouse,
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
                void _showMenu();

                Game::Object* _object = nullptr;

                bool _onlyShowIcon;

                std::vector<Input::Mouse::Icon> _icons;

                Graphics::Point _initialMousePosition;

                int _currentIcon = 0;

                std::vector<std::unique_ptr<UI::Base>> _activeIcons;

                std::vector<std::unique_ptr<UI::Base>> _inactiveIcons;

                UI::Base* _cursor = nullptr;

                Graphics::Point _iconsPos;

                bool _deactivated = false;

                unsigned int _initialMouseStack;

                Event::MouseHandler _mouseDownHandler, _mouseUpHandler, _mouseMoveHandler;

                std::shared_ptr<UI::IResourceManager> _resourceManager;
        };
    }
}
