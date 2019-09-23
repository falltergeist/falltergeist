#include "../../VM/Handler/Opcode80FFHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FF::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT")
                        << "[80FF] [*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)"
                        << std::endl;
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto critter = static_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                if (!critter) {
                    _error("critter_attempt_placement - invalid critter pointer");
                }
                auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::getInstance()->locationState()->moveObjectToHexagon(critter, hexagon);
                critter->setElevation(elevation);
                _script->dataStack()->push(1);
            }
        }
    }
}


