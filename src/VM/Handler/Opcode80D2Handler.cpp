// Project includes
#include "../../VM/Handler/Opcode80D2Handler.h"
#include "../../Game/Game.h"
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
            Opcode80D2::Opcode80D2(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D2::_run(VM::Script& script)
            {
                _logger->debug() << "[80D2] [=] int tile_distance(int tile1, int tile2)" << std::endl;
                auto tile1 = script.dataStack()->popInteger();
                auto tile2 = script.dataStack()->popInteger();
                if (tile1 < 0 || tile1 >= 200 * 200 || tile2 < 0 || tile2 >= 200 * 200) {
                    script.dataStack()->push(9999);
                } else {
                    auto grid = Game::Game::getInstance()->locationState()->hexagonGrid();
                    auto dist = grid->distance(grid->at(tile1).get(), grid->at(tile2).get());
                    script.dataStack()->push(dist);
                }
            }
        }
    }
}
