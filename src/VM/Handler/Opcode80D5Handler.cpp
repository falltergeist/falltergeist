// Project includes
#include "../../VM/Handler/Opcode80D5Handler.h"
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
            Opcode80D5::Opcode80D5(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D5::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80D5] [*] int tile_num_in_direction(int start_tile, int dir, int distance)"
                    << std::endl
                ;

                auto dataStack = script.dataStack();

                auto distance = dataStack->popInteger();
                auto dir = dataStack->popInteger();
                auto start_tile = dataStack->popInteger();

                if (dir < 0 || dir > 5 || distance < 0) {
                    //error?
                    dataStack->push(start_tile);
                } else {
                    auto grid = Game::Game::getInstance()->locationState()->hexagonGrid();
                    auto hex = grid->hexInDirection(grid->at(start_tile).get(), dir, distance);
                    if (hex) {
                        dataStack->push(hex->number());

                    } else {
                        dataStack->push(start_tile);
                    }
                }
            }
        }
    }
}
