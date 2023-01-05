// Project includes
#include "../../VM/Handler/Opcode8130Handler.h"
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
                if (auto closable = dynamic_cast<Game::IClosable *>(object)) {
                    script.dataStack()->push(!closable->closed());
                } else {
                    _error("obj_is_open: object is not Closable type!");
                }
            }
        }
    }
}


