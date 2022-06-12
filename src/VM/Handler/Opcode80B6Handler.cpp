// Project includes
#include "../../VM/Handler/Opcode80B6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/DudeObject.h"
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
            Opcode80B6::Opcode80B6(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80B6::_run(VM::Script& script)
            {
                _logger->debug() << "[80B6] [+] int move_to(GameObject* object, int position, int elevation)"
                                        << std::endl;
                auto elevation = script.dataStack()->popInteger();
                auto position = script.dataStack()->popInteger();
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("move_to: object is NULL");
                }
                auto& hexagon = Game::Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::Game::getInstance()->locationState()->moveObjectToHexagon(object, hexagon.get());
                object->setElevation(elevation);
                if (object == Game::Game::getInstance()->player().get()) {
                    Game::Game::getInstance()->locationState()->centerCameraAtHexagon(object->hexagon());
                }
                script.dataStack()->push(0);
            }
        }
    }
}
