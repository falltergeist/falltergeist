#pragma once

#include <string>
extern "C" {
    #include "lua.h"
}
#include "../State/State.h"
#include "../VFS/IFile.h"
#include "../Lua/IModuleLoader.h"

namespace Falltergeist {
    namespace VM {
        class LuaScript {
        public:
            LuaScript(const std::string& script, State::State* state);

            ~LuaScript();

            void execute();

        private:
            lua_State *luaState;

            State::State* state;

            std::vector<std::unique_ptr<Lua::IModuleLoader>> _moduleLoaders;
        };
    }
}
