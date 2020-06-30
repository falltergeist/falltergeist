#include "../../VM/Handler/Opcode80D3Handler.h"
#include "../../Game/Game.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D3::Opcode80D3(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80D3::_run()
            {
                logger->debug() << "[80D3] int tile_distance_objs(void* p2, void* p1)" << std::endl;
                auto obj1 = _script->dataStack()->popObject();
                auto obj2 = _script->dataStack()->popObject();
                int distance = Game::Game::getInstance()->locationState()->hexagonGrid()->distance(obj1->hexagon(),
                                                                                             obj2->hexagon());
                _script->dataStack()->push(distance);
            }
        }
    }
}
