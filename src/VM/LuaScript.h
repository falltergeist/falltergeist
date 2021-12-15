#pragma once

#include <string>
extern "C" {
    #include "lua.h"
}
#include "../State/State.h"

namespace Falltergeist {
    namespace VM {
        class LuaScript {
        public:
            LuaScript(const std::string& filename, State::State* state);
            ~LuaScript();
            void execute();

        private:
            lua_State *luaState;
            State::State* state;
        };
    }
}
