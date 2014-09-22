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

class CrossPlatform
{
protected:
    static std::string _falloutDataPath;
    static std::string _falltergeistDataPath;
    static std::vector<std::string>* _dataFiles;
    static std::string _version;
    const static std::vector<std::string> necessaryDatFiles;
public:
    CrossPlatform();
    ~CrossPlatform();

    static std::string getVersion();
    static std::string getHomeDirectory();
    static std::string getCurrentDirectory(); 
    static std::vector<std::string> getCdDrivePaths();
    static std::string findFalloutDataPath();
    static std::string findFalltergeistDataPath();
    static std::vector<std::string> * findFalloutDataFiles();
};

}
#endif // FALLTERGEIST_CROSSPLATFORM_H
