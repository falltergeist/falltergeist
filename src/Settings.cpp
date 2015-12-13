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

// C++ standard includes
#include <fstream>
#include <string>
#include <stdexcept>

// Falltergeist includes
#include "Platform/Platform.h"
#include "Exception.h"
#include "Logger.h"
#include "Lua/Script.h"
#include "Ini/File.h"
#include "Ini/Writer.h"
#include "Settings.h"

// Third party includes

namespace Falltergeist
{

Settings::Settings()
{
    if (!load())
    {
        save();
    }
}

Settings::~Settings()
{
}

bool Settings::save()
{
    CrossPlatform::createDirectory(CrossPlatform::getConfigPath());
    std::string configFile = CrossPlatform::getConfigPath() + "/config.lua";
    std::ofstream stream(configFile);

    Logger::info() << "Saving config to " << configFile << std::endl;

    if (!stream)
    {
        Logger::warning() << "Cannot open config file at `" << configFile << "`;" << std::endl;
        return false;
    }

    stream << "-- video" << std::endl
           << "width = "  << _screenWidth << std::endl
           << "height = " << _screenHeight << std::endl
           << "scale = "  << _scale << std::endl
           << "fullscreen = " << (_fullscreen ? "true" : "false") << std::endl
           << "-- audio"  << std::endl
           << "audio_enabled = " << (_audioEnabled ? "true" : "false") << std::endl
           << "master_volume = " << std::to_string(_masterVolume) << std::endl
           << "music_volume = " <<  std::to_string(_musicVolume) << std::endl
           << "voice_volume = " <<  std::to_string(_voiceVolume) << std::endl
           << "sfx_volume = " <<    std::to_string(_sfxVolume)  << std::endl
           << "music_path = \"" << _musicPath << "\"" << std::endl
           << "audio_buffer_size = " << _audioBufferSize << std::endl
           << "-- logger" << std::endl
           << "logger_level = \"" << _loggerLevel << "\"" << std::endl
           << "logger_colors = " << (_loggerColors ? "true" : "false") << std::endl
           << "-- game" << std::endl
           << "init_location = \"" << _initLocation << "\"" << std::endl
           << "force_location = " << (_forceLocation ? "true" : "false") << std::endl
           << "display_fps = " << (_displayFps ? "true" : "false") << std::endl
           << "worldmap_fullscreen = " << (_worldMapFullscreen ? "true" : "false") << std::endl
           << "display_mouse_position = " << (_displayMousePosition ? "true" : "false") << std::endl
           << "-- preferences" << std::endl
           << "brightness = "  << std::to_string(_brightness) << std::endl
           << "game_difficulty = " << _gameDifficulty << std::endl
           << "combat_difficulty = " << _combatDifficulty << std::endl
           << "combat_looks = " << (_combatLooks ? "true" : "false") << std::endl
           << "combat_messages = " << (_combatMessages ? "true" : "false") << std::endl
           << "combat_taunts = " << (_combatTaunts ? "true" : "false") << std::endl
           << "combat_speed = " << _combatSpeed << std::endl
           << "item_highlight = " << (_itemHighlight ? "true" : "false") << std::endl
           << "language_filter = " << (_languageFilter ? "true" : "false") << std::endl
           << "mouse_sensitivity = " << std::to_string(_mouseSensitivity) << std::endl
           << "player_speedup = " << (_playerSpeedup ? "true" : "false") << std::endl
           << "running = " << (_running ? "true" : "false") << std::endl
           << "subtitles = " << (_subtitles ? "true" : "false") << std::endl
           << "target_highlight = " << (_targetHighlight ? "true" : "false") << std::endl
           << "text_delay = " << std::to_string(_textDelay) << std::endl
           << "violence_level = " << _violenceLevel << std::endl;

    return true;
}

unsigned int Settings::screenWidth() const
{
    return _screenWidth;
}

unsigned int Settings::screenHeight() const
{
    return _screenHeight;
}

bool Settings::audioEnabled() const
{
    return _audioEnabled;
}

const std::string& Settings::initialLocation() const
{
    return _initLocation;
}

bool Settings::forceLocation() const
{
    return _forceLocation;
}

bool Settings::load()
{
    std::string configFile = CrossPlatform::getConfigPath() + "/config.lua";
    std::ifstream stream(configFile);

    Logger::info() << "Loading config from " << configFile << std::endl;

    if (!stream)
    {
        Logger::warning() << "Cannot open config file at `" << configFile << "`;" << std::endl;
        return false;
    }

    Lua::Script script(configFile);
    script.run();

    _screenWidth  = script.get("width",  (int)_screenWidth);
    _screenHeight = script.get("height", (int)_screenHeight);
    _scale        = script.get("scale",  (int)_scale);
    if (_scale > 2) _scale = 2;
    _fullscreen   = script.get("fullscreen", (bool)_fullscreen);

    _audioEnabled    = script.get("audio_enabled", (bool)_audioEnabled);
    _masterVolume    = script.get("master_volume", (double)_masterVolume);
    _musicVolume     = script.get("music_volume",  (double)_musicVolume);
    _voiceVolume     = script.get("voice_volume",  (double)_voiceVolume);
    _sfxVolume       = script.get("sfx_volume",    (double)_sfxVolume);
    _musicPath       = script.get("music_path",    (const std::string&)_musicPath);
    _audioBufferSize = script.get("audio_buffer_size",   (int)_audioBufferSize);

    _loggerLevel  = script.get("logger_level", (const std::string&)_loggerLevel);
    Logger::setLevel(_loggerLevel);
    _loggerColors = script.get("logger_colors", (bool)_loggerColors);
    Logger::useColors(_loggerColors);

    _initLocation  = script.get("init_location",  (const std::string&)_initLocation);
    _forceLocation = script.get("force_location", (bool)_forceLocation);

    _displayFps           = script.get("display_fps",            (bool)_displayFps);
    _worldMapFullscreen   = script.get("worldmap_fullscreen",    (bool)_worldMapFullscreen);
    _displayMousePosition = script.get("display_mouse_position", (bool)_displayMousePosition);

    _brightness       = script.get("brightness",        (double)_brightness);
    _gameDifficulty   = script.get("game_difficulty",   (int)_gameDifficulty);
    _combatDifficulty = script.get("combat_difficulty", (int)_combatDifficulty);
    _combatLooks      = script.get("combat_looks",      (bool)_combatLooks);
    _combatMessages   = script.get("combat_messages",   (bool)_combatMessages);
    _combatTaunts     = script.get("combat_taunts",     (bool)_combatTaunts);
    _combatSpeed      = script.get("combat_speed",      (int)_combatSpeed);
    _itemHighlight    = script.get("item_highlight",    (bool)_itemHighlight);
    _languageFilter   = script.get("language_filter",   (bool)_languageFilter);
    _mouseSensitivity = script.get("mouse_sensitivity", (double)_mouseSensitivity);
    _playerSpeedup    = script.get("player_speedup",    (bool)_playerSpeedup);
    _running          = script.get("running",           (bool)_running);
    _subtitles        = script.get("subtitles",         (bool)_subtitles);
    _targetHighlight  = script.get("target_highlight",  (bool)_targetHighlight);
    _textDelay        = script.get("text_delay",        (double)_textDelay);
    _violenceLevel    = script.get("violence_level",    (int)_violenceLevel);

    return true;
}

bool Settings::displayFps() const
{
    return _displayFps;
}

bool Settings::worldMapFullscreen() const
{
    return _worldMapFullscreen;
}

bool Settings::displayMousePosition() const
{
    return _displayMousePosition;
}

void Settings::setVoiceVolume(double _voiceVolume)
{
    this->_voiceVolume = _voiceVolume;
}

double Settings::voiceVolume() const
{
    return _voiceVolume;
}

void Settings::setSfxVolume(double _sfxVolume)
{
    this->_sfxVolume = _sfxVolume;
}

double Settings::sfxVolume() const
{
    return _sfxVolume;
}

void Settings::setMusicVolume(double _musicVolume)
{
    this->_musicVolume = _musicVolume;
}

double Settings::musicVolume() const
{
    return _musicVolume;
}

void Settings::setMasterVolume(double _masterVolume)
{
    this->_masterVolume = _masterVolume;
}

double Settings::masterVolume() const
{
    return _masterVolume;
}

std::string Settings::musicPath() const
{
    return _musicPath;
}

void Settings::setViolenceLevel(unsigned int _violenceLevel)
{
    this->_violenceLevel = _violenceLevel;
}

unsigned int Settings::violenceLevel() const
{
    return _violenceLevel;
}

void Settings::setTextDelay(double _textDelay)
{
    this->_textDelay = _textDelay;
}

double Settings::textDelay() const
{
    return _textDelay;
}

void Settings::setTargetHighlight(bool _targetHighlight)
{
    this->_targetHighlight = _targetHighlight;
}

bool Settings::targetHighlight() const
{
    return _targetHighlight;
}

void Settings::setSubtitles(bool _subtitles)
{
    this->_subtitles = _subtitles;
}

bool Settings::subtitles() const
{
    return _subtitles;
}

void Settings::setRunning(bool _running)
{
    this->_running = _running;
}

bool Settings::running() const
{
    return _running;
}

void Settings::setPlayerSpeedup(bool _playerSpeedup)
{
    this->_playerSpeedup = _playerSpeedup;
}

bool Settings::playerSpeedup() const
{
    return _playerSpeedup;
}

void Settings::setMouseSensitivity(double _mouseSensitivity)
{
    this->_mouseSensitivity = _mouseSensitivity;
}

double Settings::mouseSensitivity() const
{
    return _mouseSensitivity;
}

void Settings::setLanguageFilter(bool _languageFilter)
{
    this->_languageFilter = _languageFilter;
}

bool Settings::languageFilter() const
{
    return _languageFilter;
}

void Settings::setItemHighlight(bool _itemHighlight)
{
    this->_itemHighlight = _itemHighlight;
}

bool Settings::itemHighlight() const
{
    return _itemHighlight;
}

void Settings::setCombatSpeed(unsigned int _combatSpeed)
{
    this->_combatSpeed = _combatSpeed;
}

unsigned int Settings::combatSpeed() const
{
    return _combatSpeed;
}

void Settings::setCombatTaunts(bool _combatTaunts)
{
    this->_combatTaunts = _combatTaunts;
}

bool Settings::combatTaunts() const
{
    return _combatTaunts;
}

void Settings::setCombatMessages(bool _combatMessages)
{
    this->_combatMessages = _combatMessages;
}

bool Settings::combatMessages() const
{
    return _combatMessages;
}

void Settings::setCombatLooks(bool _combatLooks)
{
    this->_combatLooks = _combatLooks;
}

bool Settings::combatLooks() const
{
    return _combatLooks;
}

void Settings::setCombatDifficulty(unsigned int _combatDifficulty)
{
    this->_combatDifficulty = _combatDifficulty;
}

unsigned int Settings::combatDifficulty() const
{
    return _combatDifficulty;
}

void Settings::setGameDifficulty(unsigned int _gameDifficulty)
{
    this->_gameDifficulty = _gameDifficulty;
}

unsigned int Settings::gameDifficulty() const
{
    return _gameDifficulty;
}

void Settings::setBrightness(double _brightness)
{
    this->_brightness = _brightness;
}

double Settings::brightness() const
{
    return _brightness;
}

void Settings::setScale(unsigned int _scale)
{
    this->_scale = _scale;
}

unsigned int Settings::scale() const
{
    return _scale;
}

void Settings::setFullscreen(bool _fullscreen)
{
    this->_fullscreen = _fullscreen;
}

bool Settings::fullscreen() const
{
    return _fullscreen;
}

void Settings::setAudioBufferSize(int _audioBufferSize)
{
    this->_audioBufferSize = _audioBufferSize;
}

int Settings::audioBufferSize() const
{
    return _audioBufferSize;
}

}
