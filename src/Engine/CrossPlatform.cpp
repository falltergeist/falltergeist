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
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"

// Third party includes

// Platform specific includes
#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <shlobj.h>
#elif defined(__unix__)
    #include <unistd.h>
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
const std::vector<std::string> CrossPlatform::necessaryDatFiles = {"master.dat", "critter.dat"};


CrossPlatform::CrossPlatform()
{
}

CrossPlatform::~CrossPlatform()
{
}

void CrossPlatform::debug(std::string message, unsigned char level)
{
    std::cout << message << std::endl;
}

std::string CrossPlatform::getVersion()
{
    if (_version.length() > 0) return _version;
    _version = "Falltergeist 0.0.8";
#if defined(_WIN32) || defined(WIN32)
    _version += " (Windows)";
#elif defined(__unix__)
    _version += " (Linux)";
#elif defined(__MACH__)
    _version += " (Apple)";
#endif
    return _version;
}

std::string CrossPlatform::getHomeDirectory() {
#if defined(_WIN32) || defined(WIN32)        
    char cwd[256];
    LPITEMIDLIST pidl;
    SHGetSpecialFolderLocation(NULL, CSIDL_PROFILE  ,&pidl);
    SHGetPathFromIDList(pidl, cwd);
#else
    char * cwd = getenv("HOME");
#endif
    return std::string(cwd);
}

std::string CrossPlatform::getCurrentDirectory() {
    char buffer[512];
    char * cwd = getcwd(buffer, sizeof(buffer));
    return std::string(cwd);
}

std::vector<std::string> CrossPlatform::getCdDrivePaths() {
 #if defined(_WIN32) || defined(WIN32)
    std::vector<std::string> result;
    // Looking for data files on CD-ROM drives
    char buf[256];
    GetLogicalDriveStringsA(sizeof(buf), buf);

    for(char * s = buf; *s; s += strlen(s) + 1)
    {
        if (GetDriveTypeA(s) == DRIVE_CDROM)
        {
            result.push_back(std::string(s));
        }
    }

    return result;
#else
    throw Exception("CD-ROM detection not supported");
#endif
}

// This method is trying to find out where are the DAT files located
std::string CrossPlatform::findDataPath()
{
    if (_dataPath.length() > 0) return _dataPath;
    debug("Looking for Fallout data files", DEBUG_INFO);
    std::vector<std::string> directories;
    directories.push_back(getCurrentDirectory());
    directories.push_back(getHomeDirectory() + "/.falltergeist");

    try {
        std::vector<std::string> cdDrives = getCdDrivePaths();
        directories.insert(directories.end(), cdDrives.begin(), cdDrives.end());
    }
    catch(Exception e) {
        debug(e.message());
    }

    for (auto& directory : directories) {
        if (std::all_of(
                necessaryDatFiles.begin(),
                necessaryDatFiles.end(),
                [directory](std::string file) 
                {
                    std::ifstream stream(directory + "/" + file);
                    if (stream)
                    {
                        debug("Searching in directory: " + directory + " " + file + " [FOUND]", DEBUG_INFO);
                        return true;
                    }
                    else
                    {
                        debug("Searching in directory: " + directory + " " + file + " [NOT FOUND]", DEBUG_INFO);
                        return false;
                    }
                })
           )
        {
            _dataPath = directory;
            return _dataPath;
        }
    }

    throw Exception("Fallout data files are not found!");
}

// this method looks for available dat files
std::vector<std::string> * CrossPlatform::findDataFiles()
{
    if (_dataFiles) return _dataFiles;

    // looking for all available dat files in directory
    DIR * pxDir = opendir(CrossPlatform::findDataPath().c_str());
    if (!pxDir)
    {
        throw Exception("Can't open data directory: " + CrossPlatform::findDataPath());
    }
    _dataFiles = new std::vector<std::string>(necessaryDatFiles);
    struct dirent * pxItem = 0;
    while((pxItem = readdir(pxDir)))
    {
        std::string filename(pxItem->d_name);
        if (filename.length() > 4) // exclude . and ..
        {
            std::string ext = filename.substr(filename.size()-4, 4);
            if (ext == ".dat")
            {
                if (filename.length() == 12 && filename.substr(0,5) == "patch") _dataFiles->push_back(filename);
            }
        }
    }
    closedir(pxDir);

    return _dataFiles;
}

}
