// Project includes
#include "../../VM/Handler/Opcode9001Handler.h"
#include "../../Format/Int/File.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode9001::Opcode9001(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode9001::_run(VM::Script& script)
            {
                unsigned int data = script.intFile()->readValue();
                unsigned short nextOpcode = script.intFile()->readOpcode();

                // Skip 4 readed bytes
                script.setProgramCounter(script.programCounter() + 4);

                switch (nextOpcode) {
                    case 0x8014: // get exported var value
                    case 0x8015: // set exported var value
                    case 0x8016: // export var
                    {
                        script.dataStack()->push(script.intFile()->identifiers().at(data));
                        break;
                    }
                    default: {
                        script.dataStack()->push(script.intFile()->strings().at(data));
                        break;
                    }
                }

                auto value = script.dataStack()->top();
                _logger->debug()
                    << "[9001] [*] push_d string" << std::endl
                    << "     type: " << value.typeName() << std::endl
                    << "    value: " << value.toString() << std::endl
                ;
            }
        }

    }
}
