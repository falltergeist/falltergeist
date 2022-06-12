// Project includes
#include "../../VM/Handler/Opcode80DCHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DC::Opcode80DC(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80DC::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80DC] [=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)"
                    << std::endl
                ;
                script.dataStack()->popObject();
                script.dataStack()->popObject();
                script.dataStack()->push(1);
            }
        }
    }
}


