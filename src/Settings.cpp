// Project includes
#include "CrossPlatform.h"
#include "Logger.h"
#include "Settings.h"

// Third-party includes
#include <boost/property_tree/ini_parser.hpp>

// stdlib
#include <string>

namespace Falltergeist
{
    Settings::Settings()
    {
        if (!load()) {
            save();
        }
    }

    Settings::~Settings()
    {
    }

    bool Settings::save()
    {
        CrossPlatform::createDirectory(CrossPlatform::getConfigPath());
        std::string configFile = CrossPlatform::getConfigPath() + "/config.ini";
        std::ofstream stream(configFile);

        Logger::info("") << "Saving config to " << configFile << std::endl;

        if (!stream)
        {
            Logger::warning("") << "Cannot open config file at `" << configFile << "`;" << std::endl;
            return false;
        }

        boost::property_tree::ptree data;

        data.put<int>("video.width", _screenWidth);
        data.put<int>("video.height", _screenHeight);
        data.put<int>("video.x", _screenX);
        data.put<int>("video.y", _screenY);
        data.put<int>("video.scale", _scale);
        data.put<bool>("video.fullscreen", _fullscreen);
        data.put<bool>("video.always_on_top", _alwaysOnTop);

        data.put<bool>("audio.enabled", _audioEnabled);
        data.put<double>("audio.master_volume", _masterVolume);
        data.put<double>("audio.music_volume", _musicVolume);
        data.put<double>("audio.voice_volume", _voiceVolume);
        data.put<double>("audio.sfx_volume", _sfxVolume);
        data.put<std::string>("audio.music_path", _musicPath);
        data.put<int>("audio.buffer_size", _audioBufferSize);

        data.put<std::string>("logger.level", _loggerLevel);
        data.put<bool>("logger.colors", _loggerColors);

        data.put<std::string>("game.init_location", _initLocation);
        data.put<bool>("game.force_location", _forceLocation);
        data.put<bool>("game.display_fps", _displayFps);
        data.put<bool>("game.worldmap_fullscreen", _worldMapFullscreen);
        data.put<bool>("game.display_mouse_position", _displayMousePosition);

        data.put<double>("preferences.brightness", _brightness);
        data.put<int>("preferences.game_difficulty", _gameDifficulty);
        data.put<int>("preferences.combat_difficulty", _combatDifficulty);
        data.put<bool>("preferences.combat_looks", _combatLooks);
        data.put<bool>("preferences.combat_messages", _combatMessages);
        data.put<bool>("preferences.combat_taunts", _combatTaunts);
        data.put<int>("preferences.combat_speed", _combatSpeed);
        data.put<bool>("preferences.item_highlight", _itemHighlight);
        data.put<bool>("preferences.language_filter", _languageFilter);
        data.put<double>("preferences.mouse_sensitivity", _mouseSensitivity);
        data.put<bool>("preferences.player_speedup", _playerSpeedup);
        data.put<bool>("preferences.running", _running);
        data.put<bool>("preferences.subtitles", _subtitles);
        data.put<bool>("preferences.target_highlight", _targetHighlight);
        data.put<double>("preferences.text_delay", _textDelay);
        data.put<int>("preferences.violence_level", _violenceLevel);

        boost::property_tree::ini_parser::write_ini(stream, data);

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

    int Settings::screenX() const
    {
        return _screenX;
    }

    int Settings::screenY() const
    {
        return _screenY;
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
        std::string configFile = CrossPlatform::getConfigPath() + "/config.ini";
        std::ifstream stream(configFile);

        Logger::info("") << "Loading config from " << configFile << std::endl;

        if (!stream)
        {
            Logger::warning("") << "Cannot open config file at `" << configFile << "`;" << std::endl;
            return false;
        }

        boost::property_tree::ptree data;
        boost::property_tree::ini_parser::read_ini(stream, data);

        _screenWidth = data.get<int>("video.width", _screenWidth);
        _screenHeight = data.get<int>("video.height", _screenHeight);
        _screenX = data.get<int>("video.x", _screenX);
        _screenY = data.get<int>("video.y", _screenY);
        _scale = data.get<int>("video.scale", _scale);
        _fullscreen = data.get<bool>("video.fullscreen", _fullscreen);
        _alwaysOnTop = data.get<bool>("video.always_on_top", _alwaysOnTop);

        _audioEnabled = data.get<bool>("audio.enabled", _audioEnabled);
        _masterVolume = data.get<double>("audio.master_volume", _masterVolume);
        _musicVolume = data.get<double>("audio.music_volume", _musicVolume);
        _voiceVolume = data.get<double>("audio.voice_volume", _voiceVolume);
        _sfxVolume = data.get<double>("audio.sfx_volume", _sfxVolume);
        _musicPath = data.get<std::string>("audio.music_path", _musicPath);
        _audioBufferSize = data.get<int>("audio.buffer_size", _audioBufferSize);

        _loggerLevel = data.get<std::string>("logger.level", _loggerLevel);
        Logger::setLevel(_loggerLevel);
        _loggerColors = data.get<bool>("logger.colors", _loggerColors);

        _initLocation = data.get<std::string>("game.init_location", _initLocation);
        _forceLocation = data.get<bool>("game.force_location", _forceLocation);
        _displayFps = data.get<bool>("game.display_fps", _displayFps);
        _worldMapFullscreen = data.get<bool>("game.worldmap_fullscreen", _worldMapFullscreen);
        _displayMousePosition = data.get<bool>("game.display_mouse_position", _displayMousePosition);

        _brightness = data.get<double>("preferences.brightness", _brightness);
        _gameDifficulty = data.get<int>("preferences.game_difficulty", _gameDifficulty);
        _combatDifficulty = data.get<int>("preferences.combat_difficulty", _combatDifficulty);
        _combatLooks = data.get<bool>("preferences.combat_looks", _combatLooks);
        _combatMessages = data.get<bool>("preferences.combat_messages", _combatMessages);
        _combatTaunts = data.get<bool>("preferences.combat_taunts", _combatTaunts);
        _combatSpeed = data.get<int>("preferences.combat_speed", _combatSpeed);
        _itemHighlight = data.get<bool>("preferences.item_highlight", _itemHighlight);
        _languageFilter = data.get<bool>("preferences.language_filter", _languageFilter);
        _mouseSensitivity = data.get<double>("preferences.mouse_sensitivity", _mouseSensitivity);
        _playerSpeedup = data.get<bool>("preferences.player_speedup", _playerSpeedup);
        _running = data.get<bool>("preferences.running", _running);
        _subtitles = data.get<bool>("preferences.subtitles", _subtitles);
        _targetHighlight = data.get<bool>("preferences.target_highlight", _targetHighlight);
        _textDelay = data.get<double>("preferences.text_delay", _textDelay);
        _violenceLevel = data.get<int>("preferences.violence_level", _violenceLevel);

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

    bool Settings::alwaysOnTop() const
    {
        return _alwaysOnTop;
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
