// Project includes
#include "../../VM/Handler/Opcode80E5Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E5::Opcode80E5(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80E5::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80E5] [=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)"
                    << std::endl
                ;
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
            }
        }
    }
}
