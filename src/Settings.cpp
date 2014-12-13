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
#include "CrossPlatform.h"
#include "Exception.h"
#include "Logger.h"
#include "Ini/File.h"
#include "Ini/Writer.h"
#include "Settings.h"

// Third party includes

namespace Falltergeist
{
namespace Engine
{

const unsigned int Settings::_defaultScreenWidth = 640;
const unsigned int Settings::_defaultScreenHeight = 480;
const std::string Settings::_defaultInitLocation = "klamall";
const bool Settings::_defaultForceLocation = false;
const std::string Settings::_defaultLoggerLevel = "info";
const bool Settings::_defaultLoggerColors = true;
const bool Settings::_defaultDisplayFps = true;
const bool Settings::_defaultWorldMapFullscreen = false;
const bool Settings::_defaultDisplayMousePosition = true;
const unsigned int  Settings::_defaultScale = 0;
const bool Settings::_defaultFullscreen = false;

const double Settings::_defaultBrightness=1.0;
const unsigned int Settings::_defaultGameDifficulty=1;
const unsigned int Settings::_defaultCombatDifficulty=1;
const bool Settings::_defaultCombatLooks=false;
const bool Settings::_defaultCombatMessages=true;
const bool Settings::_defaultCombatTaunts=false;
const unsigned int Settings::_defaultCombatSpeed=0;
const bool Settings::_defaultItemHighlight=false;
const bool Settings::_defaultLanguageFilter=false;
const double Settings::_defaultMouseSensitivity=1.0;
const bool Settings::_defaultPlayerSpeedup=false;
const bool Settings::_defaultRunning=false;
const bool Settings::_defaultSubtitles=false;
const bool Settings::_defaultTargetHighlight=false;
const double Settings::_defaultTextDelay=0.0;
const unsigned int Settings::_defaultViolenceLevel=2;
// [sound]
const std::string Settings::_defaultMusicPath = "data/sound/music/";
const bool Settings::_defaultAudioEnabled=true;
const double Settings::_defaultMasterVolume=1.0;
const double Settings::_defaultMusicVolume=1.0;
const double Settings::_defaultSFXVolume=1.0;
const double Settings::_defaultVoiceVolume=1.0;

Settings::Settings()
{
    std::string configPath = CrossPlatform::getConfigPath();
    std::string configFile = configPath + "/config.ini";
    std::ifstream stream(configFile);

    Logger::info() << "Read config from " << configFile << std::endl;

    if (stream)
    {
        Engine::Ini::Parser iniParser(stream);
        auto ini = iniParser.parse();

        _readConfig(*ini);
    }
    else
    {
        Logger::warning() << "Cannot open config file at `" << configFile << "`; creating default configuraton file" << std::endl;
        stream.close();

        Ini::File ini;

        _createDefaultConfig(ini);
        _readConfig(ini);

        // Create config path if not exists
        try
        {
            CrossPlatform::createDirectory(configPath);

            // Write default configuration
            Ini::Writer writer(ini);
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

void Settings::_createDefaultConfig(Engine::Ini::File &ini)
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
    game->setPropertyBool("worldmap_fullscreen", _defaultWorldMapFullscreen);
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

Settings::~Settings()
{
}

void Settings::saveConfig()
{
    Ini::File ini;

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
    game->setPropertyBool("worldmap_fullscreen", _worldMapFullscreen);
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
        Ini::Writer writer(ini);
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

const std::string &Settings::defaultInitLocation()
{
    return _defaultInitLocation;
}

const std::string &Settings::initialLocation() const
{
    return _initLocation;
}

bool Settings::forceLocation() const
{
    return _forceLocation;
}

void Settings::_readConfig(Engine::Ini::File &ini)
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
    _worldMapFullscreen = game->propertyBool("worldmap_fullscreen", _defaultWorldMapFullscreen);
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

} // Engine
} // Falltergeist
