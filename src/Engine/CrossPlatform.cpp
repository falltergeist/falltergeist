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

// C++ standard includes
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

// Platform specific includes
#if defined(_WIN32)
#include <shlobj.h>
#endif

// Falltergeist includes
#include "../Engine/CrossPlatform.h"

namespace Falltergeist
{
namespace CrossPlatform
{

void debug(std::string message, unsigned char level)
{
    std::cout << message;
}

// This method is trying to find out where are the DAT files located
std::string findDataPath()
{
    if (dataPath.length() > 0) return dataPath;
    debug("Looking for Fallout data files\n", DEBUG_INFO);

    // First of all we are trying to look in the current folder (where the binary file located)
    {       
        char buffer[512];
        char * cwd = getcwd(buffer, sizeof(buffer));
        std::string path = cwd + std::string("/master.dat");
        std::ifstream stream(path.c_str());
        if (stream)
        {
            debug("Searching in current directory: " + std::string(cwd) + " [FOUND]\n", DEBUG_INFO);
            dataPath = cwd;
            return cwd;
        }
        else
        {
            debug("Searching in current directory: " + std::string(cwd) + " [NOT FOUND]\n", DEBUG_INFO);
        }
    }

    // Then trying to search in user home directory  ~/.falltergeist
    {
        char * cwd;
#if defined(_WIN32)
        SHGetSpecialFolderPath(0, cwd, CSIDL_PROFILE, FALSE);
#else
        cwd = getenv("HOME");
#endif
        std::string path(std::string(cwd) + "/.falltergeist/master.dat");
        std::ifstream stream(path.c_str());
        if (stream)
        {
            path = std::string(cwd) + "/.falltergeist";
            debug("Searching in home directory: " + path + " [FOUND]\n", DEBUG_INFO);
            dataPath = path;
            return path;
        }
        else
        {
            debug("Searching in home directory: " + std::string(cwd) + "/.falltergeist" + " [NOT FOUND]\n", DEBUG_INFO);
        }
    }

    // @TODO search on external storages (flash drives, CD-ROMs... etc)...

    debug("Fallout data files are not found\n", DEBUG_CRITICAL);
    return 0;
}

// this method looks for available dat files
std::vector<std::string> * findDataFiles()
{
    std::vector<std::string> * files = new std::vector<std::string>;
    files->push_back("master.dat"); // reserverd for master.dat
    files->push_back("critter.dat"); // reserverd for critter.dat

    for (int i = 0; i < files->size(); i++) {
        std::string path = findDataPath() + "/" + files->at(i);
        std::ifstream stream(path.c_str());
        if (!stream) {
            debug(files->at(i) + " not found!\n", DEBUG_CRITICAL);
            return 0;
        }
    }

    return files;
}

// Fallout data files names can be in upper,lower or even mixed case.
// In falltergeist all filenames are in lower case
// This method looks for file aliases
// Example: "maps/ARDEAD.map" is alias of "maps/ardead.map"
// It needed when we are reading unpacked files from data directory
std::string findFileAlias(std::string path, std::string filename)
{
    std::string full_path = path + "/" + filename;
    std::ifstream stream(full_path.c_str());
    if (!stream) {
        debug(full_path + " not found!\n", DEBUG_CRITICAL);
        return "";
    }
    return full_path;
}

}
}
