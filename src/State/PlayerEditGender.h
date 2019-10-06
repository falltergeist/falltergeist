#pragma once

#include "../Format/Enums.h"
#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class ImageList;
    }
    namespace State
    {
        class PlayerEditGender : public State
        {
            public:
                PlayerEditGender();
                ~PlayerEditGender() override;

                void init() override;

                void onFemaleButtonPress(Event::Mouse* event);
                void onMaleButtonPress(Event::Mouse* event);
                void onDoneButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
                void setGender(GENDER gender);

            protected:
                UI::ImageList* _maleImage = nullptr;
                UI::ImageList* _femaleImage = nullptr;
                GENDER _gender = GENDER::MALE;
        };
    }
}
