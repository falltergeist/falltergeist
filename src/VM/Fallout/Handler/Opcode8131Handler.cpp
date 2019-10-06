#include "Opcode8131Handler.h"
#include "Game/ContainerItemObject.h"
#include "Game/DoorSceneryObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8131::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[8131] [+] void obj_open(GameDoorSceneryObject* object) " << std::endl;
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


