// Project includes
#include "../../VM/Handler/Opcode8005.h"
#include "../../Format/Int/File.h"
#include "../../Format/Int/Procedure.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8005::Opcode8005(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8005::_run()
            {
                auto functionIndex = _script->dataStack()->popInteger();
                // @TODO: pass arguments and call external procedures
                /*auto argumentCount = _script->dataStack()->popInteger();
                std::vector<int> args;
                for (int i = 0; i < argumentCount; i++)
                {
                    args.push_back(_script->dataStack()->popInteger());
                }*/
                _script->setProgramCounter(_script->script()->procedures().at(functionIndex).bodyOffset());
                logger->debug()
                    << "[8005] [*] op_call(0x" << std::hex << functionIndex << ") = 0x"
                    << _script->programCounter() << std::endl
                ;
            }
        }
    }
}
