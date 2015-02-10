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

#ifndef FALLTERGEIST_PlayerEdit_H
#define	FALLTERGEIST_PlayerEdit_H

// C++ standard includes
#include <map>
#include <vector>

// Falltergeist includes
#include "State.h"
#include "../UI/BigCounter.h"
#include "../UI/HiddenMask.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class PlayerEdit : public State
{
protected:
    TextArea* _selectedLabel = 0;
    TextArea* _title = 0;
    TextArea* _description = 0;
    Image* _selectedImage = 0;
    std::map<std::string, TextArea*> _labels;
    std::map<std::string, BigCounter*> _counters;
    std::map<std::string, ImageButton*> _buttons;
    std::map<std::string, HiddenMask*> _masks;
    std::map<std::string, std::string> _titles;
    std::map<std::string, std::string> _descriptions;
    std::map<std::string, Image*> _images;

    TextArea* _addLabel(std::string name, TextArea* label);
    ImageButton* _addButton(std::string name, ImageButton* button);
    BigCounter* _addCounter(std::string name, BigCounter* counter);
    HiddenMask* _addMask(std::string name, HiddenMask* mask);
    void _addTitle(std::string name, std::string title);
    void _addDescription(std::string name, std::string description);
    void _addImage(std::string name, Image* image);
    
    bool _statIncrease(unsigned int num);
    bool _statDecrease(unsigned int num);
    bool _traitToggle(unsigned int num);
    bool _skillToggle(unsigned int num);

public:
    PlayerEdit();
    void init();
    void think();
    virtual ~PlayerEdit();

    void onMaskClick(MouseEvent* event);
    void onButtonClick(MouseEvent* event);
    void onAgeButtonClick(MouseEvent* event);
    void onNameButtonClick(MouseEvent* event);
    void onGenderButtonClick(MouseEvent* event);
    void onLabelClick(MouseEvent* event);
    void onBackButtonClick(MouseEvent* event);
    void onDoneButtonClick(MouseEvent* event);
    virtual void onStateActivate(StateEvent* event);
    virtual void onStateDeactivate(StateEvent* event);

};

}
}

#endif /* FALLTERGEIST_PlayerEdit_H */

