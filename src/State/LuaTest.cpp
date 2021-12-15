#include "../State/LuaTest.h"
#include "../UI/TextArea.h"

namespace Falltergeist {
    namespace State {
        LuaTest::LuaTest() : State() {
            luaScript = std::make_unique<VM::LuaScript>("../scripts/main.lua", this);
        }

        void LuaTest::think(const float &deltaTime) {
            State::think(deltaTime);
        }

        void LuaTest::init() {
            if (_initialized) {
                return;
            }

            setModal(true);
            setFullscreen(true);

            State::init();

            luaScript->execute();
        }
    }
}
