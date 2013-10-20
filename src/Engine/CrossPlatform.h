/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_CROSSPLATFORM_H
#define FALLTERGEIST_CROSSPLATFORM_H

// C++ standard includes
#include <string>
#include <list>
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace CrossPlatform
{
    static std::string dataPath;
    enum DebugLevel { DEBUG_INFO = 0, DEBUG_ERROR, DEBUG_CRITICAL };
    std::string findFileAlias(std::string path, std::string filename);
    std::string findDataPath();
    std::vector<std::string> * findDataFiles();
    void debug(std::string message, unsigned char level = 0);
}
}

#endif // FALLTERGEIST_CROSSPLATFORM_H
