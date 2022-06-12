// Project includes
#include "../../VM/Handler/Opcode80A8Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A8::Opcode80A8(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A8::_run(VM::Script& script)
            {
                _logger->debug() << "[80A8] [=] void set_map_start(int x, int y, int elev, int rot)" << std::endl;
                auto dataStack = script.dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
            }
        }
    }
}


