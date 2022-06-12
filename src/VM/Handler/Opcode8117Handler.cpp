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
            Opcode8117::Opcode8117(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8117::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8117] [=] int rm_mult_objs_from_inven(void* who, void* obj, int count)"
                    << std::endl
                ;
                auto dataStack = script.dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popObject();
                dataStack->push(0);
            }
        }
    }
}


