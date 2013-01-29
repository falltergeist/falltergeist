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
 */

#ifndef FALLTERGEIST_PLAYEREDITSTATE_H
#define	FALLTERGEIST_PLAYEREDITSTATE_H

#include "../Engine/State.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/BigCounter.h"
#include <map>
#include <vector>

namespace Falltergeist
{
class Game;
    
class PlayerEditState : public State
{
protected:

    std::vector<TextArea *> * _checkedLabels;
    std::map<std::string, TextArea *> * _labels;
    std::map<std::string, BigCounter *> * _counters;
    std::map<std::string, ImageButton *> * _buttons;

    TextArea * _addLabel(std::string name, TextArea * label);
    ImageButton * _addButton(std::string name, ImageButton * button);
    BigCounter * _addCounter(std::string name, BigCounter * counter);

public:
    PlayerEditState(Game * game);
    void think();
    virtual ~PlayerEditState();
    void onIncreaseStrengthButtonClick();
    void onDecreaseStrengthButtonClick();
    void onIncreasePerceptionButtonClick();
    void onDecreasePerceptionButtonClick();
    void onIncreaseEnduranceButtonClick();
    void onDecreaseEnduranceButtonClick();
    void onIncreaseCharismaButtonClick();
    void onDecreaseCharismaButtonClick();
    void onIncreaseIntelligenceButtonClick();
    void onDecreaseIntelligenceButtonClick();
    void onIncreaseAgilityButtonClick();
    void onDecreaseAgilityButtonClick();
    void onIncreaseLuckButtonClick();
    void onDecreaseLuckButtonClick();

    void onStrengthSelected();
    void onPerceptionSelected();
    void onEnduranceSelected();
    void onCharismaSelected();
    void onIntelligenceSelected();
    void onAgilitySelected();
    void onLuckSelected();

};

}
#endif	/* FALLTERGEIST_PLAYEREDITSTATE_H */

