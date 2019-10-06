#include "Opcode80D5Handler.h"
#include "Game/Game.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D5::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80D5] [*] int tile_num_in_direction(int start_tile, int dir, int distance)"
                                        << std::endl;

                auto dataStack = _script->dataStack();

                auto distance = dataStack->popInteger();
                auto dir = dataStack->popInteger();
                auto start_tile = dataStack->popInteger();

                if (dir < 0 || dir > 5 || distance < 0) {
                    //error?
                    dataStack->push(start_tile);
                } else {
                    auto grid = Game::getInstance()->locationState()->hexagonGrid();
                    auto hex = grid->hexInDirection(grid->at(start_tile), dir, distance);
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
