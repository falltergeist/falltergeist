/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef FALLTERGEIST_CREDITSSTATE_H
#define FALLTERGEIST_CREDITSSTATE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{

class CreditsState : public State
{
protected:
public:
    CreditsState();
    virtual ~CreditsState();

    virtual void init();
    virtual void think();
    virtual void handle(Event* event);

    void onCreditsFinished();
private:
    std::vector<TextArea*> _lines;
    unsigned long int _lastTicks;
};

}
#endif // FALLTERGEIST_CREDITSSTATE_H
