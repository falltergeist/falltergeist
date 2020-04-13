#include <string>
#include "CrossPlatform.h"
#include "Logger.h"
#include "Ini/File.h"
#include "Ini/Writer.h"
#include "Settings.h"

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

        Logger::info() << "Saving config to " << configFile << std::endl;

        if (!stream)
        {
            Logger::warning() << "Cannot open config file at `" << configFile << "`;" << std::endl;
            return false;
        }

        Ini::File file;

        auto video = file.section("video");
        video->setPropertyInt("width", _screenWidth);
        video->setPropertyInt("height", _screenHeight);
        video->setPropertyInt("x", _screenX);
        video->setPropertyInt("y", _screenY);
        video->setPropertyInt("scale", _scale);
        video->setPropertyBool("fullscreen", _fullscreen);
        video->setPropertyBool("always_on_top", _alwaysOnTop);

        auto audio = file.section("audio");
        audio->setPropertyBool("enabled", _audioEnabled);
        audio->setPropertyDouble("master_volume", _masterVolume);
        audio->setPropertyDouble("music_volume", _musicVolume);
        audio->setPropertyDouble("voice_volume", _voiceVolume);
        audio->setPropertyDouble("sfx_volume", _sfxVolume);
        audio->setPropertyString("music_path", _musicPath);
        audio->setPropertyInt("buffer_size", _audioBufferSize);

        auto logger = file.section("logger");
        logger->setPropertyString("level", _loggerLevel);
        logger->setPropertyBool("colors", _loggerColors);

        auto game = file.section("game");
        game->setPropertyString("init_location", _initLocation);
        game->setPropertyBool("force_location", _forceLocation);
        game->setPropertyBool("display_fps", _displayFps);
        game->setPropertyBool("worldmap_fullscreen", _worldMapFullscreen);
        game->setPropertyBool("display_mouse_position", _displayMousePosition);

        auto preferences = file.section("preferences");
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

        Ini::Writer writer(file);
        writer.write(stream);

        return true;
    }

    int Settings::screenWidth() const
    {
        return _screenWidth;
    }

    int Settings::screenHeight() const
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

        Logger::info() << "Loading config from " << configFile << std::endl;

        if (!stream)
        {
            Logger::warning() << "Cannot open config file at `" << configFile << "`;" << std::endl;
            return false;
        }

        Ini::Parser parser(stream);
        auto file = parser.parse();

        auto video = file->section("video");
        if (video)
        {
            _screenWidth = video->propertyInt("width", _screenWidth);
            _screenHeight = video->propertyInt("height", _screenHeight);
            _screenX = video->propertyInt("x", _screenX);
            _screenY = video->propertyInt("y", _screenY);
            _scale = video->propertyInt("scale", _scale);
            _fullscreen = video->propertyBool("fullscreen", _fullscreen);
            _alwaysOnTop = video->propertyBool("always_on_top", _alwaysOnTop);
        }

        auto audio = file->section("audio");
        if (audio)
        {
            _audioEnabled = audio->propertyBool("enabled", _audioEnabled);
            _masterVolume = audio->propertyDouble("master_volume", _masterVolume);
            _musicVolume = audio->propertyDouble("music_volume", _musicVolume);
            _voiceVolume = audio->propertyDouble("voice_volume", _voiceVolume);
            _sfxVolume = audio->propertyDouble("sfx_volume", _sfxVolume);
            _musicPath = audio->propertyString("music_path", _musicPath);
            _audioBufferSize = audio->propertyInt("buffer_size", _audioBufferSize);
        }

        auto logger = file->section("logger");
        if (logger)
        {
            _loggerLevel = logger->propertyString("level", _loggerLevel);
            Logger::setLevel(_loggerLevel);
            _loggerColors = logger->propertyBool("colors", _loggerColors);
        }

        auto game = file->section("game");
        if (game)
        {
            _initLocation = game->propertyString("init_location", _initLocation);
            _forceLocation = game->propertyBool("force_location", _forceLocation);
            _displayFps = game->propertyBool("display_fps", _displayFps);
            _worldMapFullscreen = game->propertyBool("worldmap_fullscreen", _worldMapFullscreen);
            _displayMousePosition = game->propertyBool("display_mouse_position", _displayMousePosition);
        }

        auto preferences = file->section("preferences");
        if (preferences)
        {
            _brightness = preferences->propertyDouble("brightness", _brightness);
            _gameDifficulty = preferences->propertyInt("game_difficulty", _gameDifficulty);
            _combatDifficulty = preferences->propertyInt("combat_difficulty", _combatDifficulty);
            _combatLooks = preferences->propertyBool("combat_looks", _combatLooks);
            _combatMessages = preferences->propertyBool("combat_messages", _combatMessages);
            _combatTaunts = preferences->propertyBool("combat_taunts", _combatTaunts);
            _combatSpeed = preferences->propertyInt("combat_speed", _combatSpeed);
            _itemHighlight = preferences->propertyBool("item_highlight", _itemHighlight);
            _languageFilter = preferences->propertyBool("language_filter", _languageFilter);
            _mouseSensitivity = preferences->propertyDouble("mouse_sensitivity", _mouseSensitivity);
            _playerSpeedup = preferences->propertyBool("player_speedup", _playerSpeedup);
            _running = preferences->propertyBool("running", _running);
            _subtitles = preferences->propertyBool("subtitles", _subtitles);
            _targetHighlight = preferences->propertyBool("target_highlight", _targetHighlight);
            _textDelay = preferences->propertyDouble("text_delay", _textDelay);
            _violenceLevel = preferences->propertyInt("violence_level", _violenceLevel);
        }

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
