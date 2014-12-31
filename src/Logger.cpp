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

// C++ standard includes

// Falltergeist includes
#include "Logger.h"

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
    std::string subsystemMsg = " ";
    if (subsystem.size() > 0) subsystemMsg = " [" + subsystem + "] ";
    return std::cout << levelString(level) << subsystemMsg << std::dec;
}

// Initial level; overridden with config option with default level INFO
Logger::Level Logger::_level = Logger::Level::LEVEL_DEBUG;
bool Logger::_useColors = true;

#if defined(__unix__) || defined(__APPLE__)
const bool Logger::colorsSupported = true;
#else // Assume Windows
const bool Logger::colorsSupported = false;
#endif

const char *Logger::levelString(Logger::Level level)
{
    if (_useColors && colorsSupported)
    {
        switch (level)
        {
            case Logger::Level::LEVEL_DEBUG:
                return "[DEBUG]";
            case Logger::Level::LEVEL_INFO:
                return "\x1b[32m[INFO]\x1b[0m";
            case Logger::Level::LEVEL_WARNING:
                return "\x1b[33m[WARNING]\x1b[0m";
            case Logger::Level::LEVEL_ERROR:
                return "\x1b[31m[ERROR]\x1b[0m";
            case Logger::Level::LEVEL_CRITICAL:
                return "\x1b[31;1m[CRITICAL]\x1b[0m";
        }
    }
    else
    {
        switch (level)
        {
            case Logger::Level::LEVEL_DEBUG:
                return "[DEBUG]";
            case Logger::Level::LEVEL_INFO:
                return "[INFO]";
            case Logger::Level::LEVEL_WARNING:
                return "[WARNING]";
            case Logger::Level::LEVEL_ERROR:
                return "[ERROR]";
            case Logger::Level::LEVEL_CRITICAL:
                return "[CRITICAL]";
        };
    }

    return "[UNKOWN]";
}

std::ostream &Logger::debug(const std::string &subsystem)
{
    return log(Logger::Level::LEVEL_DEBUG, subsystem);
}

std::ostream &Logger::info(const std::string &subsystem)
{
    return log(Logger::Level::LEVEL_INFO, subsystem);
}

std::ostream &Logger::warning(const std::string &subsystem)
{
    return log(Logger::Level::LEVEL_WARNING, subsystem);
}

std::ostream &Logger::error(const std::string &subsystem)
{
    return log(Logger::Level::LEVEL_ERROR, subsystem);
}

std::ostream &Logger::critical(const std::string &subsystem)
{
    return log(Logger::Level::LEVEL_CRITICAL, subsystem);
}

void Logger::useColors(bool useColors)
{
    _useColors = useColors;
}

void Logger::setLevel(const std::string &level)
{
    Logger::Level lvl;

    if (level == "debug")
    {
        lvl = Level::LEVEL_DEBUG;
    }
    else if (level == "info")
    {
        lvl = Level::LEVEL_INFO;
    }
    else if (level == "warning")
    {
        lvl = Level::LEVEL_WARNING;
    }
    else if (level == "error")
    {
        lvl = Level::LEVEL_ERROR;
    }
    else if (level == "critical")
    {
        lvl = Level::LEVEL_CRITICAL;
    }
    else
    {
        warning() << "Unknown level " << level << " ignored";
        return;
    }

    setLevel(lvl);

}
}
