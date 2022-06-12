// Project includes
#include "../../VM/Handler/Opcode814CHandler.h"
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
            Opcode814C::Opcode814C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode814C::_run(VM::Script& script)
            {
                _logger->debug() << "[814C] [=] int rotation_to_tile(int srcTile, int destTile)" << std::endl;
                // TODO: error checking
                auto to_index = script.dataStack()->popInteger();
                auto from_index = script.dataStack()->popInteger();
                auto grid = Game::Game::getInstance()->locationState()->hexagonGrid();
                auto& from_hex = grid->at(from_index);
                auto& to_hex = grid->at(to_index);
                unsigned int rotation = from_hex->orientationTo(to_hex.get());
                script.dataStack()->push(rotation);
            }
        }
    }
}

