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

// C++ standard includes
#include <iostream>

// Falltergeist includes
#include "../States/SettingsMenuState.h"
#include "../Engine/ResourceManager.h"
#include "../UI/Image.h"
#include "../Engine/Game.h"
#include "../UI/MultistateImageButton.h"
#include "../UI/ImageButton.h"
#include "../UI/Slider.h"
#include "../UI/TextArea.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

SettingsMenuState::SettingsMenuState() : State()
{
}

SettingsMenuState::~SettingsMenuState()
{
}

void SettingsMenuState::init()
{
    if (_initialized) return;
    State::init();

    auto background = std::shared_ptr<Image>(new Image("art/intrface/prefscrn.frm"));

    auto switch1 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 71));
    switch1->setMaxState(3);    
    auto switch2 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 149));
    switch2->setMaxState(3);
    auto switch3 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 227));
    auto switch4 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 309));
    switch4->setMaxState(3);
    auto switch5 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 387));
    switch5->setMaxState(2);

    auto switch6 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74));
    auto switch7 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66));
    auto switch8 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66*2));
    auto switch9 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66*3));
    auto switch10 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299,74 + 66*4));
    auto switch11 = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299,74 + 66*5));

    // LABELS
    auto msg = ResourceManager::msgFileType("text/english/game/options.msg");
    
    auto font1_907824ff = ResourceManager::font("font1.aaf", 0x907824ff);
    auto font3_907824ff = ResourceManager::font("font3.aaf", 0x907824ff);
    auto font4_907824ff = ResourceManager::font("font4.aaf", 0x907824ff);

    //GAME PREFERENCES
    _addTextArea(msg->message(100), 74, 10)->setFont(font4_907824ff);
    
    //COMBAT DIFFICULTY
    auto difficulty = _addTextArea(msg->message(102), 21, 48);
    difficulty->setWidth(158)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER)->setFont(font1_907824ff);

    //GAME DIFFICULTY
    _addTextArea(difficulty, 21, 48 + 77)->setText(msg->message(101));

    //VIOLENCE LEVEL
    _addTextArea(difficulty, 21, 48 + 156)->setText(msg->message(103));
    
    //TARGET HIGHLIGHT
    auto title5 = std::shared_ptr<TextArea>(new TextArea(difficulty, 21, 128+ 158));
    title5->setText(msg->message(104));
    
    //COMBAT LOOKS
    auto title6 = std::shared_ptr<TextArea>(new TextArea(difficulty, 21, 128 + 235));
    title6->setText(msg->message(105));
    
    //COMBAT MESSAGES
    auto title7 = std::shared_ptr<TextArea>(new TextArea(msg->message(106), 206, 49));
    title7->setFont(font1_907824ff);
    
    //COMBAT TAUNTS
    auto title8 = std::shared_ptr<TextArea>(new TextArea(title7, 206, 49 + 66));
    title8->setText(msg->message(107));
    
    //LANGUAGE FILTER
    auto title9 = std::shared_ptr<TextArea>(new TextArea(title7, 206, 49 + 66*2));
    title9->setText(msg->message(108));
    
    //RUNNING
    auto title10 = std::shared_ptr<TextArea>(new TextArea(title7, 206, 49 + 66*3));
    title10->setText(msg->message(109));
    
    auto title11 = std::shared_ptr<TextArea>(new TextArea(title7, 206, 49 + 66*4));
    title11->setText(msg->message(110));
    
    auto title12 = std::shared_ptr<TextArea>(new TextArea(title7, 206, 49 + 66*5));
    title12->setText(msg->message(111));
    
    auto title13 = std::shared_ptr<TextArea>(new TextArea(msg->message(112), 384, 19));
    title13->setFont(font1_907824ff);

    auto title14 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 94));
    title14->setText(msg->message(113));
    
    auto title15 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165));
    title15->setText(msg->message(114));
    
    auto title16 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165 + 51));
    title16->setText(msg->message(115));
    
    auto title17 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165 + 51*2));
    title17->setText(msg->message(116));
    
    auto title18 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165 + 51*3));
    title18->setText(msg->message(117));
    
    auto title19 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165 + 51*4));
    title19->setText(msg->message(118));
    
    auto title20 = std::shared_ptr<TextArea>(new TextArea(title13, 384, 165 + 51*5));
    title20->setText(msg->message(119));

    auto title21 = std::shared_ptr<TextArea>(new TextArea(title13, 43, 449));
    title21->setText(msg->message(120))->setFont(font3_907824ff);

    auto title22 = std::shared_ptr<TextArea>(new TextArea(title13, 169, 449));
    title22->setText(msg->message(300))->setFont(font3_907824ff);

    auto title23 = std::shared_ptr<TextArea>(new TextArea(title13, 283, 449));
    title23->setText(msg->message(121))->setFont(font3_907824ff);

    auto label1 = std::shared_ptr<TextArea>(new TextArea(msg->message(203), 43, 81)); label1->setFont(font1_907824ff);
    auto label2 = std::shared_ptr<TextArea>(new TextArea(msg->message(204), 68, 67)); label2->setFont(font1_907824ff);
    auto label3 = std::shared_ptr<TextArea>(new TextArea(msg->message(205), 122, 81)); label3->setFont(font1_907824ff);

    auto label4 = std::shared_ptr<TextArea>(new TextArea(msg->message(206), 13, 159)); label4->setFont(font1_907824ff);
    auto label5 = std::shared_ptr<TextArea>(new TextArea(msg->message(207), 68, 145)); label5->setFont(font1_907824ff);
    auto label6 = std::shared_ptr<TextArea>(new TextArea(msg->message(208), 122, 159)); label6->setFont(font1_907824ff);

    auto label7 = std::shared_ptr<TextArea>(new TextArea(msg->message(214), 56, 236)); label7->setFont(font1_907824ff);
    auto label8 = std::shared_ptr<TextArea>(new TextArea(msg->message(215), 65, 222)); label8->setFont(font1_907824ff);
    auto label9 = std::shared_ptr<TextArea>(new TextArea(msg->message(207), 122, 236)); label9->setFont(font1_907824ff);
    auto label10 = std::shared_ptr<TextArea>(new TextArea(msg->message(216), 122, 257)); label10->setFont(font1_907824ff)->setWidth(60);

    auto label11 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 42, 319)); label11->setFont(font1_907824ff);
    auto label12 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 88, 305)); label12->setFont(font1_907824ff);
    auto label13 = std::shared_ptr<TextArea>(new TextArea(msg->message(213), 122, 319)); label13->setFont(font1_907824ff)->setWidth(70)->setWordWrap(true);

    auto label14 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 42, 397)); label14->setFont(font1_907824ff);
    auto label15 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 88, 383)); label15->setFont(font1_907824ff);

    auto label16 = std::shared_ptr<TextArea>(new TextArea(msg->message(211), 203, 69)); label16->setFont(font1_907824ff);
         label16->setFont(font1_907824ff)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT)
                 ->setWidth(100);
    auto label17 = std::shared_ptr<TextArea>(new TextArea(msg->message(212), 320, 69)); label17->setFont(font1_907824ff);

    auto label18 = std::shared_ptr<TextArea>(new TextArea(label16, 203, 69 + 67));
    label18->setText(msg->message(202));
    auto label19 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 320, 69 + 67)); label19->setFont(font1_907824ff);

    auto label20 = std::shared_ptr<TextArea>(new TextArea(label16, 203, 69 + 67 + 66));
    label20->setText(msg->message(202));
    auto label21 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 320, 69 + 67 + 66)); label21->setFont(font1_907824ff);

    auto label22 = std::shared_ptr<TextArea>(new TextArea(label16, 203, 69 + 67 + 66 + 64));
    label22->setText(msg->message(209));
    auto label23 = std::shared_ptr<TextArea>(new TextArea(msg->message(219), 320, 69 + 67 + 66 + 64)); label23->setFont(font1_907824ff);

    auto label24 = std::shared_ptr<TextArea>(new TextArea(label16, 203, 69 + 67 + 66 + 66 + 65));
    label24->setText(msg->message(202));
    auto label25 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 320, 69 + 66 + 67 + 66 + 65)); label25->setFont(font1_907824ff);

    auto label26 = std::shared_ptr<TextArea>(new TextArea(label16, 203, 69 + 67 + 66 + 64 + 65 + 68));
    label26->setText(msg->message(202));
    auto label27 = std::shared_ptr<TextArea>(new TextArea(msg->message(201), 320, 69 + 64 + 67 + 66 + 65 + 68)); label27->setFont(font1_907824ff);

    auto label28 = std::shared_ptr<TextArea>(new TextArea(msg->message(122), 405, 72)); label28->setFont(font1_907824ff);

    auto label29 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 384, 38)); label29->setFont(font1_907824ff);
    auto label30 = std::shared_ptr<TextArea>(new TextArea(msg->message(210), 524, 38));
         label30->setFont(font1_907824ff)
                ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT)
                ->setWidth(100);

    auto label31 = std::shared_ptr<TextArea>(new TextArea(msg->message(217), 384, 113)); label31->setFont(font1_907824ff);
    auto label32 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 469, 113)); label32->setFont(font1_907824ff);
    auto label33 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 113)); label33->setText(msg->message(218));

    auto label34 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 384, 184)); label34->setFont(font1_907824ff);
    auto label35 = std::shared_ptr<TextArea>(new TextArea(msg->message(221), 450, 184)); label35->setFont(font1_907824ff);
    auto label36 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 494, 184)); label36->setFont(font1_907824ff);
    auto label37 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184)); label37->setText(msg->message(222));

    auto label38 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 384, 184+51)); label38->setFont(font1_907824ff);
    auto label39 = std::shared_ptr<TextArea>(new TextArea(msg->message(221), 450, 184+51)); label39->setFont(font1_907824ff);
    auto label40 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 494, 184+51)); label40->setFont(font1_907824ff);
    auto label41 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184+51)); label41->setText(msg->message(222));

    auto label42 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 384, 184+51*2)); label42->setFont(font1_907824ff);
    auto label43 = std::shared_ptr<TextArea>(new TextArea(msg->message(221), 450, 184+51*2)); label43->setFont(font1_907824ff);
    auto label44 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 494, 184+51*2)); label44->setFont(font1_907824ff);
    auto label45 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184+51*2)); label45->setText(msg->message(222));

    auto label46 = std::shared_ptr<TextArea>(new TextArea(msg->message(202), 384, 184+51*3)); label46->setFont(font1_907824ff);
    auto label47 = std::shared_ptr<TextArea>(new TextArea(msg->message(221), 450, 184+51*3)); label47->setFont(font1_907824ff);
    auto label48 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 494, 184+51*3)); label48->setFont(font1_907824ff);
    auto label49 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184+51*3)); label49->setText(msg->message(222));

    auto label50 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 384, 184+51*4)); label50->setFont(font1_907824ff);
    auto label51 = std::shared_ptr<TextArea>(new TextArea(msg->message(209), 384, 184+51*5)); label51->setFont(font1_907824ff);
    auto label52 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184+51*4)); label52->setText(msg->message(223));
    auto label53 = std::shared_ptr<TextArea>(new TextArea(label30, 524, 184+51*5)); label53->setText(msg->message(218));

    // BUTTONS

    // button: Default
    auto button1 = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 23, 450));
    button1->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onDefaultButtonClick);

    // button: Done
    auto button2 = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 148, 450));
    button2->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onSaveButtonClick);

    // button: Cancel
    auto button3 = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 263, 450));
    button3->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onCancelButtonClick);

    // button: Affect player speed
    auto button4 = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_CHECKBOX, 383, 68));

    // SLIDERS
    auto slider1 = std::shared_ptr<Slider>(new Slider(384, 50));
    auto slider2 = std::shared_ptr<Slider>(new Slider(384, 125));
    slider2->setValue(0.5);
    auto slider3 = std::shared_ptr<Slider>(new Slider(384, 196));
    auto slider4 = std::shared_ptr<Slider>(new Slider(384, 196 + 51));
    auto slider5 = std::shared_ptr<Slider>(new Slider(384, 196 + 51*2));
    auto slider6 = std::shared_ptr<Slider>(new Slider(384, 196 + 51*3));
    auto slider7 = std::shared_ptr<Slider>(new Slider(384, 196 + 51*4));
    auto slider8 = std::shared_ptr<Slider>(new Slider(384, 196 + 51*5));


    add(background);

    add({ title5, title6,
          title7, title8, title9, title10, title11, title12, title13,
          title14, title15, title16, title17, title18, title19, title20,
          title21, title22, title23,
          button1, button2, button3, button4,
          label1, label2, label3, label4, label5, label6, label7, label8,
          label9, label10, label11, label12, label13, label14, label15,
          label16, label17, label18, label19, label20, label21, label22, label23,
          label24, label25, label26, label27, label28, label29, label30, label31,
          label32, label33, label34, label35, label36, label37, label38, label39,
          label40, label41, label42, label43, label44, label45, label46, label47,
          label48, label49, label50, label51, label52, label53
    });

    add({switch1, switch2, switch3, switch4, switch5,
         switch6, switch7, switch8, switch9, switch10, switch11
    });

    add({slider1, slider2, slider3, slider4, slider5, slider6, slider7, slider8});

}

