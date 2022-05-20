#include "../../VM/Handler/Opcode80B2Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B2::Opcode80B2(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B2::_run()
            {
                logger->debug()
                        << "[80B2] [=] void mark_area_known(int AREA_MARK_TYPE, int AreaNum, int MARK_STATE);"
                        << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
            }
        }
    }
}
