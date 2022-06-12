// Project includes
#include "../../VM/Handler/Opcode80FFHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
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
            Opcode80FF::Opcode80FF(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80FF::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80FF] [*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)"
                    << std::endl
                ;
                auto elevation = script.dataStack()->popInteger();
                auto position = script.dataStack()->popInteger();
                auto critter = static_cast<Game::CritterObject *>(script.dataStack()->popObject());
                if (!critter) {
                    _error("critter_attempt_placement - invalid critter pointer");
                }
                auto& hexagon = Game::Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::Game::getInstance()->locationState()->moveObjectToHexagon(critter, hexagon.get());
                critter->setElevation(elevation);
                script.dataStack()->push(1);
            }
        }
    }
}


