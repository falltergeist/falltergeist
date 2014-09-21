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
#include <iostream>

// Falltergeist includes
#include "../Engine/Logger.h"

// Third party includes

namespace Falltergeist
{

Logger::Level Logger::level()
{
    return _level;
}

void Logger::setLevel(Logger::Level level)
{
    _level = level;
}

std::ostream &Logger::log(Logger::Level level, const std::string &subsystem)
{
    // A /dev/null-like stream
    static std::ostream nullstream(nullptr);
    if (level < _level) return nullstream;
    return std::cout << levelString(level) << subsystem << " " << std::dec;
}

// Used as default value when reading from config
Logger::Level Logger::_level = Logger::Level::DEBUG;

const char *Logger::levelString(Logger::Level level)
{
    switch (level)
    {
#if defined(__unix__) || defined(__APPLE__)
        case Logger::Level::DEBUG:
            return "[DEBUG]";
        case Logger::Level::INFO:
            return "\x1b[32m[INFO]\x1b[0m";
        case Logger::Level::WARNING:
            return "\x1b[33m[WARNING]\x1b[0m";
        case Logger::Level::ERROR:
            return "\x1b[31m[ERROR]\x1b[0m";
        case Logger::Level::CRITICAL:
            return "\x1b[31;1m[CRITICAL]\x1b[0m";
#else // Assume Windows
        case Logger::Level::DEBUG:
            return "[DEBUG]";
        case Logger::Level::INFO:
            return "[INFO]";
        case Logger::Level::WARNING:
            return "[WARNING]";
        case Logger::Level::ERROR:
            return "[ERROR]";
        case Logger::Level::CRITICAL:
            return "[CRITICAL]";
#endif
    };

    return "[UNKOWN]";
}

std::ostream &Logger::debug(const std::string &subsystem)
{
    return log(Logger::Level::DEBUG, subsystem);
}

std::ostream &Logger::info(const std::string &subsystem)
{
    return log(Logger::Level::INFO, subsystem);
}

std::ostream &Logger::warning(const std::string &subsystem)
{
    return log(Logger::Level::WARNING, subsystem);
}

std::ostream &Logger::error(const std::string &subsystem)
{
    return log(Logger::Level::ERROR, subsystem);
}

std::ostream &Logger::critical(const std::string &subsystem)
{
    return log(Logger::Level::CRITICAL, subsystem);
}

}