// Project includes
#include "../../VM/Handler/Opcode8028Handler.h"
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
            Opcode8028::Opcode8028(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8028::_run()
            {
                logger->debug() << "[8028] [?] int lookup_string_proc(string)" << std::endl;
                std::string name = _script->dataStack()->popString();
                _script->dataStack()->push((int) _script->script()->procedure(name)->bodyOffset());
            }
        }
    }
}
