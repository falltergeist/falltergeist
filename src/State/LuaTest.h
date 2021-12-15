#pragma once

#include "../State/State.h"
#include "../VM/LuaScript.h"

namespace Falltergeist {
    namespace State {
        class LuaTest final : public State {
        public:
            LuaTest();
            ~LuaTest() override = default;

            void think(const float &deltaTime) override;
            void init() override;

        private:
            std::unique_ptr<VM::LuaScript> luaScript;
        };
    }
}
