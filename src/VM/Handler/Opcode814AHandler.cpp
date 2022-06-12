// Project includes
#include "../../VM/Handler/Opcode814AHandler.h"
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
            Opcode814A::Opcode814A(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode814A::_run(VM::Script& script)
            {
                // @TODO
                _logger->debug() << "[814A] [*] int art_anim(int fid)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->push(0);
            }
        }
    }
}

