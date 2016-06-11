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

#ifndef FALLTERGEIST_STATE_NEWGAME_H
#define FALLTERGEIST_STATE_NEWGAME_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        class DudeObject;
    }
    namespace State
    {
        class NewGame : public State
        {
            public:
                NewGame();
                ~NewGame() override;

                void init() override;
                void think() override;

                void onBackButtonClick(Event::Mouse* event);
                void onBackFadeDone(Event::State* event);
                void onBeginGameButtonClick(Event::Mouse* event);
                void onEditButtonClick(Event::Mouse* event);
                void onCreateButtonClick(Event::Mouse* event);
                void onPrevCharacterButtonClick(Event::Mouse* event);
                void onNextCharacterButtonClick(Event::Mouse* event);
                void onStateActivate(Event::State* event) override;
                void doBeginGame();
                void doEdit();
                void doCreate();
                void doBack();
                void doNext();
                void doPrev();
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                unsigned char _selectedCharacter = 0;
                std::vector<std::unique_ptr<Game::DudeObject>> _characters;

                void _changeCharacter();
        };
    }
}
#endif // FALLTERGEIST_STATE_NEWGAME_H
