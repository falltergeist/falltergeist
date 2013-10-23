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
//#include <algorithm>
//#include <string.h>

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"

// Third party includes

// Platform specific includes
#if defined(_WIN32) || defined(WIN32)
        #include <windows.h>
        #include <shlobj.h>
#endif

namespace Falltergeist
{

void debug(std::string message, unsigned char level)
{
    CrossPlatform::debug(message, level);
}

// static members initialization
std::string CrossPlatform::_version;
std::string CrossPlatform::_dataPath;
std::vector<std::string> * CrossPlatform::_dataFiles = 0;


CrossPlatform::CrossPlatform()
{
}

CrossPlatform::~CrossPlatform()
{
}

void CrossPlatform::debug(std::string message, unsigned char level)
{
    std::cout << message;
}

std::string CrossPlatform::getVersion()
{
    if (_version.length() > 0) return _version;
    _version = "Falltergeist 0.0.7";
#if defined(_WIN32) || defined(WIN32)
    _version += " (Windows)";
#elif defined(__unix__)
    _version += " (Linux)";
#elif defined(__MACH__)
    _version += " (Apple)";
#endif
    return _version;
}

// This method is trying to find out where are the DAT files located
std::string CrossPlatform::findDataPath()
{
    if (_dataPath.length() > 0) return _dataPath;
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
            _dataPath = cwd;
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
#if defined(_WIN32) || defined(WIN32)
        SHGetSpecialFolderPath(0, cwd, CSIDL_PROFILE, FALSE);
#else
        cwd = getenv("HOME");
#endif
        std::string path(std::string(cwd) + "/.falltergeist/master.dat");
        std::ifstream stream(path.c_str());
        if (stream)
        {
            path = std::string(cwd) + "/.falltergeist";
            debug("Searching in user directory: " + path + " [FOUND]\n", DEBUG_INFO);
            _dataPath = path;
            return path;
        }
        else
        {
            debug("Searching in user directory: " + std::string(cwd) + "/.falltergeist" + " [NOT FOUND]\n", DEBUG_INFO);
        }
    }

 #if defined(_WIN32) || defined(WIN32)
    // Looking for data files on CD-ROM drives
    char buf[26];
    GetLogicalDriveStringsA(sizeof(buf),buf);
    for(char * s = buf; *s; s += strlen(s)+1)
    {
        if (GetDriveTypeA(s) == DRIVE_CDROM)
        {
            std::string path = std::string(s) + "master.dat";
            std::ifstream stream(path.c_str());
            if (stream)
            {
                _dataPath = s;
                debug("Searching in CD-ROM drive " + _dataPath + " [FOUND]\n", DEBUG_INFO);
                return _dataPath;
            }
            else
            {
                debug("Searching in CD-ROM drive " + std::string(s) + " [NOT FOUND]\n", DEBUG_INFO);
            }            
        }
    }
#endif

    throw Exception("Fallout data files are not found!");
}

// this method looks for available dat files
std::vector<std::string> * CrossPlatform::findDataFiles()
{
    if (_dataFiles) return _dataFiles;

    _dataFiles = new std::vector<std::string>;
    _dataFiles->push_back(""); // reserverd for master.dat
    _dataFiles->push_back(""); // reserverd for critter.dat

    // looking for all available dat files in directory
    DIR * pxDir = opendir(CrossPlatform::findDataPath().c_str());
    if (!pxDir)
    {
        throw Exception("Can't open data directory: " + CrossPlatform::findDataPath());
    }
    struct dirent * pxItem = 0;
    while((pxItem = readdir(pxDir)))
    {
        std::string filename(pxItem->d_name);
        if (filename.length() > 4) // exclude . and ..
        {
            std::string ext = filename.substr(filename.size()-4, 4);
            if (ext == ".dat")
            {
                if (filename == "master.dat")  _dataFiles->at(0) = "master.dat";
                if (filename == "critter.dat") _dataFiles->at(1) = "critter.dat";
                if (filename.length() == 12 && filename.substr(0,5) == "patch") _dataFiles->push_back(filename);
            }
        }
    }
    closedir(pxDir);

    if (_dataFiles->at(0) != "master.dat")  throw Exception("master.dat not found!");
    if (_dataFiles->at(1) != "critter.dat") throw Exception("critter.dat not found!");

    return _dataFiles;
}

}
