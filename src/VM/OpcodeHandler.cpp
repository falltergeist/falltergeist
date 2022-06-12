// Project includes
#include "../Format/Int/File.h"
#include "../Logger.h"
#include "../VM/ErrorException.h"
#include "../VM/OpcodeHandler.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        void OpcodeHandler::run(VM::Script& script)
        {
            script.setProgramCounter(script.programCounter() + 2);
            _run(script);
        }

        void OpcodeHandler::_run(VM::Script& script)
        {
        }

        void OpcodeHandler::_warning(VM::Script& script, const std::string &message)
        {
            Logger::warning("SCRIPT") << message << " at " << script.intFile()->filename() << ":0x" << std::hex
                                      << script.programCounter() << std::endl;
        }

        void OpcodeHandler::_error(const std::string &message)
        {
            throw ErrorException(message);
        }
    }
}
