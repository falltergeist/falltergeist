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

// C++ standard includes
#include <fstream>
#include <string>
#include <stdexcept>

// Falltergeist includes
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Settings/IniFile.h"
#include "../../Engine/Settings/IniWriter.h"
#include "../../Engine/Settings/Settings.h"

// Third party includes

namespace Falltergeist
{

const unsigned int EngineSettings::_defaultScreenWidth = 640;
const unsigned int EngineSettings::_defaultScreenHeight = 480;
const std::string EngineSettings::_defaultInitLocation = "klamall";
const bool EngineSettings::_defaultForceLocation = false;
const std::string EngineSettings::_defaultLoggerLevel = "info";
const bool EngineSettings::_defaultLoggerColors = true;
const bool EngineSettings::_defaultDisplayFps = true;
const bool EngineSettings::_defaultDisplayMousePosition = true;
const unsigned int  EngineSettings::_defaultScale = 0;
const bool EngineSettings::_defaultFullscreen = false;

const double EngineSettings::_defaultBrightness=1.0;
const unsigned int EngineSettings::_defaultGameDifficulty=1;
const unsigned int EngineSettings::_defaultCombatDifficulty=1;
const bool EngineSettings::_defaultCombatLooks=false;
const bool EngineSettings::_defaultCombatMessages=true;
const bool EngineSettings::_defaultCombatTaunts=false;
const unsigned int EngineSettings::_defaultCombatSpeed=0;
const bool EngineSettings::_defaultItemHighlight=false;
const bool EngineSettings::_defaultLanguageFilter=false;
const double EngineSettings::_defaultMouseSensitivity=1.0;
const bool EngineSettings::_defaultPlayerSpeedup=false;
const bool EngineSettings::_defaultRunning=false;
const bool EngineSettings::_defaultSubtitles=false;
const bool EngineSettings::_defaultTargetHighlight=false;
const double EngineSettings::_defaultTextDelay=0.0;
const unsigned int EngineSettings::_defaultViolenceLevel=2;
// [sound]
const std::string EngineSettings::_defaultMusicPath = "data/sound/music/";
const bool EngineSettings::_defaultAudioEnabled=true;
const double EngineSettings::_defaultMasterVolume=1.0;
const double EngineSettings::_defaultMusicVolume=1.0;
const double EngineSettings::_defaultSFXVolume=1.0;
const double EngineSettings::_defaultVoiceVolume=1.0;

EngineSettings::EngineSettings()
{
    std::string configPath = CrossPlatform::getConfigPath();
    std::string configFile = configPath + "/config.ini";
    std::ifstream stream(configFile);

    Logger::info() << "Read config from " << configFile << std::endl;

    if (stream)
    {
        IniParser iniParser(stream);
        auto ini = iniParser.parse();

        _readConfig(*ini);
    }
    else
    {
        Logger::warning() << "Cannot open config file at `" << configFile << "`; creating default configuraton file" << std::endl;
        stream.close();

        IniFile ini;

        _createDefaultConfig(ini);
        _readConfig(ini);

        // Create config path if not exists
        try
        {
            CrossPlatform::createDirectory(configPath);

            // Write default configuration
            IniWriter writer(ini);
            std::ofstream os(configFile);

            if (os)
            {
                writer.write(os);
            }
            else
            {
                Logger::error("[INI]") << "Cannot write to file `" << configFile << "`" << std::endl;
            }
        }
        catch (const std::runtime_error &e)
        {
            Logger::error("[INI]") << "Cannot create directory `" <<
                    configPath << "` to write config file: " <<
                    e.what() << std::endl;
        }
    }
}

void EngineSettings::_createDefaultConfig(IniFile &ini)
{
    auto video = ini.section("video");
    video->setPropertyInt("width", _defaultScreenWidth);
    video->setPropertyInt("height", _defaultScreenHeight);
    video->setPropertyInt("scale", _defaultScale);
    video->setPropertyBool("fullscreen", _defaultFullscreen);

    auto audio = ini.section("audio");
    audio->setPropertyBool("enabled", _defaultAudioEnabled);
    audio->setPropertyDouble("master_volume", _defaultMasterVolume);
    audio->setPropertyDouble("music_volume", _defaultMusicVolume);
    audio->setPropertyDouble("voice_volume", _defaultVoiceVolume);
    audio->setPropertyDouble("sfx_volume", _defaultSFXVolume);
    audio->setPropertyString("music_path", _defaultMusicPath);

    auto logger = ini.section("logger");
    logger->setPropertyString("level", _defaultLoggerLevel);
    logger->setPropertyBool("colors", _defaultLoggerColors);

    auto game = ini.section("game");
    game->setPropertyString("init_location", _defaultInitLocation);
    game->setPropertyBool("force_location", _defaultForceLocation);
    game->setPropertyBool("display_fps", _defaultDisplayFps);
    game->setPropertyBool("display_mouse_position", _defaultDisplayMousePosition);

    auto preferences = ini.section("preferences");
    preferences->setPropertyDouble("brightness", _defaultBrightness);
    preferences->setPropertyInt("game_difficulty", _defaultGameDifficulty);
    preferences->setPropertyInt("combat_difficulty", _defaultCombatDifficulty);
    preferences->setPropertyBool("combat_looks", _defaultCombatLooks);
    preferences->setPropertyBool("combat_messages", _defaultCombatMessages);
    preferences->setPropertyBool("combat_taunts", _defaultCombatTaunts);
    preferences->setPropertyInt("combat_speed", _defaultCombatSpeed);
    preferences->setPropertyBool("item_highlight", _defaultItemHighlight);
    preferences->setPropertyBool("language_filter", _defaultLanguageFilter);
    preferences->setPropertyDouble("mouse_sensitivity", _defaultMouseSensitivity);
    preferences->setPropertyBool("player_speedup", _defaultPlayerSpeedup);
    preferences->setPropertyBool("running", _defaultRunning);
    preferences->setPropertyBool("subtitles", _defaultSubtitles);
    preferences->setPropertyBool("target_highlight", _defaultTargetHighlight);
    preferences->setPropertyDouble("text_delay", _defaultTextDelay);
    preferences->setPropertyInt("violence_level", _defaultViolenceLevel);
}

EngineSettings::~EngineSettings()
{
}

void EngineSettings::saveConfig()
{
    IniFile ini;

    auto video = ini.section("video");
    video->setPropertyInt("width", _screenWidth);
    video->setPropertyInt("height", _screenHeight);
    video->setPropertyInt("scale", _scale);
    video->setPropertyBool("fullscreen", _fullscreen);

    auto audio = ini.section("audio");
    audio->setPropertyBool("enabled", _audioEnabled);
    audio->setPropertyDouble("master_volume", _masterVolume);
    audio->setPropertyDouble("music_volume", _musicVolume);
    audio->setPropertyDouble("voice_volume", _voiceVolume);
    audio->setPropertyDouble("sfx_volume", _sfxVolume);
    audio->setPropertyString("music_path", _musicPath);

    auto logger = ini.section("logger");
    logger->setPropertyString("level", _loggerLevel);
    logger->setPropertyBool("colors", _loggerColors);

    auto game = ini.section("game");
    game->setPropertyString("init_location", _initLocation);
    game->setPropertyBool("force_location", _forceLocation);
    game->setPropertyBool("display_fps", _displayFps);
    game->setPropertyBool("display_mouse_position", _displayMousePosition);

    auto preferences = ini.section("preferences");
    preferences->setPropertyDouble("brightness", _brightness);
    preferences->setPropertyInt("game_difficulty", _gameDifficulty);
    preferences->setPropertyInt("combat_difficulty", _combatDifficulty);
    preferences->setPropertyBool("combat_looks", _combatLooks);
    preferences->setPropertyBool("combat_messages", _combatMessages);
    preferences->setPropertyBool("combat_taunts", _combatTaunts);
    preferences->setPropertyInt("combat_speed", _combatSpeed);
    preferences->setPropertyBool("item_highlight", _itemHighlight);
    preferences->setPropertyBool("language_filter", _languageFilter);
    preferences->setPropertyDouble("mouse_sensitivity", _mouseSensitivity);
    preferences->setPropertyBool("player_speedup", _playerSpeedup);
    preferences->setPropertyBool("running", _running);
    preferences->setPropertyBool("subtitles", _subtitles);
    preferences->setPropertyBool("target_highlight", _targetHighlight);
    preferences->setPropertyDouble("text_delay", _textDelay);
    preferences->setPropertyInt("violence_level", _violenceLevel);

    // Create config path if not exists
    std::string configPath = CrossPlatform::getConfigPath();
    std::string configFile = configPath + "/config.ini";
    try
    {
        CrossPlatform::createDirectory(configPath);

        // Write default configuration
        IniWriter writer(ini);
        std::ofstream os(configFile);

        if (os)
        {
            writer.write(os);
        }
        else
        {
            Logger::error("[INI]") << "Cannot write to file `" << configFile << "`" << std::endl;
        }
    }
    catch (const std::runtime_error &e)
    {
        Logger::error("[INI]") << "Cannot create directory `" <<
                configPath << "` to write config file: " <<
                e.what() << std::endl;
    }
}

unsigned int EngineSettings::screenWidth() const
{
    return _screenWidth;
}

unsigned int EngineSettings::screenHeight() const
{
    return _screenHeight;
}

bool EngineSettings::audioEnabled() const
{
    return _audioEnabled;
}

const std::string &EngineSettings::defaultInitLocation()
{
    return _defaultInitLocation;
}

const std::string &EngineSettings::initialLocation() const
{
    return _initLocation;
}

bool EngineSettings::forceLocation() const
{
    return _forceLocation;
}

void EngineSettings::_readConfig(IniFile &ini)
{
    auto video = ini.section("video");
    _screenWidth = video->propertyInt("width", _defaultScreenWidth);
    _screenHeight = video->propertyInt("height", _defaultScreenHeight);
    _scale = video->propertyInt("scale", _defaultScale);
    if (_scale > 2) _scale = 2;
    _fullscreen = video->propertyBool("fullscreen", _defaultFullscreen);

    auto audio = ini.section("audio");
    _audioEnabled = audio->propertyBool("enabled", _defaultAudioEnabled);
    _masterVolume = audio->propertyDouble("master_volume", _defaultMasterVolume);
    _musicVolume = audio->propertyDouble("music_volume", _defaultMusicVolume);
    _voiceVolume = audio->propertyDouble("voice_volume", _defaultVoiceVolume);
    _sfxVolume = audio->propertyDouble("sfx_volume", _defaultSFXVolume);
    _musicPath = audio->propertyString("music_path", _defaultMusicPath);

    auto logger = ini.section("logger");
    _loggerLevel = logger->propertyString("level", _defaultLoggerLevel);
    Logger::setLevel(_loggerLevel);
    _loggerColors = logger->propertyBool("colors", _defaultLoggerColors);
    Logger::useColors(_loggerColors);

    auto game = ini.section("game");
    _initLocation = game->propertyString("init_location", _defaultInitLocation);
    _forceLocation = game->propertyBool("force_location", _defaultForceLocation);


    _displayFps = game->propertyBool("display_fps", _defaultDisplayFps);
    _displayMousePosition = game->propertyBool("display_mouse_position", _defaultDisplayMousePosition);

    auto preferences = ini.section("preferences");
    _brightness = preferences->propertyDouble("brightness", _defaultBrightness);
    _gameDifficulty = preferences->propertyInt("game_difficulty", _defaultGameDifficulty);
    _combatDifficulty = preferences->propertyInt("combat_difficulty", _defaultCombatDifficulty);
    _combatLooks = preferences->propertyBool("combat_looks", _defaultCombatLooks);
    _combatMessages = preferences->propertyBool("combat_messages", _defaultCombatMessages);
    _combatTaunts = preferences->propertyBool("combat_taunts", _defaultCombatTaunts);
    _combatSpeed = preferences->propertyInt("combat_speed", _defaultCombatSpeed);
    _itemHighlight = preferences->propertyBool("item_highlight", _defaultItemHighlight);
    _languageFilter = preferences->propertyBool("language_filter", _defaultLanguageFilter);
    _mouseSensitivity = preferences->propertyDouble("mouse_sensitivity", _defaultMouseSensitivity);
    _playerSpeedup = preferences->propertyBool("player_speedup", _defaultPlayerSpeedup);
    _running = preferences->propertyBool("running", _defaultRunning);
    _subtitles = preferences->propertyBool("subtitles", _defaultSubtitles);
    _targetHighlight = preferences->propertyBool("target_highlight", _defaultTargetHighlight);
    _textDelay = preferences->propertyDouble("text_delay", _defaultTextDelay);
    _violenceLevel = preferences->propertyInt("violence_level", _defaultViolenceLevel);
}

bool EngineSettings::displayFps() const
{
    return _displayFps;
}

bool EngineSettings::displayMousePosition() const
{
    return _displayMousePosition;
}

void EngineSettings::setVoiceVolume(double _voiceVolume)
{
    this->_voiceVolume = _voiceVolume;
}

double EngineSettings::voiceVolume() const
{
    return _voiceVolume;
}

void EngineSettings::setSfxVolume(double _sfxVolume)
{
    this->_sfxVolume = _sfxVolume;
}

double EngineSettings::sfxVolume() const
{
    return _sfxVolume;
}

void EngineSettings::setMusicVolume(double _musicVolume)
{
    this->_musicVolume = _musicVolume;
}

double EngineSettings::musicVolume() const
{
    return _musicVolume;
}

void EngineSettings::setMasterVolume(double _masterVolume)
{
    this->_masterVolume = _masterVolume;
}

double EngineSettings::masterVolume() const
{
    return _masterVolume;
}

std::string EngineSettings::musicPath() const
{
    return _musicPath;
}

void EngineSettings::setViolenceLevel(unsigned int _violenceLevel)
{
    this->_violenceLevel = _violenceLevel;
}

unsigned int EngineSettings::violenceLevel() const
{
    return _violenceLevel;
}

void EngineSettings::setTextDelay(double _textDelay)
{
    this->_textDelay = _textDelay;
}

double EngineSettings::textDelay() const
{
    return _textDelay;
}

void EngineSettings::setTargetHighlight(bool _targetHighlight)
{
    this->_targetHighlight = _targetHighlight;
}

bool EngineSettings::targetHighlight() const
{
    return _targetHighlight;
}

void EngineSettings::setSubtitles(bool _subtitles)
{
    this->_subtitles = _subtitles;
}

bool EngineSettings::subtitles() const
{
    return _subtitles;
}

void EngineSettings::setRunning(bool _running)
{
    this->_running = _running;
}

bool EngineSettings::running() const
{
    return _running;
}

void EngineSettings::setPlayerSpeedup(bool _playerSpeedup)
{
    this->_playerSpeedup = _playerSpeedup;
}

bool EngineSettings::playerSpeedup() const
{
    return _playerSpeedup;
}

void EngineSettings::setMouseSensitivity(double _mouseSensitivity)
{
    this->_mouseSensitivity = _mouseSensitivity;
}

double EngineSettings::mouseSensitivity() const
{
    return _mouseSensitivity;
}

void EngineSettings::setLanguageFilter(bool _languageFilter)
{
    this->_languageFilter = _languageFilter;
}

bool EngineSettings::languageFilter() const
{
    return _languageFilter;
}

void EngineSettings::setItemHighlight(bool _itemHighlight)
{
    this->_itemHighlight = _itemHighlight;
}

bool EngineSettings::itemHighlight() const
{
    return _itemHighlight;
}

void EngineSettings::setCombatSpeed(unsigned int _combatSpeed)
{
    this->_combatSpeed = _combatSpeed;
}

unsigned int EngineSettings::combatSpeed() const
{
    return _combatSpeed;
}

void EngineSettings::setCombatTaunts(bool _combatTaunts)
{
    this->_combatTaunts = _combatTaunts;
}

bool EngineSettings::combatTaunts() const
{
    return _combatTaunts;
}

void EngineSettings::setCombatMessages(bool _combatMessages)
{
    this->_combatMessages = _combatMessages;
}

bool EngineSettings::combatMessages() const
{
    return _combatMessages;
}

void EngineSettings::setCombatLooks(bool _combatLooks)
{
    this->_combatLooks = _combatLooks;
}

bool EngineSettings::combatLooks() const
{
    return _combatLooks;
}

void EngineSettings::setCombatDifficulty(unsigned int _combatDifficulty)
{
    this->_combatDifficulty = _combatDifficulty;
}

unsigned int EngineSettings::combatDifficulty() const
{
    return _combatDifficulty;
}

void EngineSettings::setGameDifficulty(unsigned int _gameDifficulty)
{
    this->_gameDifficulty = _gameDifficulty;
}

unsigned int EngineSettings::gameDifficulty() const
{
    return _gameDifficulty;
}

void EngineSettings::setBrightness(double _brightness)
{
    this->_brightness = _brightness;
}

double EngineSettings::brightness() const
{
    return _brightness;
}

void EngineSettings::setScale(unsigned int _scale)
{
    this->_scale = _scale;
}

unsigned int EngineSettings::scale() const
{
    return _scale;
}

void EngineSettings::setFullscreen(bool _fullscreen)
{
    this->_fullscreen = _fullscreen;
}

bool EngineSettings::fullscreen() const
{
    return _fullscreen;
}

}
