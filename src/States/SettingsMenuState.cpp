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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../States/SettingsMenuState.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Game.h"
#include "../UI/MultistateImageButton.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

SettingsMenuState::SettingsMenuState(Game* game) : State(game)
{
}

SettingsMenuState::~SettingsMenuState()
{
}

void SettingsMenuState::init()
{    
    State::init();
    
    
    _fon = new InteractiveSurface();
    _fon->loadFromBmpFile(CrossPlatform::findDataPath() + "/scr00000.bmp");
    _fon->onKeyboardRelease((EventHandler) &SettingsMenuState::onButtonPress);
    add(_fon);
    
    auto background = new Surface(ResourceManager::surface("art/intrface/prefscrn.frm", 0, 0));
    background->setXOffset(0);
    background->setYOffset(0);
    
    auto switch1 = new MultistateImageButton(MultistateImageButton::TYPE_BIG_SWITCH, 76, 71);
    auto switch2 = new MultistateImageButton(MultistateImageButton::TYPE_SMALL_SWITCH, 176, 71);

    // LABELS
    auto msg = ResourceManager::msgFileType("text/english/game/options.msg");
    
    auto title1 = new TextArea(msg->message(100), 74, 10);
    title1->setFont("font4.aaf")->setColor(0xffb89c28);
    
    auto title2 = new TextArea(msg->message(101), 21, 48);
    title2->setColor(0xffb89c28)->setWidth(158)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER)->setFont("font3.aaf");

    auto title3 = new TextArea(title2, 21, 48 + 77);
    title2->setText(msg->message(102));

    auto title4 = new TextArea(title2, 21, 48 + 156);
    title4->setText(msg->message(103));
    
    auto title5 = new TextArea(title2, 21, 128+ 158);
    title5->setText(msg->message(104));
    
    auto title6 = new TextArea(title2, 21, 128 + 235);
    title6->setText(msg->message(105));
    
    auto title7 = new TextArea(msg->message(106), 206, 49);
    title7->setFont("font3.aaf")->setColor(0xffb89c28);
    
    auto title8 = new TextArea(title7, 206, 49 + 66);
    title8->setText(msg->message(107));
    
    auto title9 = new TextArea(title7, 206, 49 + 66*2);
    title9->setText(msg->message(108));
    
    auto title10 = new TextArea(title7, 206, 49 + 66*3);
    title10->setText(msg->message(109));
    
    auto title11 = new TextArea(title7, 206, 49 + 66*4);
    title11->setText(msg->message(110));
    
    auto title12 = new TextArea(title7, 206, 49 + 66*5);
    title12->setText(msg->message(111));
    
    auto title13 = new TextArea(msg->message(112), 384, 19);
    title13->setFont("font3.aaf")->setColor(0xffb89c28);

    auto title14 = new TextArea(title13, 384, 94);
    title14->setText(msg->message(113));
    
    auto title15 = new TextArea(title13, 384, 165);
    title15->setText(msg->message(114));
    
    auto title16 = new TextArea(title13, 384, 165 + 51);
    title16->setText(msg->message(115));
    
    auto title17 = new TextArea(title13, 384, 165 + 51*2);
    title17->setText(msg->message(116));
    
    auto title18 = new TextArea(title13, 384, 165 + 51*3);
    title18->setText(msg->message(117));
    
    auto title19 = new TextArea(title13, 384, 165 + 51*4);
    title19->setText(msg->message(118));
    
    auto title20 = new TextArea(title13, 384, 165 + 51*5);
    title20->setText(msg->message(119));

    auto title21 = new TextArea(title13, 43, 449);
    title21->setText(msg->message(120));

    auto title22 = new TextArea(title13, 169, 449);
    title22->setText(msg->message(300));

    auto title23 = new TextArea(title13, 283, 449);
    title23->setText(msg->message(121));

    auto label1 = new TextArea(msg->message(203), 43, 81);
    label1->setColor(0xffb89c28);

    // BUTTONS

    auto button1 = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 23, 450);
    button1->onLeftButtonClick((EventHandler) &SettingsMenuState::onDefaultButtonClick);

    auto button2 = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 148, 450);
    button2->onLeftButtonClick((EventHandler) &SettingsMenuState::onSaveButtonClick);

    auto button3 = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 263, 450);
    button3->onLeftButtonClick((EventHandler) &SettingsMenuState::onCancelButtonClick);



    /*
{122}{}{Влияние на скорость игрока}
{123}{}{Речь Pipboy}
#
# Label text
#
{201}{}{Вкл.}
{202}{}{Выкл.}
{203}{}{Легко}
{204}{}{Нормально}
{205}{}{Сложно}
{206}{}{По-детски}
{207}{}{Нормально}
{208}{}{Круто}
{209}{}{Нормально}
{210}{}{Очень быстро}
{211}{}{Развернуто}
{212}{}{Кратко}
{213}{}{Только наведение}
{214}{}{Нет}
{215}{}{Минимально}
{216}{}{Максимум крови}
{217}{}{Медленно}
{218}{}{Быстрее}
{219}{}{Всегда}
{220}{}{Много}
{221}{}{Тихо}
{222}{}{Громко}
{223}{}{Ярче}
{224}{}{Широко}

     
     */
    add({ title1, title2, title3, title4, title5, title6,
         title7, title8, title9, title10, title11, title12, title13,
         title14, title15, title16, title17, title18, title19, title20,
         title21, title22, title23, button1, button2, button3, label1 });
    add(switch1);
    add(switch2);

    //for (auto& label : _labels) add(label.second);
    
}

void SettingsMenuState::think()
{    
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

TextArea* SettingsMenuState::_addLabel(std::string name, TextArea* label)
{
    _labels.insert(std::make_pair(name, label));
    return label;
}

void SettingsMenuState::onButtonPress(Event* event)
{
    event->sender()->setVisible(!event->sender()->visible());
}

void SettingsMenuState::onCancelButtonClick(Event* event)
{
    _game->popState();
}

void SettingsMenuState::onSaveButtonClick(Event* event)
{
    _game->popState();
}

void SettingsMenuState::onDefaultButtonClick(Event* event)
{
}

}
