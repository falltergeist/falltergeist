// Project includes
#include "../../VM/Handler/Opcode80BBHandler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ObjectFactory.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
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
            Opcode80BB::Opcode80BB(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80BB::_run()
            {
                logger->debug()
                    << "[80BB] [+] int tile_contains_obj_pid(int position, int elevation, int PID)"
                    << std::endl
                ;
                auto PID = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                int found = 0;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
                    if (object->PID() == PID && object->elevation() == elevation) {
                        found = 1;
                    }
                }
                _script->dataStack()->push(found);
            }
        }
    }
}
