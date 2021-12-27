#include "../State/LuaState.h"
#include "../Game/Game.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Exception.h"

namespace Falltergeist {
    namespace State {

        LuaState::LuaState(const std::string& sceneName) {
            auto& vfs = ResourceManager::getInstance()->vfs();
            auto&& scriptFile = "data/scripts/scenes/" + sceneName + ".lua";
            auto file = vfs.open(scriptFile, VFS::IFile::OpenMode::Read);
            if (!file || !file->isOpened()) {
                throw Exception("Could not open script file: " + scriptFile);
            }

            std::string script;
            script.resize(file->size() + 1);
            file->read(script.data(), file->size());
            script[file->size()] = 0;
            vfs.close(file);

            _luaScript = std::make_unique<VM::LuaScript>(script, this);
        }

        void LuaState::think(const float& deltaTime) {
            State::think(deltaTime);
        }

        void LuaState::init() {
            if (_initialized) {
                return;
            }

            setModal(true);
            setFullscreen(true);
            Game::Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::BIG_ARROW);

            State::init();

            _luaScript->execute();
        }
    }
}
