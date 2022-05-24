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
            Opcode80E6::Opcode80E6(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E6::_run()
            {
                logger->debug() << "[80E6] [=] void set_exit_grids(int mapId, int elevation, int tileNum, int rotation)" << std::endl;
                auto rotation = _script->dataStack()->popInteger();
                auto tile = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto mapId = _script->dataStack()->popInteger();
                logger->debug() << "mapId=" << mapId << "elevation=" << elevation << " tile=" << tile << " rotation=" << rotation << std::endl;
            }
        }
    }
}
