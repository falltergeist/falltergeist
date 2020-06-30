#include "../../VM/Handler/Opcode8131Handler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DoorSceneryObject.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8131::Opcode8131(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8131::_run()
            {
                logger->debug() << "[8131] [+] void obj_open(GameDoorSceneryObject* object) " << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("obj_open: object is NULL");
                }
                // @TODO: need some refactoring to get rid of this ugly if-elses
                if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                    door->setOpened(true);
                } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                    container->setOpened(true);
                } else {
                    _error("obj_open: object is not openable type!");
                }
            }
        }
    }
}


