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
 *
 */

#ifndef FALLTERGEIST_CRITTERDIALOGSTATE_H
#define FALLTERGEIST_CRITTERDIALOGSTATE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/State.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
class GameCritterObject;
class VM;

class CritterDialogState : public State
{
protected:
    std::shared_ptr<GameCritterObject> _critter;
    VM* _script = 0;
    unsigned int _oldCameraX;
    unsigned int _oldCameraY;
    std::vector<int> _functions;
    std::vector<int> _reactions;
    std::shared_ptr<TextArea> _question;
    std::vector<std::shared_ptr<TextArea>> _answers;


public:
    CritterDialogState();
    virtual ~CritterDialogState();
    virtual void init();

    std::shared_ptr<GameCritterObject> critter();
    void setCritter(std::shared_ptr<GameCritterObject> critter);

    VM* script();
    void setScript(VM* value);

    void setQuestion(std::string value);

    std::vector<int>* functions();
    std::vector<int>* reactions();
    void deleteAnswers();
    bool hasAnswers();
    void addAnswer(std::string text);

    virtual void think();

    void close();

    void onAnswerIn(std::shared_ptr<Event> event);
    void onAnswerOut(std::shared_ptr<Event> event);
    void onAnswerClick(std::shared_ptr<Event> event);
};

}
#endif // FALLTERGEIST_CRITTERDIALOGSTATE_H
