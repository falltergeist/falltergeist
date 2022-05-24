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
        OpcodeHandler::OpcodeHandler(VM::Script *script) : _script(script)
        {
            _offset = script->programCounter();
        }

        OpcodeHandler::~OpcodeHandler()
        {
        }

        void OpcodeHandler::run()
        {
            _script->setProgramCounter(_script->programCounter() + 2);
            _run();
        }

        void OpcodeHandler::_run()
        {
        }

        void OpcodeHandler::_warning(const std::string &message)
        {
            Logger::warning("SCRIPT") << message << " at " << _script->script()->filename() << ":0x" << std::hex
                                      << _offset << std::endl;
        }

        void OpcodeHandler::_error(const std::string &message)
        {
            throw ErrorException(message);
        }
    }
}
