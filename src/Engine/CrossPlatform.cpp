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
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

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
        char * cwd = getenv("HOME");
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
    files->push_back(""); // reserverd for master.dat
    files->push_back(""); // reserverd for critter.dat

    // looking for all available dat files in directory
    DIR * pxDir = opendir(findDataPath().c_str());
    struct dirent * pxItem = NULL;
    if(pxDir != NULL)
    {
        while((pxItem = readdir(pxDir)))
        {
            std::string filename(pxItem->d_name);
            std::transform(filename.begin(),filename.end(),filename.begin(), ::tolower);
            if (filename.length() > 4)
            {
                std::string ext = filename.substr(filename.size()-4,4);
                if (ext.compare(".dat") == 0)
                {
                    if (filename.compare("master.dat") == 0) files->at(0).append("master.dat");
                    if (filename.compare("critter.dat") == 0) files->at(1).append("critter.dat");
                    if (filename.length() == 12 && filename.substr(0,5).compare("patch") == 0) files->push_back(filename);
                }
            }
        }
        closedir(pxDir);
    }
    else
    {
        debug("Unable to read data files directory\n", DEBUG_CRITICAL);
    }

    if (files->at(0).compare("master.dat") != 0)
    {
        debug("master.dat not found!\n", DEBUG_CRITICAL);
        return 0;
    }
    if (files->at(1).compare("critter.dat") != 0)
    {
        debug("critter.dat not found!\n", DEBUG_CRITICAL);
        return 0;
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
    DIR * dir = opendir(path.c_str());
    if (!dir) return 0;
    struct dirent * entry;

    int pos = filename.find('/');
    //complex filename
    if (pos > 0)
    {
        std::string folder(filename.substr(0, pos));
        // check if there is a folder
        while ((entry = readdir(dir)))
        {
            std::string dirname(entry->d_name);
            std::transform(dirname.begin(),dirname.end(),dirname.begin(), ::tolower);
            if (dirname.compare(folder) == 0 && entry->d_type == DT_DIR)
            {
                path.append("/").append(entry->d_name);
                std::string alias = findFileAlias(path, filename.substr(pos+1, filename.length()));
                if (alias.length())
                {
                    std::string newname = std::string(entry->d_name) + "/" + alias;
                    closedir(dir);
                    return newname;
                }
            }
        }
    }
    else
    {
        while ((entry = readdir(dir)))
        {
            std::string fname = entry->d_name;
            std::transform(fname.begin(),fname.end(),fname.begin(), ::tolower);
            if (fname.compare(filename) == 0 && entry->d_type != DT_DIR)
            {
                fname = entry->d_name;
                return fname;
            }
        }
    }
    closedir(dir);
    return ""; // empty string if nothing found
}

}
}
