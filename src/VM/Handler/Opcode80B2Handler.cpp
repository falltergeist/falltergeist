// Project includes
#include "../../VM/Handler/Opcode80B2Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B2::Opcode80B2(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80B2::_run(VM::Script& script)
            {
                _logger->debug()
                        << "[80B2] [=] void mark_area_known(int AREA_MARK_TYPE, int AreaNum, int MARK_STATE);"
                        << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
            }
        }
    }
}
