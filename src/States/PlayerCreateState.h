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

#ifndef FALLTERGEIST_PLAYERCREATESTATE_H
#define FALLTERGEIST_PLAYERCREATESTATE_H

// C++ standard includes
#include <map>
#include <vector>

// Falltergeist includes
#include "../Engine/State.h"
#include "../UI/BigCounter.h"
#include "../UI/HiddenMask.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

class PlayerCreateState : public State
{
protected:
    std::shared_ptr<TextArea> _selectedLabel;
    std::shared_ptr<TextArea> _title;
    std::shared_ptr<TextArea> _description;
    std::shared_ptr<Image> _selectedImage;
    std::map<std::string, std::shared_ptr<TextArea>> _labels;
    std::map<std::string, std::shared_ptr<BigCounter>> _counters;
    std::map<std::string, std::shared_ptr<ImageButton>> _buttons;
    std::map<std::string, std::shared_ptr<HiddenMask>> _masks;
    std::map<std::string, std::string> _titles;
    std::map<std::string, std::string> _descriptions;
    std::map<std::string, std::shared_ptr<Image>> _images;

    std::shared_ptr<TextArea> _addLabel(std::string name, std::shared_ptr<TextArea> label);
    std::shared_ptr<ImageButton> _addButton(std::string name, std::shared_ptr<ImageButton> button);
    std::shared_ptr<BigCounter> _addCounter(std::string name, std::shared_ptr<BigCounter> counter);
    std::shared_ptr<HiddenMask> _addMask(std::string name, std::shared_ptr<HiddenMask> mask);
    void _addTitle(std::string name, std::string title);
    void _addDescription(std::string name, std::string description);
    void _addImage(std::string name, std::shared_ptr<Image> image);

    bool _statIncrease(unsigned int num);
    bool _statDecrease(unsigned int num);
    bool _traitToggle(unsigned int num);
    bool _skillToggle(unsigned int num);

public:
    PlayerCreateState();
    void init();
    void think();
    virtual ~PlayerCreateState();

    void onMaskClick(std::shared_ptr<MouseEvent> event);
    void onButtonClick(std::shared_ptr<MouseEvent> event);
    void onAgeButtonClick(std::shared_ptr<MouseEvent> event);
    void onNameButtonClick(std::shared_ptr<MouseEvent> event);
    void onGenderButtonClick(std::shared_ptr<MouseEvent> event);
    void onLabelClick(std::shared_ptr<MouseEvent> event);
    void onBackButtonClick(std::shared_ptr<MouseEvent> event);
    void onDoneButtonClick(std::shared_ptr<MouseEvent> event);
};

}
#endif /* FALLTERGEIST_PLAYERCREATESTATE_H */
