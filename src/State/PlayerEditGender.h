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
        class ImageList;
    }
    namespace State
    {
        class PlayerEditGender final : public State
        {
            public:
                PlayerEditGender(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

                virtual ~PlayerEditGender() = default;

                void init() override;

                void onFemaleButtonPress(Event::Mouse* event);

                void onMaleButtonPress(Event::Mouse* event);

                void onDoneButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

                void setGender(GENDER gender);

            private:
                UI::ImageList* _maleImage = nullptr;

                UI::ImageList* _femaleImage = nullptr;

                GENDER _gender = GENDER::MALE;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
