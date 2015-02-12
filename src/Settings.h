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

#ifndef FALLTERGEIST_SETTINGS_H
#define FALLTERGEIST_SETTINGS_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third patry includes

namespace Falltergeist
{
namespace Ini
{
    class File;
} // Ini


class Settings
{
public:

    Settings();
    ~Settings();

    void saveConfig();

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const std::string &initialLocation() const;

    static const std::string &defaultInitLocation();

    bool forceLocation() const;

    bool displayFps() const;

    bool worldMapFullscreen() const;

    bool displayMousePosition() const;

    bool audioEnabled() const;
    void setVoiceVolume(double _voiceVolume);
    double voiceVolume() const;
    void setSfxVolume(double _sfxVolume);
    double sfxVolume() const;
    void setMusicVolume(double _musicVolume);
    double musicVolume() const;
    void setMasterVolume(double _masterVolume);
    double masterVolume() const;
    std::string musicPath() const;
    void setViolenceLevel(unsigned int _violenceLevel);
    unsigned int violenceLevel() const;
    void setTextDelay(double _textDelay);
    double textDelay() const;
    void setTargetHighlight(bool _targetHighlight);
    bool targetHighlight() const;
    void setSubtitles(bool _subtitles);
    bool subtitles() const;
    void setRunning(bool _running);
    bool running() const;
    void setPlayerSpeedup(bool _playerSpeedup);
    bool playerSpeedup() const;
    void setMouseSensitivity(double _mouseSensitivity);
    double mouseSensitivity() const;
    void setLanguageFilter(bool _languageFilter);
    bool languageFilter() const;
    void setItemHighlight(bool _itemHighlight);
    bool itemHighlight() const;
    void setCombatSpeed(unsigned int _combatSpeed);
    unsigned int combatSpeed() const;
    void setCombatTaunts(bool _combatTaunts);
    bool combatTaunts() const;
    void setCombatMessages(bool _combatMessages);
    bool combatMessages() const;
    void setCombatLooks(bool _combatLooks);
    bool combatLooks() const;
    void setCombatDifficulty(unsigned int _combatDifficulty);
    unsigned int combatDifficulty() const;
    void setGameDifficulty(unsigned int _gameDifficulty);
    unsigned int gameDifficulty() const;
    void setBrightness(double _brightness);
    double brightness() const;
    void setScale(unsigned int _scale);
    unsigned int scale() const;
    void setFullscreen(bool _fullscreen);
    bool fullscreen() const;
    void setAudioBufferSize(int _audioBufferSize);
    int audioBufferSize() const;

private:
    unsigned int _screenWidth;
    unsigned int _screenHeight;
    std::string _initLocation;
    bool _forceLocation;
    bool _displayFps;
    bool _worldMapFullscreen;
    bool _displayMousePosition;
    std::string _loggerLevel;
    bool _loggerColors;
    unsigned int _scale;
    bool _fullscreen;

    double _brightness;
    unsigned int _gameDifficulty;
    unsigned int _combatDifficulty;
    bool _combatLooks;
    bool _combatMessages;
    bool _combatTaunts;
    unsigned int _combatSpeed;
    bool _itemHighlight;
    bool _languageFilter;
    double _mouseSensitivity;
    bool _playerSpeedup;
    bool _running;
    bool _subtitles;
    bool _targetHighlight;
    double _textDelay;
    unsigned int _violenceLevel;
    // [sound]
    std::string _musicPath;
    bool _audioEnabled;
    double _masterVolume;
    double _musicVolume;
    double _sfxVolume;
    double _voiceVolume;
    int _audioBufferSize;

    void _createDefaultConfig(Ini::File &ini);
    void _readConfig(Ini::File &ini);

    // DEFAULTS
    static const unsigned int _defaultScreenWidth;
    static const unsigned int _defaultScreenHeight;
    static const std::string _defaultInitLocation;
    static const bool _defaultForceLocation;
    static const std::string _defaultLoggerLevel;
    static const bool _defaultLoggerColors;
    static const bool _defaultDisplayFps;
    static const bool _defaultWorldMapFullscreen;
    static const bool _defaultDisplayMousePosition;
    static const unsigned int _defaultScale;
    static const bool _defaultFullscreen;

    // [preferences]
    static const double _defaultBrightness;
    static const unsigned int _defaultGameDifficulty;
    static const unsigned int _defaultCombatDifficulty;
    static const bool _defaultCombatLooks;
    static const bool _defaultCombatMessages;
    static const bool _defaultCombatTaunts;
    static const unsigned int _defaultCombatSpeed;
    static const bool _defaultItemHighlight;
    static const bool _defaultLanguageFilter;
    static const double _defaultMouseSensitivity;
    static const bool _defaultPlayerSpeedup;
    static const bool _defaultRunning;
    static const bool _defaultSubtitles;
    static const bool _defaultTargetHighlight;
    static const double _defaultTextDelay;
    static const unsigned int _defaultViolenceLevel;
    // [sound]
    static const std::string _defaultMusicPath;
    static const bool _defaultAudioEnabled;
    static const double _defaultMasterVolume;
    static const double _defaultMusicVolume;
    static const double _defaultSFXVolume;
    static const double _defaultVoiceVolume;
    static const int _defaultAudioBufferSize;

};

} // Falltergeist

#endif // FALLTERGEIST_SETTINGS_H
