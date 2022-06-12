// Project includes
#include "../../VM/Handler/Opcode80D3Handler.h"
#include "../../Game/Game.h"
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
            Opcode80D3::Opcode80D3(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D3::_run(VM::Script& script)
            {
                _logger->debug() << "[80D3] int tile_distance_objs(void* p2, void* p1)" << std::endl;
                auto obj1 = script.dataStack()->popObject();
                auto obj2 = script.dataStack()->popObject();
                int distance = Game::Game::getInstance()->locationState()->hexagonGrid()->distance(obj1->hexagon(),
                                                                                             obj2->hexagon());
                script.dataStack()->push(distance);
            }
        }
    }
}
