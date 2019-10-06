#include "Opcode80D3Handler.h"
#include "Game/Game.h"
#include "PathFinding/HexagonGrid.h"
#include "State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D3::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80D3] int tile_distance_objs(void* p2, void* p1)" << std::endl;
                auto obj1 = _script->dataStack()->popObject();
                auto obj2 = _script->dataStack()->popObject();
                int distance = Game::getInstance()->locationState()->hexagonGrid()->distance(obj1->hexagon(),
                                                                                             obj2->hexagon());
                _script->dataStack()->push(distance);
            }
        }
    }
}
