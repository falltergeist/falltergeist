#pragma once

#include <string>

namespace Falltergeist {
    namespace VFS {
        class IDriver {
        public:
            virtual ~IDriver() = default;

            virtual bool exists(const std::string& path) = 0;
        };
    }
}