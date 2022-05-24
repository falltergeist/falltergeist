// Project includes
#include "../../VM/Handler/Opcode8149Handler.h"
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
            Opcode8149::Opcode8149(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8149::_run()
            {
                // TODO: should it return FID of current animation?
                logger->debug() << "[8149] [+] int obj_art_fid(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                _script->dataStack()->push(object->FID());
            }
        }
    }
}
