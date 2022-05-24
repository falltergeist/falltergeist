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
            Opcode9001::Opcode9001(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode9001::_run()
            {
                unsigned int data = _script->script()->readValue();
                unsigned short nextOpcode = _script->script()->readOpcode();

                // Skip 4 readed bytes
                _script->setProgramCounter(_script->programCounter() + 4);

                switch (nextOpcode) {
                    case 0x8014: // get exported var value
                    case 0x8015: // set exported var value
                    case 0x8016: // export var
                    {
                        _script->dataStack()->push(_script->script()->identifiers().at(data));
                        break;
                    }
                    default: {
                        _script->dataStack()->push(_script->script()->strings().at(data));
                        break;
                    }
                }

                auto value = _script->dataStack()->top();
                logger->debug()
                    << "[9001] [*] push_d string" << std::endl
                    << "     type: " << value.typeName() << std::endl
                    << "    value: " << value.toString() << std::endl
                ;
            }
        }

    }
}
