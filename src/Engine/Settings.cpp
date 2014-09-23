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

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"
#include "../Engine/IniFile.h"
#include "../Engine/IniWriter.h"
#include "../Engine/Logger.h"
#include "../Engine/Settings.h"

// Third party includes

namespace Falltergeist
{

const unsigned int EngineSettings::_defaultScreenWidth = 640;
const unsigned int EngineSettings::_defaultScreenHeight = 480;
const std::string EngineSettings::_defaultRenderer = "sdl";
const bool EngineSettings::_defaultAudioEnabled = false;
const std::string EngineSettings::_defaultInitLocation = "klamall";

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

        auto video = ini->section("video");
        _screenWidth = video->propertyInt("width", _defaultScreenWidth);
        _screenHeight = video->propertyInt("height", _defaultScreenHeight);

        auto renderer = video->propertyString("renderer", _defaultRenderer);
        _setRenderer(renderer);

        auto audio = ini->section("audio");
        _audioEnabled = audio->propertyBool("enabled", _defaultAudioEnabled);

        auto logger = ini->section("logger");
        Logger::setLevel(logger->propertyString("level", "info"));
        Logger::useColors(logger->propertyBool("colors", true));

        auto game = ini->section("game");
        _initLocation = game->propertyString("init_location", _defaultInitLocation);
    }
    else
    {
        Logger::warning() << "Cannot open config file at `" << configFile << "`; creating default configuraton file" << std::endl;
        stream.close();

        _screenWidth = _defaultScreenWidth;
        _screenHeight = _defaultScreenHeight;
        _setRenderer(_defaultRenderer);
        _audioEnabled = _defaultAudioEnabled;

        IniFile ini;

        auto video = ini.section("video");
        video->setPropertyInt("width", _defaultScreenWidth);
        video->setPropertyInt("height", _defaultScreenHeight);
        video->setPropertyString("renderer", _defaultRenderer);

        auto audio = ini.section("audio");
        audio->setPropertyBool("enabled", _defaultAudioEnabled);

        // Create config path if not exists
        CrossPlatform::createDirectory(configPath);

        // Write default configuraton
        IniWriter writer(ini);
        std::ofstream os(configFile);
        writer.write(os);
    }
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

}