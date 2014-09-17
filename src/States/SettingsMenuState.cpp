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
    add(background);

    // Switches (big)
    auto combatDifficultySwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 71));
    combatDifficultySwitch->setMaxState(3);
    add(combatDifficultySwitch);

    auto gameDifficultySwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 149));
    gameDifficultySwitch->setMaxState(3);
    add(gameDifficultySwitch);

    auto violenceLevelSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 227));
    add(violenceLevelSwitch);

    auto targetHighlightSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 309));
    targetHighlightSwitch->setMaxState(3);
    add(targetHighlightSwitch);

    auto combatLooksSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 387));
    combatLooksSwitch->setMaxState(2);
    add(combatLooksSwitch);

    // Switches (small)
    auto combatMessagesSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74));
    add(combatMessagesSwitch);

    auto combatTauntsSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66));
    add(combatTauntsSwitch);

    auto languageFilterSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66*2));
    add(languageFilterSwitch);

    auto runningSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299, 74 + 66*3));
    add(runningSwitch);

    auto subtitlesSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299,74 + 66*4));
    add(subtitlesSwitch);

    auto itemHightlightSwitch = std::shared_ptr<MultistateImageButton>(new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 299,74 + 66*5));
    add(itemHightlightSwitch);

    // LABELS
    auto msg = ResourceManager::msgFileType("text/english/game/options.msg");
    
    auto font1_907824ff = ResourceManager::font("font1.aaf", 0x907824ff);
    auto font3_907824ff = ResourceManager::font("font3.aaf", 0x907824ff);
    auto font4_907824ff = ResourceManager::font("font4.aaf", 0x907824ff);

    // GAME PREFERENCES
    _addTextArea(msg->message(100), 74, 10)->setFont(font4_907824ff);
    
    // COMBAT DIFFICULTY
    auto difficulty = _addTextArea(msg->message(102), 21, 48);
    difficulty->setWidth(158)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER)->setFont(font1_907824ff);

    // GAME DIFFICULTY
    _addTextArea(difficulty, 21, 48 + 77)->setText(msg->message(101));

    // VIOLENCE LEVEL
    _addTextArea(difficulty, 21, 48 + 156)->setText(msg->message(103));
    
    // TARGET HIGHLIGHT
    _addTextArea(difficulty, 21, 128+158)->setText(msg->message(104));
    
    // COMBAT LOOKS
    _addTextArea(difficulty, 21, 128 + 235)->setText(msg->message(105));
    
    // COMBAT MESSAGES
    auto combatMessages = _addTextArea(msg->message(106), 206, 49);
    combatMessages->setFont(font1_907824ff);
    
    // COMBAT TAUNTS
    _addTextArea(combatMessages, 206, 49 + 66)->setText(msg->message(107));
    
    // LANGUAGE FILTER
    _addTextArea(combatMessages, 206, 49 + 66*2)->setText(msg->message(108));
    
    // RUNNING
    _addTextArea(combatMessages, 206, 49 + 66*3)->setText(msg->message(109));

    // SUBTITLES
    _addTextArea(combatMessages, 206, 49 + 66*4)->setText(msg->message(110));

    // ITEM HIGHLIGHT
    _addTextArea(combatMessages, 206, 49 + 66*5)->setText(msg->message(111));

    // COMBAT SPEED
    auto combatSpeed = _addTextArea(msg->message(112), 384, 19);
    combatSpeed->setFont(font1_907824ff);

    // TEXT DELAY
    _addTextArea(combatSpeed, 384, 95)->setText(msg->message(113));

    // MASTER AUDIO VOLUME
    _addTextArea(combatSpeed, 384, 165)->setText(msg->message(114));

    // MUSIC/MOVIE VOLUME
    _addTextArea(combatSpeed, 384, 165 + 51)->setText(msg->message(115));

    // SOUND EFFECTS VOLUME
    _addTextArea(combatSpeed, 384, 165 + 51*2)->setText(msg->message(116));

    // SPEECH VOLUME
    _addTextArea(combatSpeed, 384, 165 + 51*3)->setText(msg->message(117));

    // BRIGHTNESS LEVEL
    _addTextArea(combatSpeed, 384, 165 + 51*4)->setText(msg->message(118));

    // MOUSE SENSITIVITY
    _addTextArea(combatSpeed, 384, 165 + 51*5)->setText(msg->message(119));

    // DEFAULT BUTTON LABEL
    _addTextArea(combatSpeed, 43, 449)->setText(msg->message(120))->setFont(font3_907824ff);

    // DONE BUTTON LABEL
    _addTextArea(combatSpeed, 169, 449)->setText(msg->message(300))->setFont(font3_907824ff);

    // CANCEL BUTTON LABEL
    _addTextArea(combatSpeed, 283, 449)->setText(msg->message(121))->setFont(font3_907824ff);

    // COMBAT DIFFICULTY SWITCH LABELS
    _addTextArea(msg->message(203), 43, 81)->setFont(font1_907824ff);     // EASY
    _addTextArea(msg->message(204), 68, 67)->setFont(font1_907824ff);     // NORMAL
    _addTextArea(msg->message(205), 122, 81)->setFont(font1_907824ff);    // HARD

    // GAME DIFFICULTY SWITCH LABELS
    _addTextArea(msg->message(206), 13, 159)->setFont(font1_907824ff);    // WIMPY
    _addTextArea(msg->message(207), 68, 145)->setFont(font1_907824ff);    // NORMAL
    _addTextArea(msg->message(208), 122, 159)->setFont(font1_907824ff);   // ROUGH

    // VIOLENCE LEVEL SWITCH LABELS
    _addTextArea(msg->message(214), 56, 236)->setFont(font1_907824ff);    // NONE
    _addTextArea(msg->message(215), 65, 222)->setFont(font1_907824ff);    // MINIMUM
    _addTextArea(msg->message(207), 122, 236)->setFont(font1_907824ff);   // NORMAL
    _addTextArea(msg->message(216), 122, 257)->setFont(font1_907824ff)->setWidth(60); // MAXIMUM BLOOD

    // TARGET HIGHLIGHT SWITCH LABELS
    _addTextArea(msg->message(202), 42, 319)->setFont(font1_907824ff);    // OFF
    _addTextArea(msg->message(201), 88, 305)->setFont(font1_907824ff);    // ON
    _addTextArea(msg->message(213), 122, 319)->setFont(font1_907824ff)->setWidth(70)->setWordWrap(true); // TARGETING ONLY

    // COMBAT LOOKS SWITCH LABELS
    _addTextArea(msg->message(202), 42, 397)->setFont(font1_907824ff);    // OFF
    _addTextArea(msg->message(201), 88, 383)->setFont(font1_907824ff);    // ON

    // COMBAT MESSAGES SWITCH LABELS
    auto verboseLabel = _addTextArea(msg->message(211), 203, 69);         // VERBOSE
    verboseLabel->setFont(font1_907824ff)
           ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT)
           ->setWidth(100);
    _addTextArea(msg->message(212), 320, 69)->setFont(font1_907824ff);    // BRIEF

    // COMBAT TAUNTS SWITCH LABELS
    _addTextArea(verboseLabel, 203, 69 + 67)->setText(msg->message(202)); // OFF
    _addTextArea(msg->message(201), 320, 69 + 67)->setFont(font1_907824ff); // ON

    // LANGUAGE FILTER SWITCH LABELS
    _addTextArea(verboseLabel, 203, 69 + 67 + 66)->setText(msg->message(202)); // OFF
    _addTextArea(msg->message(201), 320, 69 + 67 + 66)->setFont(font1_907824ff); // ON

    // RUNNING SWITCH LABELS
    _addTextArea(verboseLabel, 203, 69 + 67 + 66 + 64)->setText(msg->message(209)); // NORMAL
    _addTextArea(msg->message(219), 320, 69 + 67 + 66 + 64)->setFont(font1_907824ff); // ALWAYS

    // SUBTITLES SWITCH LABELS
    _addTextArea(verboseLabel, 203, 69 + 67 + 66 + 66 + 65)->setText(msg->message(202)); // OFF
    _addTextArea(msg->message(201), 320, 69 + 66 + 67 + 66 + 65)->setFont(font1_907824ff); // OFF

    // ITEM HIGHLIGHT SWITCH LABELS
    _addTextArea(verboseLabel, 203, 69 + 67 + 66 + 64 + 65 + 68)->setText(msg->message(202)); // OFF
    _addTextArea(msg->message(201), 320, 69 + 64 + 67 + 66 + 65 + 68)->setFont(font1_907824ff); // ON

    // AFFECT PLAYER SPEECH
    _addTextArea(msg->message(122), 405, 72)->setFont(font1_907824ff);

    // COMBAT SPEED SLIDER LABELS
    _addTextArea(msg->message(209), 384, 38)->setFont(font1_907824ff);      // NORMAL
    auto fastestLabel = _addTextArea(msg->message(210), 524, 38);           // FASTEST
    fastestLabel->setFont(font1_907824ff)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT)
            ->setWidth(100);

    // TEXT DELAY SLIDER LABELS
    _addTextArea(msg->message(217), 384, 113)->setFont(font1_907824ff);     // SLOW
    _addTextArea(msg->message(209), 469, 113)->setFont(font1_907824ff);     // NORMAL
    _addTextArea(fastestLabel, 524, 113)->setText(msg->message(218));       // FASTER

    // MASTER AUDIO VOLUME SLIDER LABELS
    _addTextArea(msg->message(202), 384, 184)->setFont(font1_907824ff);     // OFF
    _addTextArea(msg->message(221), 450, 184)->setFont(font1_907824ff);     // QUIET
    _addTextArea(msg->message(209), 494, 184)->setFont(font1_907824ff);     // NORMAL
    _addTextArea(fastestLabel, 524, 184)->setText(msg->message(222));       // LOUD

    // MUSIC/MOVIE VOLUME SLIDER LABELS
    _addTextArea(msg->message(202), 384, 184+51)->setFont(font1_907824ff);  // OFF
    _addTextArea(msg->message(221), 450, 184+51)->setFont(font1_907824ff);  // QUIET
    _addTextArea(msg->message(209), 494, 184+51)->setFont(font1_907824ff);  // NORMAL
    _addTextArea(fastestLabel, 524, 184+51)->setText(msg->message(222));    // LOUD

    // SOUND EFFECTS SLIDER LABELS
    _addTextArea(msg->message(202), 384, 184+51*2)->setFont(font1_907824ff);// OFF
    _addTextArea(msg->message(221), 450, 184+51*2)->setFont(font1_907824ff);// QUIET
    _addTextArea(msg->message(209), 494, 184+51*2)->setFont(font1_907824ff);// NORMAL
    _addTextArea(fastestLabel, 524, 184+51*2)->setText(msg->message(222));  // LOUD

    // SPEECH VOLUME SLIDER LABELS
    _addTextArea(msg->message(202), 384, 184+51*3)->setFont(font1_907824ff);// OFF
    _addTextArea(msg->message(221), 450, 184+51*3)->setFont(font1_907824ff);// QUIET
    _addTextArea(msg->message(209), 494, 184+51*3)->setFont(font1_907824ff);// NORMAL
    _addTextArea(fastestLabel, 524, 184+51*3)->setText(msg->message(222));  // LOUD

    // BRIGHTNESS LEVEL SLIDER LABELS
    _addTextArea(msg->message(209), 384, 184+51*4)->setFont(font1_907824ff);// NORMAL
    _addTextArea(fastestLabel, 524, 184+51*4)->setText(msg->message(223));  // BRIGHTER

    // MOUSE SENSITIVITY SLIDER LABELS
    _addTextArea(msg->message(209), 384, 184+51*5)->setFont(font1_907824ff);// NORMAL
    _addTextArea(fastestLabel, 524, 184+51*5)->setText(msg->message(218));  // FASTER

    // BUTTONS

    // button: Default
    auto defaultButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 23, 450));
    defaultButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onDefaultButtonClick);
    add(defaultButton);

    // button: Done
    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 148, 450));
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onSaveButtonClick);
    add(doneButton);

    // button: Cancel
    auto cancelButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 263, 450));
    cancelButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SettingsMenuState::onCancelButtonClick);
    add(cancelButton);

    // button: Affect player speed
    auto affectPlayerSpeedCheckBox = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_CHECKBOX, 383, 68));
    add(affectPlayerSpeedCheckBox);

    // SLIDERS
    // COMBAT SPEED SLIDER
    auto combatSpeedSlider = std::shared_ptr<Slider>(new Slider(384, 50));
    add(combatSpeedSlider);

    // TEXT DELAY SLIDER
    auto textDelaySlider = std::shared_ptr<Slider>(new Slider(384, 125));
    textDelaySlider->setValue(0.5);
    add(textDelaySlider);

    // MASTER AUDIO VOLUME SLIDER
    auto masterAudioVolumeSlider = std::shared_ptr<Slider>(new Slider(384, 196));
    add(masterAudioVolumeSlider);

    // MUSIC VOLUME SLIDER
    auto musicVolumeSlider = std::shared_ptr<Slider>(new Slider(384, 196 + 51));
    add(musicVolumeSlider);

    // SOUND EFFECTS VOLUME SLIDER
    auto soundEffectsVolumeSlider = std::shared_ptr<Slider>(new Slider(384, 196 + 51*2));
    add(soundEffectsVolumeSlider);

    // SPEECH VOLUME SLIDER
    auto speechVolumeSlider = std::shared_ptr<Slider>(new Slider(384, 196 + 51*3));
    add(speechVolumeSlider);

    // BRIGHTNESS LEVEL SLIDER
    auto brightnessLevelSlider = std::shared_ptr<Slider>(new Slider(384, 196 + 51*4));
    add(brightnessLevelSlider);

    // MOUSE SENSITIVITY SLIDER
    auto mouseSensitivitySlider = std::shared_ptr<Slider>(new Slider(384, 196 + 51*5));
    add(mouseSensitivitySlider);
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
