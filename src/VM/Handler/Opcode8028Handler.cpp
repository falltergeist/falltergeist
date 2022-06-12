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
            Opcode8028::Opcode8028(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8028::_run(VM::Script& script)
            {
                _logger->debug() << "[8028] [?] int lookup_string_proc(string)" << std::endl;
                std::string name = script.dataStack()->popString();
                script.dataStack()->push((int) script.intFile()->procedure(name)->bodyOffset());
            }
        }
    }
}
