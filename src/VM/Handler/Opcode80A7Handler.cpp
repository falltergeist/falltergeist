#include "../../VM/Handler/Opcode80A7Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A7::Opcode80A7(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80A7::_run()
            {
                logger->debug()
                        << "[80A7] [+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)"
                        << std::endl;
                auto PID = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                Game::Object *found = nullptr;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
                    if (object->PID() == PID && object->elevation() == elevation) {
                        found = object;
                        break;
                    }
                }
                _script->dataStack()->push(found);
            }
        }
    }
}


