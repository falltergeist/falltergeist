#include "../../VM/Handler/Opcode80D2Handler.h"
#include "../../Game/Game.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D2::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80D2] [=] int tile_distance(int tile1, int tile2)" << std::endl;
                auto tile1 = _script->dataStack()->popInteger();
                auto tile2 = _script->dataStack()->popInteger();
                if (tile1 < 0 || tile1 >= 200 * 200 || tile2 < 0 || tile2 >= 200 * 200) {
                    _script->dataStack()->push(9999);
                } else {
                    auto grid = Game::getInstance()->locationState()->hexagonGrid();
                    auto dist = grid->distance(grid->at(tile1), grid->at(tile2));
                    _script->dataStack()->push(dist);
                }
            }
        }
    }
}
