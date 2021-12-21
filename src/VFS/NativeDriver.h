#pragma once

#include "../VFS/IDriver.h"

namespace Falltergeist {
    namespace VFS {
        class NativeDriver final : public IDriver {
        public:
            NativeDriver(const std::string& basePath);

            bool exists(const std::string &path) override;
        private:
            std::string _basePath;
        };
    }
}
