// Project includes
#include "../../VM/Handler/Opcode8100Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ObjectFactory.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8100::Opcode8100(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8100::_run(VM::Script& script)
            {
                _logger->debug() << "[8100] [+] int obj_pid(void* obj)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    script.dataStack()->push(0);
                } else {
                    script.dataStack()->push(object->PID());
                }
            }
        }
    }
}


