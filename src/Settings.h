/*
 * Copyright 2012-2016 Falltergeist Developers.
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
}
namespace Lua
{
    class Script;
}

class Settings
{
public:

    Settings();
    ~Settings();

    bool save();
    bool load();

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const std::string& initialLocation() const;

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
    unsigned int _screenWidth = 640;
    unsigned int _screenHeight = 480;
    std::string _initLocation = "klamall";
    bool _forceLocation = false;
    bool _displayFps = true;
    bool _worldMapFullscreen = false;
    bool _displayMousePosition = true;
    std::string _loggerLevel = "info";
    bool _loggerColors = true;
    unsigned int _scale = 0;
    bool _fullscreen = false;

    double _brightness = 1.0;
    unsigned int _gameDifficulty = 1;
    unsigned int _combatDifficulty = 1;
    bool _combatLooks = false;
    bool _combatMessages = true;
    bool _combatTaunts = false;
    unsigned int _combatSpeed = 0;
    bool _itemHighlight = false;
    bool _languageFilter = false;
    double _mouseSensitivity = 1.0;
    bool _playerSpeedup = false;
    bool _running = false;
    bool _subtitles = false;
    bool _targetHighlight = false;
    double _textDelay = 0.0;
    unsigned int _violenceLevel = 2;
    // [sound]
    std::string _musicPath = "data/sound/music/";
    bool _audioEnabled = true;
    double _masterVolume = 1.0;
    double _musicVolume = 1.0;
    double _sfxVolume = 1.0;
    double _voiceVolume = 1.0;
    int _audioBufferSize = 512;
};

} // Falltergeist

#endif // FALLTERGEIST_SETTINGS_H
