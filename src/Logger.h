#pragma once

// Project includes
#include "Graphics/Size.h"
#include "Graphics/Point.h"
#include "ILogger.h"

// Third-party includes

// stdlib
#include <iosfwd>
#include <iostream>

namespace Falltergeist
{
    class Logger final : public ILogger
    {
        public:
            enum class Level
            {
                LOG_DEBUG     = 0,
                LOG_INFO      = 1,
                LOG_WARNING   = 2,
                LOG_ERROR     = 3,
                LOG_CRITICAL  = 4,
                LOG_NONE      = 5
            };

            Logger() = default;
            Logger(const std::string& channel);

            static Level level();
            static void setLevel(Level level);
            static void setLevel(const std::string &level);
            static const char *levelString(Level level);

            static const bool colorsSupported;
            static void useColors(bool useColors);

            static std::ostream &log(Level level, const std::string &subsystem = "");
            static std::ostream &debug(const std::string &subsystem = "");
            static std::ostream &info(const std::string &subsystem = "");
            static std::ostream &warning(const std::string &subsystem = "");
            static std::ostream &error(const std::string &subsystem = "");
            static std::ostream &critical(const std::string &subsystem = "");

            std::ostream& debug() override;
            std::ostream& info() override;
            std::ostream& warning() override;
            std::ostream& error() override;
            std::ostream& critical() override;

        private:
            static Level _level;
            static bool _useColors;
            std::string _channel;
    };

    // Support for custom types in output streams:
    std::ostream& operator<<(std::ostream& lhs, const Graphics::Point& rhs);
    std::ostream& operator<<(std::ostream& lhs, const Graphics::Size& rhs);

    std::string to_string(const Graphics::Point& point);
    std::string to_string(const Graphics::Size& size);
}
