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

#include "../Engine/CrossPlatform.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>



namespace Falltergeist
{
namespace CrossPlatform
{

void debug(const char * message, unsigned char level = 1)
{
    std::cout << message;
}

char * findDataPath()
{

    debug("* Searching for Fallout data files\n");

    // Сначала ищем в текущей папке
    {
        debug(" - Searching in current directory: ");
        char buffer[512];
        char * cwd = getcwd(buffer, sizeof(buffer));
        std::string path(cwd);
        path.append("/master.dat");
        std::ifstream stream(path.c_str());
        debug(cwd);
        if (stream)
        {
            debug(" - [OK]\n");

            return cwd;
        }
        else
        {
            debug(" - [FAIL]\n");
        }
    }
    // Потом ищем в домашней папке .falltergeist
    {
        debug(" - Searching in home directory: ");
        char * cwd = getenv("HOME");
        std::string path(cwd);
        path.append("/.falltergeist/master.dat");
        std::ifstream stream(path.c_str());
        debug(cwd);
        debug("/.falltergeist");
        if (stream)
        {
            path.clear();
            path.append(cwd);
            path.append("/.falltergeist");
            debug(" - [OK]\n");
            return (char *) path.c_str();
        }
        else
        {
            debug(" - [FAIL]\n");
        }
    }

    // Потом ищем подключенные диски и файлы в их корне
    // @TODO
    debug("[CRITICAL] Fallout data files are not founded\n", 0);
    return 0;
}



}
}
