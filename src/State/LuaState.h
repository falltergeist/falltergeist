#pragma once

#include "../State/State.h"
#include "../VM/LuaScript.h"

namespace Falltergeist {
    namespace State {
        class LuaState final : public State {
        public:
            LuaState(const std::string& sceneName);

            ~LuaState() override = default;

            void think(const float &deltaTime) override;

            void init() override;

        private:
            std::unique_ptr<VM::LuaScript> _luaScript;
        };
    }
}
