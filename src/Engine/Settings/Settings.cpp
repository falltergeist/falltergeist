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
const std::string EngineSettings::_defaultRenderer = "sdl";
const bool EngineSettings::_defaultAudioEnabled = false;
const std::string EngineSettings::_defaultInitLocation = "klamall";
const bool EngineSettings::_defaultForceLocation = false;
const std::string EngineSettings::_defaultLoggerLevel = "info";
const bool EngineSettings::_defaultLoggerColors = true;
const bool EngineSettings::_defaultDisplayFps = true;
const bool EngineSettings::_defaultDisplayMousePosition = true;

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
            writer.write(os);
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
    video->setPropertyString("renderer", _defaultRenderer);

    auto audio = ini.section("audio");
    audio->setPropertyBool("enabled", _defaultAudioEnabled);

    auto logger = ini.section("logger");
    logger->setPropertyString("level", _defaultLoggerLevel);
    logger->setPropertyBool("colors", _defaultLoggerColors);

    auto game = ini.section("game");
    game->setPropertyString("init_location", _defaultInitLocation);
    game->setPropertyBool("force_location", _defaultForceLocation);
    game->setPropertyBool("display_fps", _defaultDisplayFps);
    game->setPropertyBool("display_mouse_position", _defaultDisplayMousePosition);
}

EngineSettings::~EngineSettings()
{
}

unsigned int EngineSettings::screenWidth() const
{
    return _screenWidth;
}

unsigned int EngineSettings::screenHeight() const
{
    return _screenHeight;
}

EngineSettings::Renderer EngineSettings::renderer() const
{
    return _renderer;
}

bool EngineSettings::audioEnabled() const
{
    return _audioEnabled;
}

void EngineSettings::_setRenderer(std::string renderer)
{
    if (!(renderer == "sdl" || renderer == "opengl"))
    {
        std::cerr << "Unkown renderer: "
                << renderer << ", using " << _defaultRenderer
                << std::endl;
        renderer = _defaultRenderer;
    }

    if (renderer == "sdl")
    {
        _renderer = Renderer::SDL;
    }
    else
    {
        _renderer = Renderer::OPENGL;
    }
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

    auto renderer = video->propertyString("renderer", _defaultRenderer);
    _setRenderer(renderer);

    auto audio = ini.section("audio");
    _audioEnabled = audio->propertyBool("enabled", _defaultAudioEnabled);

    auto logger = ini.section("logger");
    Logger::setLevel(logger->propertyString("level", "info"));
    Logger::useColors(logger->propertyBool("colors", true));

    auto game = ini.section("game");
    _initLocation = game->propertyString("init_location", _defaultInitLocation);
    _forceLocation = game->propertyBool("force_location", _defaultForceLocation);


    _displayFps = game->propertyBool("display_fps", _defaultDisplayFps);
    _displayMousePosition = game->propertyBool("display_mouse_position", _defaultDisplayMousePosition);
}

bool EngineSettings::displayFps() const
{
    return _displayFps;
}

bool EngineSettings::displayMousePosition() const
{
    return _displayMousePosition;
}
}
