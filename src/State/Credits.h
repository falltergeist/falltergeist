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

#ifndef FALLTERGEIST_STATE_CREDITS_H
#define FALLTERGEIST_STATE_CREDITS_H

// C++ standard includes

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace UI
    {
        class TextArea;
    }
    namespace State
    {
        class Credits : public State
        {
            public:
                Credits();
                ~Credits() override;

                void init() override;
                void think() override;
                void handle(Event::Event* event) override;

                void onCreditsFinished();
                void onCreditsFadeDone(Event::State* event);
                void onStateActivate(Event::State* event) override;
            private:
                std::vector<UI::TextArea*> _lines;
                unsigned long int _lastTicks;
        };
    }
}
#endif // FALLTERGEIST_STATE_CREDITS_H
