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

// Third party includes

namespace Falltergeist
{

SettingsMenuState::SettingsMenuState(Game * game) : State(game)
{
}

SettingsMenuState::~SettingsMenuState()
{
}

void SettingsMenuState::init()
{    
    Surface * background = new Surface(ResourceManager::surface("art/intrface/prefscrn.frm", 0, 0));
    background->setXOffset(0);
    background->setYOffset(0);
    
    
    
    
    add(background);    
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

}
