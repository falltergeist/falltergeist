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

private:
    unsigned int _screenWidth;
    unsigned int _screenHeight;
    Renderer _renderer;
    bool _audioEnabled;
};

}

#endif // FALLTERGEIST_ENGINE_SETTINGS_H
