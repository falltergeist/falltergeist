/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_PlayerEditAlert_H
#define FALLTERGEIST_PlayerEditAlert_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class PlayerEditAlert : public State
{
protected:
    std::string _message;
public:
    PlayerEditAlert();
    ~PlayerEditAlert() override;

    void setMessage(const std::string& message);

    void init() override;

    void onDoneButtonClick(Event::Mouse* event);
};

}
}

#endif // FALLTERGEIST_PlayerEditAlert_H
