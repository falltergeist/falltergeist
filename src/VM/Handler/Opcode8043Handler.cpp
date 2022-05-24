// Project includes
#include "../../VM/Handler/Opcode8043Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8043::Opcode8043(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8043::_run()
            {
                logger->debug() << "[8043] [*] op_bwnot" << std::endl;
                auto arg = _script->dataStack()->pop();
                if (!arg.isNumber()) {
                    _error(std::string("op_bwnot: invalid argument type: ") + arg.typeName());
                }
                _script->dataStack()->push(~arg.toInteger());
            }
        }
    }
}
