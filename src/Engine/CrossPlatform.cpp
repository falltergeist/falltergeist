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
    throw Exception("not supported");
#endif
}

// This method is trying to find out where are the DAT files located
std::string CrossPlatform::findDataPath()
{
    if (_dataPath.length() > 0) return _dataPath;
    debug("Looking for Fallout data files\n", DEBUG_INFO);
    std::vector<std::string> directories;
    directories.push_back(getCurrentDirectory());
    directories.push_back(getHomeDirectory() + "/.falltergeist");

    try {
        std::vector<std::string> cdDrives = getCdDrivePaths();
        directories.insert(directories.end(), cdDrives.begin(), cdDrives.end());
    }
    catch(Exception e) {
        debug("cdrom drive detection not supported");
    }

    std::vector<std::string> necessaryFiles;
    necessaryFiles.push_back("master.dat");
    necessaryFiles.push_back("critter.dat");

    for (int j = 0; j < directories.size();j++) {

        bool dataFound = true;
        for (int i = 0; i < necessaryFiles.size(); i++) {
            std::string path(directories.at(j)); 
            path.append("/");
            path.append(necessaryFiles.at(i));
            std::ifstream stream(path.c_str());
            if (stream)
            {
                debug("Searching in directory: " + directories.at(j) + " " + necessaryFiles.at(i) + " [FOUND]\n", DEBUG_INFO);
            }
            else
            {
                dataFound = false;
                debug("Searching in directory: " + directories.at(j) + " " + necessaryFiles.at(i) + " [NOT FOUND]\n", DEBUG_INFO);
            }
        }

        if (dataFound) {
            _dataPath = directories.at(j);
            return _dataPath;
        }
    }

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
