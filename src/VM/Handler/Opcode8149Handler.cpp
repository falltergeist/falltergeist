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
            Opcode8149::Opcode8149(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8149::_run(VM::Script& script)
            {
                // TODO: should it return FID of current animation?
                _logger->debug() << "[8149] [+] int obj_art_fid(void* obj)" << std::endl;
                auto object = script.dataStack()->popObject();
                script.dataStack()->push(object->FID());
            }
        }
    }
}
