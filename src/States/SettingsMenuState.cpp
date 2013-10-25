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
#include "../UI/MultistateImageButton.h"
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
    
    
    //_fon = new InteractiveSurface(); 
    //_fon->loadFromBmpFile(CrossPlatform::findDataPath() + "/scr00000.bmp");
    //_fon->onKeyboardRelease((EventHandler) &SettingsMenuState::onButtonPress);
    //add(_fon);
    
    auto background = new Surface(ResourceManager::surface("art/intrface/prefscrn.frm", 0, 0));
    background->setXOffset(0);
    background->setYOffset(0);
    
    auto bigSwitchesSurface = ResourceManager::surface("art/intrface/prfbknbs.frm");
    auto bigSwitchSet = new SurfaceSet();
    bigSwitchSet->addSurface(bigSwitchesSurface->crop(0, 47*0, 46, 47));
    bigSwitchSet->addSurface(bigSwitchesSurface->crop(0, 47*1, 46, 47));
    bigSwitchSet->addSurface(bigSwitchesSurface->crop(0, 47*2, 46, 47));
    bigSwitchSet->addSurface(bigSwitchesSurface->crop(0, 47*3, 46, 47));

    auto switch1 = new MultistateImageButton(bigSwitchSet, 100, 100);
    // prfbknbs.frm - 4 больших переключателя - расположены вертикально // 46x188
    // prflknbs.frm - 2 маленьких переключателя - расположены вертикально
    
    
    // labels    
    auto msg = ResourceManager::msgFileType("text/english/game/options.msg");
    _addLabel("title_1", new TextArea(msg->message(100), 74, 10))->setFont("font4.aaf")->setColor(0xffb89c28);    
    _addLabel("title_2", new TextArea(msg->message(101), 21, 48))
            ->setFont("font3.aaf")
            ->setColor(0xffb89c28)
            ->setWidth(158)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);    
    _addLabel("title_21", new TextArea(msg->message(102), 21, 48 + 77))
            ->setFont("font3.aaf")
            ->setColor(0xffb89c28)
            ->setWidth(158)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);    
    _addLabel("title_22", new TextArea(msg->message(103), 21, 48 + 156))
            ->setFont("font3.aaf")
            ->setColor(0xffb89c28)
            ->setWidth(158)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);                
    _addLabel("title_23", new TextArea(msg->message(104), 21, 48 + 158+80))
            ->setFont("font3.aaf")
            ->setColor(0xffb89c28)
            ->setWidth(158)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);                
    _addLabel("title_24", new TextArea(msg->message(105), 21, 48 + 235+80))
            ->setFont("font3.aaf")
            ->setColor(0xffb89c28)
            ->setWidth(158)
            ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);                  
    
    _addLabel("title_3", new TextArea(msg->message(106), 206, 49))->setFont("font3.aaf")->setColor(0xffb89c28);        
    _addLabel("title_31", new TextArea(msg->message(107), 206, 49 + 66))->setFont("font3.aaf")->setColor(0xffb89c28);        
    _addLabel("title_32", new TextArea(msg->message(108), 206, 49 + 66*2))->setFont("font3.aaf")->setColor(0xffb89c28);        
    _addLabel("title_33", new TextArea(msg->message(109), 206, 49 + 66*3))->setFont("font3.aaf")->setColor(0xffb89c28);        
    _addLabel("title_34", new TextArea(msg->message(110), 206, 49 + 66*4))->setFont("font3.aaf")->setColor(0xffb89c28);        
    _addLabel("title_35", new TextArea(msg->message(111), 206, 49 + 66*5))->setFont("font3.aaf")->setColor(0xffb89c28);        
    
    _addLabel("title_4", new TextArea(msg->message(112), 384, 19))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_5", new TextArea(msg->message(113), 384, 94))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_6", new TextArea(msg->message(114), 384, 165))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_7", new TextArea(msg->message(115), 384, 165 + 51))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_8", new TextArea(msg->message(116), 384, 165 + 51*2))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_9", new TextArea(msg->message(117), 384, 165 + 51*3))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_10", new TextArea(msg->message(118), 384, 165 + 51*4))->setFont("font3.aaf")->setColor(0xffb89c28);
    _addLabel("title_11", new TextArea(msg->message(119), 384, 165 + 51*5))->setFont("font3.aaf")->setColor(0xffb89c28);
    
    /*
     
{100}{}{НАСТРОЙКИ}
{101}{}{СЛОЖНОСТЬ ИГРЫ}
{102}{}{СЛОЖНОСТЬ БОЯ}
{103}{}{УРОВЕНЬ НАСИЛИЯ}
{104}{}{ВЫДЕЛЕНИЕ ЦЕЛИ}
{105}{}{ИНФО В БОЮ}
{106}{}{СООБЩ. В БОЮ}
{107}{}{НАСМЕШКИ В БОЮ}
{108}{}{ФИЛЬТР РУГАНИ}
{109}{}{БЕГ}
{110}{}{СУБТИТРЫ}
{111}{}{ВЫДЕЛ. ПРЕДМ.}
{112}{}{СКОРОСТЬ БОЯ}
{113}{}{ЗАДЕРЖКА ТЕКСТА}
{114}{}{ОБЩ. ГРОМКОСТЬ}
{115}{}{ГРОМКОСТЬ МУЗЫКИ/ВИДЕО}
{116}{}{ГРОМКОСТЬ ЭФФЕКТОВ}
{117}{}{ГРОМКОСТЬ РЕЧИ}
{118}{}{УРОВЕНЬ ЯРКОСТИ}
{119}{}{ЧУВСТВИТЕЛЬНОСТЬ МЫШИ}
{120}{}{СТАНД.}
{121}{}{ОТМЕНА}
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
    
    add(background);    
    //add(switch1);
    
    for (auto& label : _labels) add(label.second);
    
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

}
