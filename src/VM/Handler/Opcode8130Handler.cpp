// Project includes
#include "../../VM/Handler/Opcode8130Handler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DoorSceneryObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8130::Opcode8130(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8130::_run(VM::Script& script)
            {
                _logger->debug() << "[8130] [+] int obj_is_open(GameObject* object) " << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("obj_is_open: object is NULL");
                }
                // @TODO: need some refactoring to get rid of this ugly if-elses
                if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                    script.dataStack()->push(door->opened());
                } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                    script.dataStack()->push(container->opened());
                } else {
                    _error("obj_is_open: object is not openable type!");
                }
            }
        }
    }
}


