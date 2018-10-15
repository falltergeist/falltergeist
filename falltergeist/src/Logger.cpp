/*
 * Copyright 2012-2018 Falltergeist Developers.
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
#include <sstream>

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
        if (level < _level) {
            return nullstream;
        }
        std::string subsystemMsg = " ";
        if (subsystem.size() > 0) {
            subsystemMsg = " [" + subsystem + "] ";
        }
        return std::cout << levelString(level) << subsystemMsg << std::dec;
    }

    // Initial level; overridden with config option with default level LOG_INFO
    Logger::Level Logger::_level = Logger::Level::LOG_DEBUG;
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
                case Logger::Level::LOG_DEBUG:
                    return "[DEBUG]";
                case Logger::Level::LOG_INFO:
                    return "\x1b[32m[INFO]\x1b[0m";
                case Logger::Level::LOG_WARNING:
                    return "\x1b[33m[WARNING]\x1b[0m";
                case Logger::Level::LOG_ERROR:
                    return "\x1b[31m[ERROR]\x1b[0m";
                case Logger::Level::LOG_CRITICAL:
                    return "\x1b[31;1m[CRITICAL]\x1b[0m";
            }
        }
        else
        {
            switch (level)
            {
                case Logger::Level::LOG_DEBUG:
                    return "[DEBUG]";
                case Logger::Level::LOG_INFO:
                    return "[INFO]";
                case Logger::Level::LOG_WARNING:
                    return "[WARNING]";
                case Logger::Level::LOG_ERROR:
                    return "[ERROR]";
                case Logger::Level::LOG_CRITICAL:
                    return "[CRITICAL]";
            };
        }

        return "[UNKOWN]";
    }

    std::ostream &Logger::debug(const std::string &subsystem)
    {
        return log(Logger::Level::LOG_DEBUG, subsystem);
    }

    std::ostream &Logger::info(const std::string &subsystem)
    {
        return log(Logger::Level::LOG_INFO, subsystem);
    }

    std::ostream &Logger::warning(const std::string &subsystem)
    {
        return log(Logger::Level::LOG_WARNING, subsystem);
    }

    std::ostream &Logger::error(const std::string &subsystem)
    {
        return log(Logger::Level::LOG_ERROR, subsystem);
    }

    std::ostream &Logger::critical(const std::string &subsystem)
    {
        return log(Logger::Level::LOG_CRITICAL, subsystem);
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
            lvl = Level::LOG_DEBUG;
        }
        else if (level == "info")
        {
            lvl = Level::LOG_INFO;
        }
        else if (level == "warning")
        {
            lvl = Level::LOG_WARNING;
        }
        else if (level == "error")
        {
            lvl = Level::LOG_ERROR;
        }
        else if (level == "critical")
        {
            lvl = Level::LOG_CRITICAL;
        }
        else
        {
            warning() << "Unknown level " << level << " ignored";
            return;
        }

        setLevel(lvl);

    }

    std::ostream& operator <<(std::ostream& lhs, const Point& rhs)
    {
        lhs << "(" << rhs.x() << "," << rhs.y() << ")";
        return lhs;
    }

    std::ostream& operator <<(std::ostream& lhs, const Size& rhs)
    {
        lhs << rhs.width() << "x" << rhs.height();
        return lhs;
    }

    std::string to_string(const Point& point)
    {
        std::ostringstream sstr;
        sstr << point;
        return sstr.str();
    }

    std::string to_string(const Size& size)
    {
        std::ostringstream sstr;
        sstr << size;
        return sstr.str();
    }
}
