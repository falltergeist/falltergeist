#include "../../VM/Handler/Opcode80D2Handler.h"
#include "../../Game/Game.h"
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
            Opcode80D2::Opcode80D2(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80D2::_run()
            {
                logger->debug() << "[80D2] [=] int tile_distance(int tile1, int tile2)" << std::endl;
                auto tile1 = _script->dataStack()->popInteger();
                auto tile2 = _script->dataStack()->popInteger();
                if (tile1 < 0 || tile1 >= 200 * 200 || tile2 < 0 || tile2 >= 200 * 200) {
                    _script->dataStack()->push(9999);
                } else {
                    auto grid = Game::Game::getInstance()->locationState()->hexagonGrid();
                    auto dist = grid->distance(grid->at(tile1), grid->at(tile2));
                    _script->dataStack()->push(dist);
                }
            }
        }
    }
}
