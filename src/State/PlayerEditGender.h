#pragma once

// Project includes
#include "../Format/Enums.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

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
                PlayerEditGender(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~PlayerEditGender() = default;

                void init() override;

                void onFemaleButtonPress(Event::Mouse* event);

                void onMaleButtonPress(Event::Mouse* event);

                void onDoneButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

                void setGender(GENDER gender);

            private:
                std::shared_ptr<UI::ImageList> _maleImage = nullptr;

                std::shared_ptr<UI::ImageList> _femaleImage = nullptr;

                GENDER _gender = GENDER::MALE;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
