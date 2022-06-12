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
            Opcode8005::Opcode8005(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8005::_run(VM::Script& script)
            {
                auto functionIndex = script.dataStack()->popInteger();
                // @TODO: pass arguments and call external procedures
                /*auto argumentCount = script.dataStack()->popInteger();
                std::vector<int> args;
                for (int i = 0; i < argumentCount; i++)
                {
                    args.push_back(script.dataStack()->popInteger());
                }*/
                script.setProgramCounter(script.intFile()->procedures().at(functionIndex).bodyOffset());
                _logger->debug()
                    << "[8005] [*] op_call(0x" << std::hex << functionIndex << ") = 0x"
                    << script.programCounter() << std::endl
                ;
            }
        }
    }
}
