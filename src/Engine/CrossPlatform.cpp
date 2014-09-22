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
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#ifndef __APPLE__
    #include <mntent.h>
#endif

#if defined (__APPLE__)
    #include <sys/param.h>
    #include <sys/ucred.h>
    #include <sys/mount.h>
#endif

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <shlobj.h>
#elif defined(__unix__) || defined(__MACH__)
    #include <unistd.h>
#endif

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"
#include "../Engine/Logger.h"

// Third party includes

namespace Falltergeist
{

void debug(std::string message, unsigned char level)
{
    CrossPlatform::debug(message, level);
}

// static members initialization
std::string CrossPlatform::_version;
std::string CrossPlatform::_falloutDataPath;
std::string CrossPlatform::_falltergeistDataPath;
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
    CrossPlatform::debug(true, message, level);
}

void CrossPlatform::debug(bool newline, std::string message, unsigned char level)
{
    std::cout << message;

    if (newline)
    {
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::flush;
    }
}

std::string CrossPlatform::getVersion()
{
    if (_version.length() > 0) return _version;
    _version = "Falltergeist 0.1.4";
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
    std::vector<std::string> result;
 #if defined(_WIN32) || defined(WIN32)
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

#elif defined(__unix__)
        FILE* mtab = setmntent("/etc/mtab", "r");
        struct mntent* m;
        struct mntent mnt;
        char strings[4096];
        while ((m = getmntent_r(mtab, &mnt, strings, sizeof(strings))))
        {
            std::string directory = mnt.mnt_dir;
            std::string type = mnt.mnt_type;
            if (type == "iso9660")
            {
                result.push_back(directory);
            }
        }
        endmntent(mtab);
#elif defined (__APPLE__)
    struct statfs *mntbuf;
    int mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
    for ( int i = 0; i < mntsize; i++ )
    {
        std::string directory = ((struct statfs *)&mntbuf[i])->f_mntonname;
        std::string type = ((struct statfs *)&mntbuf[i])->f_fstypename;
        if (type == "cd9660")
        {
            result.push_back(directory);
        }
    }
#else
    throw Exception("CD-ROM detection not supported");
#endif
    return result;
}

// This method is trying to find out where are the DAT files located
std::string CrossPlatform::findFalloutDataPath()
{
    if (_falloutDataPath.length() > 0) return _falloutDataPath;
    Logger::info() << "Looking for Fallout data files" << std::endl;
    std::vector<std::string> directories;
    directories.push_back(getCurrentDirectory());
    directories.push_back(getHomeDirectory() + "/.falltergeist");

    try
    {
        std::vector<std::string> cdDrives = getCdDrivePaths();
        directories.insert(directories.end(), cdDrives.begin(), cdDrives.end());
    }
    catch(Exception e)
    {
        Logger::error() << e.message() << std::endl;
    }

    for (auto& directory : directories)
    {
        if (std::all_of(
                necessaryDatFiles.begin(),
                necessaryDatFiles.end(),
                [directory](std::string file)
                {
                    std::ifstream stream(directory + "/" + file);
                    if (stream)
                    {
                        Logger::info() << "Searching in directory: " << directory << " " << file << " [FOUND]" << std::endl;
                        return true;
                    }
                    else
                    {
                        Logger::info() << "Searching in directory: " << directory << " " << file << " [NOT FOUND]" << std::endl;
                        return false;
                    }
                })
           )
        {
            _falloutDataPath = directory;
            return _falloutDataPath;
        }
    }

    throw Exception("Fallout data files are not found!");
}

std::string CrossPlatform::findFalltergeistDataPath()
{
    if (_falltergeistDataPath.length() > 0) return _falltergeistDataPath;
    Logger::info() << "Looking for Falltergeist data files" << std::endl;
    std::vector<std::string> directories;
    directories.push_back(getCurrentDirectory());
    directories.push_back(getHomeDirectory() + "/.falltergeist");

    for (auto& directory : directories)
    {
        std::ifstream stream(directory + "/data/dialogs.lst");
        if (stream)
        {
            Logger::info() << "Searching in directory: " << directory << " data/dialogs.lst [FOUND]" << std::endl;
            _falltergeistDataPath = directory;
            return _falltergeistDataPath;
        }
        else
        {
            Logger::info() << "Searching in directory: " << directory << " data/dialogs.lst [NOT FOUND]" << std::endl;
        }
    }

    throw Exception("Falltergeist data files are not found!");
}

// this method looks for available dat files
std::vector<std::string> * CrossPlatform::findFalloutDataFiles()
{
    if (_dataFiles) return _dataFiles;

    // looking for all available dat files in directory
    DIR * pxDir = opendir(CrossPlatform::findFalloutDataPath().c_str());
    if (!pxDir)
    {
        throw Exception("Can't open data directory: " + CrossPlatform::findFalloutDataPath());
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

std::ostream &CrossPlatform::debug(unsigned char level)
{
    // /dev/null-like stream
    static std::ostream nullstream(nullptr);
    // Check debug level
    // TODO: perform real check
    if (false)
    {
        return nullstream << std::dec;
    }
    else
    {
        return std::cout << std::dec;
    }
}
}
