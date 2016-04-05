/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_STATE_PLAYEREDITGENDER_H
#define FALLTERGEIST_STATE_PLAYEREDITGENDER_H

// C++ standard includes

// Falltergeist includes
#include "../Format/Enums.h"
#include "../State/State.h"

// Third party includes

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
#endif // FALLTERGEIST_STATE_PLAYEREDITGENDER_H
