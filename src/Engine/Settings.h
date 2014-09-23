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

#ifndef FALLTERGEIST_ENGINE_SETTINGS_H
#define FALLTERGEIST_ENGINE_SETTINGS_H

// C++ standard includes

// Falltergeist includes

// Third patry includes

namespace Falltergeist
{

class IniFile;

class EngineSettings
{
public:
    enum class Renderer
    {
        OPENGL,
        SDL
    };

    EngineSettings();
    ~EngineSettings();

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    Renderer renderer() const;

    bool audioEnabled() const;

    const std::string &initialLocation() const;

    static const std::string &defaultInitLocation();

    bool forceLocation() const;

private:
    unsigned int _screenWidth;
    unsigned int _screenHeight;
    Renderer _renderer;
    bool _audioEnabled;
    std::string _initLocation;
    bool _forceLocation;

    void _setRenderer(std::string renderer);
    void _createDefaultConfig(IniFile &ini);
    void _readConfig(IniFile &ini);

    // DEFAULTS
    static const unsigned int _defaultScreenWidth;
    static const unsigned int _defaultScreenHeight;
    static const std::string _defaultRenderer;
    static const bool _defaultAudioEnabled;
    static const std::string _defaultInitLocation;
    static const bool _defaultForceLocation;
    static const std::string _defaultLoggerLevel;
    static const bool _defaultLoggerColors;
};

}

#endif // FALLTERGEIST_ENGINE_SETTINGS_H
