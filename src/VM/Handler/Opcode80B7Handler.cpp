// Project includes
#include "../../VM/Handler/Opcode80B7Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ObjectFactory.h"
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
            Opcode80B7::Opcode80B7(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B7::_run() {
                logger->debug()
                        << "[80B7] [+] GameObject* create_object_sid(int PID, int position, int elevation, int SID)"
                        << std::endl;
                auto dataStack = _script->dataStack();
                auto SID = dataStack->popInteger();
                auto elevation = dataStack->popInteger();
                auto position = dataStack->popInteger();
                auto PID = dataStack->popInteger();
                auto object = Game::Game::getInstance()->locationState()->addObject(PID, position, elevation);
                if (SID > 0) {
                    auto intFile = ResourceManager::getInstance()->intFileType(SID);
                    if (intFile) {
                        object->setScript(new VM::Script(intFile, object));
                    }
                }
                if (object->script()) {
                    object->script()->initialize();
                }
                _script->dataStack()->push(object);
            }
        }
    }
}
