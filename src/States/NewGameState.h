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

#ifndef FALLTERGEIST_NEWGAMESTATE_H
#define FALLTERGEIST_NEWGAMESTATE_H

// C++ standard includes
#include <vector>
#include <memory>

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class GcdFileType;
class Surface;
class ImageList;
class TextArea;
class GameDudeObject;

class NewGameState : public State
{
protected:
    ImageList* _characterImages = 0;
    std::vector<GameDudeObject*> _characters;
    TextArea* _playerStats1 = 0;
    TextArea* _playerStats2 = 0;
    TextArea* _playerStats3 = 0;
    TextArea* _playerBio = 0;
    TextArea* _playerName = 0;
    TextArea* _playerHitPointsMax = 0;
    TextArea* _playerArmorClass = 0;
    TextArea* _playerActionPoints = 0;
    TextArea* _playerMeleeDamage = 0;
    TextArea* _playerSkills = 0;
    TextArea* _playerSkillsValues = 0;
    TextArea* _playerTraits = 0;
    unsigned char _selectedCharacter = 0;
public:
    NewGameState();
    virtual ~NewGameState();
    virtual void init();
    virtual void think();

    void changeCharacter();
    std::string statToString(unsigned int stat);

    void onBackButtonClick(std::shared_ptr<MouseEvent> event);
    void onBeginGameButtonClick(std::shared_ptr<MouseEvent> event);
    void onEditButtonClick(std::shared_ptr<MouseEvent> event);
    void onCreateButtonClick(std::shared_ptr<MouseEvent> event);
    void onPrevCharacterButtonClick(std::shared_ptr<MouseEvent> event);
    void onNextCharacterButtonClick(std::shared_ptr<MouseEvent> event);
};

}
#endif // FALLTERGEIST_NEWGAMESTATE_H
