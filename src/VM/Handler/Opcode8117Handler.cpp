// Project includes
#include "../../VM/Handler/Opcode8117Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8117::Opcode8117(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8117::_run()
            {
                logger->debug()
                    << "[8117] [=] int rm_mult_objs_from_inven(void* who, void* obj, int count)"
                    << std::endl
                ;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popObject();
                dataStack->push(0);
            }
        }
    }
}


