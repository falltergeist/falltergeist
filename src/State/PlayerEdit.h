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
#include <memory>
#include <vector>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
    class BigCounter;
    class HiddenMask;
    class Image;
    class ImageButton;
    class TextArea;
}
namespace State
{

class PlayerEdit : public State
{
protected:
    std::shared_ptr<UI::TextArea> _selectedLabel;
    std::shared_ptr<UI::TextArea> _title;
    std::shared_ptr<UI::TextArea> _description;
    std::shared_ptr<UI::Image> _selectedImage;

    std::map<std::string, std::shared_ptr<UI::TextArea>> _labels;
    std::map<std::string, std::shared_ptr<UI::BigCounter>> _counters;
    std::map<std::string, std::shared_ptr<UI::ImageButton>> _buttons;
    std::map<std::string, std::shared_ptr<UI::HiddenMask>> _masks;
    std::map<std::string, std::string> _titles;
    std::map<std::string, std::string> _descriptions;
    std::map<std::string, std::shared_ptr<UI::Image>> _images;

    UI::TextArea* _addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label);
    UI::ImageButton* _addButton(const std::string& name, std::shared_ptr<UI::ImageButton> button);
    UI::BigCounter* _addCounter(const std::string& name, std::shared_ptr<UI::BigCounter> counter);
    UI::HiddenMask* _addMask(const std::string& name, std::shared_ptr<UI::HiddenMask> mask);
    void _addTitle(const std::string& name, std::string title);
    void _addDescription(const std::string& name, std::string description);
    void _addImage(const std::string& name, std::shared_ptr<UI::Image> image);
    
    bool _statIncrease(unsigned int num);
    bool _statDecrease(unsigned int num);
    bool _traitToggle(unsigned int num);
    bool _skillToggle(unsigned int num);

public:
    PlayerEdit();
    ~PlayerEdit() override;

    void init() override;
    void think() override;

    void onMaskClick(Event::Mouse* event);
    void onButtonClick(Event::Mouse* event);
    void onAgeButtonClick(Event::Mouse* event);
    void onNameButtonClick(Event::Mouse* event);
    void onGenderButtonClick(Event::Mouse* event);
    void onLabelClick(Event::Mouse* event);
    void doCancel();
    void doDone();
    void doPrint();

    void onStateActivate(Event::State* event) override;
    void onStateDeactivate(Event::State* event) override;
    void onKeyDown(Event::Keyboard* event) override;

};

}
}

#endif /* FALLTERGEIST_PlayerEdit_H */

