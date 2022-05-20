#include "../../VM/Handler/Opcode80B6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/DudeObject.h"
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
            Opcode80B6::Opcode80B6(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B6::_run()
            {
                logger->debug() << "[80B6] [+] int move_to(GameObject* object, int position, int elevation)"
                                        << std::endl;
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("move_to: object is NULL");
                }
                auto hexagon = Game::Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::Game::getInstance()->locationState()->moveObjectToHexagon(object, hexagon);
                object->setElevation(elevation);
                if (object == Game::Game::getInstance()->player().get()) {
                    Game::Game::getInstance()->locationState()->centerCameraAtHexagon(object->hexagon());
                }
                _script->dataStack()->push(0);
            }
        }
    }
}
