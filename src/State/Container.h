#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }
    namespace State
    {
        class Container final : public State
        {
            public:
                Container(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    Game::ContainerItemObject* object
                );

                virtual ~Container() = default;

                void init() override;

                Game::ContainerItemObject* object() const;

                void onDoneButtonClick(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

                void onKeyDown(Event::Keyboard* event) override;

            private:
                Game::ContainerItemObject* _object = nullptr;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;
        };
    }
}
