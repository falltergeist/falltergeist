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

#ifndef FALLTERGEIST_CRITTERDIALOGSTATE_H
#define FALLTERGEIST_CRITTERDIALOGSTATE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class GameCritterObject;
class VM;

class CritterDialogState : public State
{
protected:
    GameCritterObject* _critter = 0;
    VM* _script = 0;
    std::string* _question = 0;
    unsigned int _oldCameraX;
    unsigned int _oldCameraY;
    std::vector<int> _functions;
    std::vector<int> _reactions;
    std::vector<std::string*> _answers;

public:
    CritterDialogState();
    virtual ~CritterDialogState();
    virtual void init();

    GameCritterObject* critter();
    void setCritter(GameCritterObject* critter);

    VM* script();
    void setScript(VM* value);

    std::string* question();
    void setQuestion(std::string* value);

    std::vector<int>* functions();
    std::vector<int>* reactions();
    std::vector<std::string*>* answers();

};

}
#endif // FALLTERGEIST_CRITTERDIALOGSTATE_H
