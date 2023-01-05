// Project includes
#include "../../VM/Handler/Opcode8132Handler.h"
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
            Opcode8132::Opcode8132(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {
            }

            void Opcode8132::_run(VM::Script& script)
            {
                _logger->debug() << "[8132] [+] void obj_close(GameDoorSceneryObject* object) " << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("obj_close: object is NULL");
                }
                if (auto closable = dynamic_cast<Game::IClosable *>(object)) {
                    closable->close();
                } else {
                    _error("obj_close: object is not Closable type!");
                }
            }
        }
    }
}


