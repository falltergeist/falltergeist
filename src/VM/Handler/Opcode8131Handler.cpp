// Project includes
#include "../../VM/Handler/Opcode8131Handler.h"
#include "../../Game/IClosable.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8131::Opcode8131(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {
            }

            void Opcode8131::_run(VM::Script& script)
            {
                _logger->debug() << "[8131] [+] void obj_open(GameDoorSceneryObject* object) " << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("obj_open: object is NULL");
                }
                if (auto closable = dynamic_cast<Game::IClosable *>(object)) {
                    closable->open();
                } else {
                    _error("obj_open: object is not Closable type!");
                }
            }
        }
    }
}


