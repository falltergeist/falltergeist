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

#ifndef FALLTERGEIST_PlayerCreate_H
#define FALLTERGEIST_PlayerCreate_H

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

class PlayerCreate : public State
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

    TextArea* _addLabel(const std::string& name, TextArea* label);
    ImageButton* _addButton(const std::string& name, ImageButton* button);
    BigCounter* _addCounter(const std::string& name, BigCounter* counter);
    HiddenMask* _addMask(const std::string& name, HiddenMask* mask);
    void _addTitle(const std::string& name, std::string title);
    void _addDescription(const std::string& name, std::string description);
    void _addImage(const std::string& name, Image* image);

    bool _statIncrease(unsigned int num);
    bool _statDecrease(unsigned int num);
    bool _traitToggle(unsigned int num);
    bool _skillToggle(unsigned int num);

public:
    PlayerCreate();
    ~PlayerCreate() override;

    void init() override;
    void think() override;

    void onMaskClick(Event::Mouse* event);
    void onButtonClick(Event::Mouse* event);
    void onAgeButtonClick(Event::Mouse* event);
    void onNameButtonClick(Event::Mouse* event);
    void onGenderButtonClick(Event::Mouse* event);
    void onLabelClick(Event::Mouse* event);
    void onBackButtonClick(Event::Mouse* event);
    void onDoneButtonClick(Event::Mouse* event);
    void onOptionsButtonClick(Event::Mouse* event);
    void doAge();
    void doName();
    void doGender();
    void doOptions();
    void doDone();
    void doBack();
    void onKeyDown(Event::Keyboard* event) override;
};

}
}

#endif /* FALLTERGEIST_PlayerCreate_H */
