#pragma once

#include "../Lua/IModuleLoader.h"
#include "../VFS/VFS.h"

namespace Falltergeist {
    namespace Lua {
        class VFSModuleLoader final : public IModuleLoader {
        public:
            VFSModuleLoader(VFS::VFS& vfs);

            bool loadModule(const std::string& name, lua_State* L) override;

        private:
            VFS::VFS& _vfs;
        };
    }
}
