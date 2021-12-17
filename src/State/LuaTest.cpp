#include "../State/LuaTest.h"
#include "../UI/TextArea.h"
#include "../Game/Game.h"
#include "../Input/Mouse.h"
#include <filesystem>

namespace Falltergeist::State {
        LuaTest::LuaTest() : State() {
            // TODO use VFS
            luaScript = std::make_unique<VM::LuaScript>(std::string(std::filesystem::current_path()) + "/scripts/main.lua", this);
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
            Game::Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::BIG_ARROW);

            State::init();

            luaScript->execute();
        }
    }
