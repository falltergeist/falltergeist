#pragma once

#include <exception>
#include <stdexcept>
#include <string>

namespace Falltergeist
{
    class Exception : public std::exception
    {
        public:
            explicit Exception(const char* message);
            explicit Exception(const std::string& message);
            const char* what() const noexcept override;

        private:
            std::runtime_error _error;
    };
}
