/*
 * Copyright 2012-2013 Falltergeist Developers.
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
 *
 */

#ifndef FALLTERGEIST_PLAYEREDITAGESTATE_H
#define FALLTERGEIST_PLAYEREDITAGESTATE_H

#include "../Engine/State.h"

namespace Falltergeist
{
class Game;
class BigCounter;

class PlayerEditAgeState : public State
{
protected:
    BigCounter * _counter;
public:
    PlayerEditAgeState(Game * game);
    void init();
    ~PlayerEditAgeState();
    void onIncButtonClick(Event * event);
    void onDecButtonClick(Event * event);
    void onDoneButtonClick(Event * event);
};
}

#endif // FALLTERGEIST_PLAYEREDITAGESTATE_H
