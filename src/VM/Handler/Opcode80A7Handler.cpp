// Project includes
#include "../../VM/Handler/Opcode80A7Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A7::Opcode80A7(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A7::_run(VM::Script& script)
            {
                _logger->debug()
                        << "[80A7] [+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)"
                        << std::endl;
                auto PID = script.dataStack()->popInteger();
                auto elevation = script.dataStack()->popInteger();
                auto position = script.dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                Game::Object *found = nullptr;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
                    if (object->PID() == PID && object->elevation() == elevation) {
                        found = object;
                        break;
                    }
                }
                script.dataStack()->push(found);
            }
        }
    }
}