void SettingsMenuState::think()
{
    State::think();
}

IniFileSection SettingsMenuState::_getSettings()
{
    // @todo Load options from FALLTERGEIST_DATA/config.ini if exists

    // or return default values
    return _getDefaultSettings();
}

IniFileSection SettingsMenuState::_getDefaultSettings()
{
    return IniFileSection({
        {       "brightness", "1.000000"}, // max 1.179993
        {"combat_difficulty", "1"},
        {     "combat_looks", "0"},
        {  "combat_messages", "1"},
        {     "combat_speed", "0"},
        {    "combat_taunts", "1"},
        {  "game_difficulty", "1"},
        {   "item_highlight", "1"},
        {  "language_filter", "0"},
        {"mouse_sensitivity", "1.000000"},  // max 2.500000
        {   "player_speedup", "0"},
        {          "running", "0"},
        {        "subtitles", "0"},
        { "target_highlight", "2"},
        {  "text_base_delay", "3.500000"},  // max 1.000000
        {  "text_line_delay", "1.000000"},  // max 0.000000
        {   "violence_level", "3"}
    });
}

std::shared_ptr<TextArea> SettingsMenuState::_addLabel(std::string name, std::shared_ptr<TextArea> label)
{
    _labels.insert(std::make_pair(name, label));
    return label;
}

std::shared_ptr<TextArea> SettingsMenuState::_addTextArea(std::shared_ptr<libfalltergeist::MsgMessage> message, unsigned int x, unsigned int y)
{
    auto textArea = std::shared_ptr<TextArea>(new TextArea(message, x, y));
    add(textArea);
    return textArea;
}

std::shared_ptr<TextArea> SettingsMenuState::_addTextArea(std::shared_ptr<TextArea> parent, unsigned int x, unsigned int y)
{
    auto textArea = std::shared_ptr<TextArea>(new TextArea(parent, x, y));
    add(textArea);
    return textArea;
}

void SettingsMenuState::onCancelButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

void SettingsMenuState::onSaveButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

void SettingsMenuState::onDefaultButtonClick(std::shared_ptr<MouseEvent> event)
{
}

}
