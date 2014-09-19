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
#include "../Engine/Settings.h"

// Third party includes

namespace Falltergeist
{

EngineSettings::EngineSettings()
{
    std::string configFile = CrossPlatform::getHomeDirectory() + "/.falltergeist/config.ini";
    std::ifstream stream(configFile);

    if (!stream) throw Exception("Failed to locate config file " + configFile);

    IniParser iniParser(stream);
    auto ini = iniParser.parse();

    auto video = ini->section("video");
    _screenWidth  = video->template property<int>("width", 640);
    _screenHeight = video->template property<int>("height", 480);

    auto renderer = video->template property<std::string>("renderer", "sdl");

    if (renderer == "sdl")
    {
        _renderer = Renderer::SDL;
    }
    else if (renderer == "opengl")
    {
        _renderer = Renderer::OPENGL;
    }
    else
    {
        std::cerr << "Unkown rendered: " << renderer << std::endl;
    }

    auto audio = ini->section("audio");
    _audioEnabled = audio->template property<bool>("enabled", false);
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
}
