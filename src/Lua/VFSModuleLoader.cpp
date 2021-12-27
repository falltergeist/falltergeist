#include "../Lua/VFSModuleLoader.h"
#include "../Exception.h"

extern "C" {
    #include "lauxlib.h"
}

namespace Falltergeist {
    namespace Lua {
        VFSModuleLoader::VFSModuleLoader(VFS::VFS& vfs) : _vfs(vfs) {
        }

        bool VFSModuleLoader::loadModule(const std::string& name, lua_State* L) {
            const std::string&& pathToFile = "data/scripts/" + name + ".lua";
            if (_vfs.exists(pathToFile)) {
                return false;
            }

            auto file = _vfs.open(pathToFile);
            if (!file || !file->isOpened()) {
                return false;
            }

            std::string sourceCode;
            sourceCode.resize(file->size());
            file->read(sourceCode.data(), file->size());
            //sourceCode[file->size()] = 0;

            _vfs.close(file);

            if(luaL_loadbuffer(L, sourceCode.c_str(), sourceCode.size(), name.c_str()) != LUA_OK) {
                throw Exception(std::string("Could not load buffer: ") + lua_tostring(L, -1));
            }

            return true;
        }
    }
}
