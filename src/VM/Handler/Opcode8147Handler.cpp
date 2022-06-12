// Project includes
#include "../../VM/Handler/Opcode8147Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8147::Opcode8147(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8147::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8147] [=] void move_obj_inven_to_obj(void* srcObj, void* destObj)"
                    << std::endl
                ;
                script.dataStack()->popObject();
                script.dataStack()->popObject();
            }
        }
    }
}

