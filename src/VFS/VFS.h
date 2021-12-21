#pragma once

#include "../VFS/IDriver.h"
#include <map>
#include <memory>
#include <string>

namespace Falltergeist {
    namespace VFS {
        class VFS final {
        public:
            void addMount(const std::string& mountPath, std::unique_ptr<IDriver>&& driver);

            void addMount(const std::string& mountPath, std::unique_ptr<IDriver>& driver);

            bool exists(const std::string& pathToFile);

        private:
            std::multimap<std::string, std::unique_ptr<IDriver>> _mounts;
        };
    }
}
