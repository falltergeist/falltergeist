/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#if defined(_WIN32) || defined(_MSC_VER)

// C++ standard includes

#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <time.h>

// Falltergeist includes
#include "Platform.h"
#include "../Exception.h"
#include "../Logger.h"

// Third party includes
#include <SDL.h>
#include <windows.h>
#include <shlobj.h>

namespace Falltergeist
{

// static members initialization
std::string CrossPlatform::_version;
std::string CrossPlatform::_falloutDataPath;
std::string CrossPlatform::_falltergeistDataPath;
std::vector<std::string> *CrossPlatform::_dataFiles = 0;
const std::vector<std::string> CrossPlatform::necessaryDatFiles = { "master.dat", "critter.dat" };

CrossPlatform::CrossPlatform()
{
}

CrossPlatform::~CrossPlatform()
{
}

std::string CrossPlatform::getVersion()
{
    if (_version.length() > 0) return _version;
    _version = "Falltergeist 0.2.0";
    _version += " (Windows)";
    return _version;
}

std::string CrossPlatform::getHomeDirectory()
{
    char cwd[MAX_PATH];
    LPITEMIDLIST pidl;
    SHGetSpecialFolderLocation(NULL, CSIDL_PROFILE, &pidl);
    SHGetPathFromIDList(pidl, cwd);
    return std::string(cwd);
}

std::string CrossPlatform::getExecutableDirectory()
{
    char* buffer = SDL_GetBasePath();
    std::string path(buffer);
    SDL_free(buffer);
    return path;
}

std::vector<std::string> CrossPlatform::getCdDrivePaths()
{
    std::vector<std::string> result;
    // Looking for data files on CD-ROM drives
    char buf[MAX_PATH];
    GetLogicalDriveStringsA(sizeof(buf), buf);

    for (char * s = buf; *s; s += strlen(s) + 1)
    {
        if (GetDriveTypeA(s) == DRIVE_CDROM)
        {
            result.push_back(std::string(s));
        }
    }

    return result;
}

// This method is trying to find out where are the DAT files located
std::string CrossPlatform::findFalloutDataPath()
{
    if (_falloutDataPath.length() > 0)
        return _falloutDataPath;
    Logger::info() << "Looking for Fallout data files" << std::endl;
    std::vector<std::string> directories;
    directories.push_back(getExecutableDirectory());

    for (auto &directory : getDataPaths())
    {
        directories.push_back(directory);
    }

    try
    {
        std::vector<std::string> cdDrives = getCdDrivePaths();
        directories.insert(directories.end(), cdDrives.begin(), cdDrives.end());
    }
    catch (Exception e)
    {
        Logger::error() << e.what() << std::endl;
    }

    for (auto &directory : directories)
    {
        if (std::all_of(
            necessaryDatFiles.begin(),
            necessaryDatFiles.end(),
            [directory](const std::string& file) {
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
    if (_falltergeistDataPath.length() > 0)
        return _falltergeistDataPath;
    Logger::info() << "Looking for Falltergeist data files" << std::endl;
    std::vector<std::string> directories;
    directories.push_back(getExecutableDirectory());

    for (auto &directory : getDataPaths())
    {
        directories.push_back(directory);
    }

    for (auto &directory : directories)
    {
        std::ifstream stream(directory + "/data/movies.lst");
        if (stream)
        {
            Logger::info() << "Searching in directory: " << directory << "data/movies.lst [FOUND]" << std::endl;
            _falltergeistDataPath = directory;
            return _falltergeistDataPath;
        }
        else
        {
            Logger::info() << "Searching in directory: " << directory << "data/movies.lst [NOT FOUND]" << std::endl;
        }
    }

    throw Exception("Falltergeist data files are not found!");
}

// this method looks for available dat files
std::vector<std::string> *CrossPlatform::findFalloutDataFiles()
{
    if (_dataFiles)
        return _dataFiles;

    std::string path = CrossPlatform::findFalloutDataPath() + "*";
    WIN32_FIND_DATA findData;
    ZeroMemory(&findData, sizeof(findData));
    HANDLE handle = FindFirstFileA(path.c_str(), &findData);
    if (handle == INVALID_HANDLE_VALUE) {
        throw Exception("Can't open data directory: " + CrossPlatform::findFalloutDataPath());
    }

    _dataFiles = new std::vector<std::string>(necessaryDatFiles);

    do {
        std::string filename(findData.cFileName);

        if (filename.length() > 4) // exclude . and ..
        {
            std::string ext = filename.substr(filename.size() - 4, 4);
            if (ext == ".dat")
            {
                if (filename.length() == 12 && filename.substr(0, 5) == "patch")
                    _dataFiles->insert(_dataFiles->begin(), filename);
            }
        }

    } while (FindNextFile(handle, &findData));

    FindClose(handle);
    return _dataFiles;
}

bool CrossPlatform::_createDirectory(const char *dir)
{
    DWORD attrs = GetFileAttributes(dir);

    // Assume path exists
    if (attrs != INVALID_FILE_ATTRIBUTES)
    {
        // Directory already exists
        if (attrs & FILE_ATTRIBUTE_DIRECTORY) return false;

        throw std::runtime_error("Path `" + std::string(dir) + "' already exists and is not a directory");
    }
    else
    {
        if (CreateDirectory(dir, NULL) != 0) return true;

        DWORD errorId = GetLastError();

        // FIXME: Use FormatMessage to get error string
        throw std::runtime_error("CreateDirectory failed with code: " + std::to_string(errorId));
    }
    return false;
}

void CrossPlatform::createDirectory(std::string path)
{
    // Start index of 1 means that we skip root directory.
    for (auto dirDelim = path.find_first_of('/', 1U); dirDelim != std::string::npos;
         dirDelim = path.find_first_of('/', dirDelim + 1)) {
        path[dirDelim] = '\0';
        _createDirectory(path.c_str());
        path[dirDelim] = '/';
    }
    _createDirectory(path.c_str());
}

std::string CrossPlatform::getConfigPath()
{
    char path[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, path);
    return std::string(path) + "/falltergeist";
}

std::vector<std::string> CrossPlatform::getDataPaths()
{
    std::vector<std::string> _dataPaths;
    _dataPaths.push_back(getConfigPath());
    return _dataPaths;
}

void CrossPlatform::getTime(TimeInfo * out) {
    if (!out)
        throw Exception("nullptr passed into getTime");

    // Get ticks per second
    LARGE_INTEGER Frequency;
    if (QueryPerformanceFrequency(&Frequency) == FALSE)
    {
        throw Exception("Call to QueryPerformanceFrequency failed");
    }

    // Get current tick count
    LARGE_INTEGER time;
    if (QueryPerformanceCounter(&time) == FALSE)
    {
        throw Exception("Call to QueryPerformanceCounter failed");
    }

    out->_sec = time.QuadPart / Frequency.QuadPart;
    out->_nano = time.QuadPart / (Frequency.QuadPart / 1000000000ull);
}
}

#endif // #if defined(_WIN32)
