// Project includes
#include "../../VM/Handler/Opcode80E6Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E6::Opcode80E6(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80E6::_run(VM::Script& script)
            {
                _logger->debug() << "[80E6] [=] void set_exit_grids(int mapId, int elevation, int tileNum, int rotation)" << std::endl;
                auto rotation = script.dataStack()->popInteger();
                auto tile = script.dataStack()->popInteger();
                auto elevation = script.dataStack()->popInteger();
                auto mapId = script.dataStack()->popInteger();
                _logger->debug() << "mapId=" << mapId << "elevation=" << elevation << " tile=" << tile << " rotation=" << rotation << std::endl;
            }
        }
    }
}
