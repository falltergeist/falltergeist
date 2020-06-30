#include "../../VM/Handler/Opcode814AHandler.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode814A::Opcode814A(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode814A::_run()
            {
                // @TODO
                logger->debug() << "[814A] [*] int art_anim(int fid)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->push(0);
            }
        }
    }
}

