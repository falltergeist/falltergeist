#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"
#include "../UI/Factory/ImageButtonFactory.h"

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
        class Container final : public State
        {
            public:
                Container(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~Container() = default;

                void init() override;

                Game::ContainerItemObject* object();
                void setObject(Game::ContainerItemObject* object);

                void onDoneButtonClick(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                Game::ContainerItemObject* _object = nullptr;
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
