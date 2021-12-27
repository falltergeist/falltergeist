#pragma once

#include <string>
extern "C" {
    #include "lua.h"
}
namespace Falltergeist {
    namespace Lua {
        class IModuleLoader {
        public:
            virtual ~IModuleLoader() = default;

            /**
             * Handles require('module_name') calls in LUA script. Returns true on success
             */
            virtual bool loadModule(const std::string& name, lua_State* L) = 0;
        };
    }
}
