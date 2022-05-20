#pragma once

#include "../Format/Enums.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }

    namespace State
    {
        class Skilldex final : public State
        {
            public:
                Skilldex(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~Skilldex() = default;

                void init() override;


                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;

                void onCancelButtonClick();
                void onSkillButtonClick(SKILL skill);

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
