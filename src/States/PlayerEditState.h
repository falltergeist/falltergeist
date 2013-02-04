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
#include "../UI/HiddenMask.h"
#include <map>
#include <vector>

namespace Falltergeist
{
class Game;
    
class PlayerEditState : public State
{
protected:
    TextArea * _selectedLabel;
    Surface * _selectedImage;
    Surface * _image;
    std::map<std::string, TextArea *> * _labels;
    std::map<std::string, BigCounter *> * _counters;
    std::map<std::string, ImageButton *> * _buttons;
    std::map<std::string, HiddenMask *> * _masks;
    std::map<std::string, std::string> * _titles;
    std::map<std::string, std::string> * _descriptions;
    std::map<std::string, Surface *> * _images;    

    TextArea * _addLabel(std::string name, TextArea * label);
    ImageButton * _addButton(std::string name, ImageButton * button);
    BigCounter * _addCounter(std::string name, BigCounter * counter);
    HiddenMask * _addMask(std::string name, HiddenMask * mask);
    void _addTitle(std::string name, std::string title);
    void _addDescription(std::string name, std::string description);
    void _addImage(std::string name, Surface * image);

public:
    PlayerEditState(Game * game);
    void think();
    virtual ~PlayerEditState();

    void onMaskClick(Event * event);
    void onButtonClick(Event * event);
    void onLabelClick(Event * event);

};

}
#endif	/* FALLTERGEIST_PLAYEREDITSTATE_H */

