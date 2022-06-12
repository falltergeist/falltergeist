// Project includes
#include "../../VM/Handler/Opcode80DAHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DA::Opcode80DA(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80DA::_run(VM::Script& script)
            {
                _logger->debug() << "[80DA] [=] void wield_obj_critter(void* who, void* obj)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->popObject();
            }
        }
    }
}
