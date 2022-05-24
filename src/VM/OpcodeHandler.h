#pragma once

// Project includes

// Third-party includes

// stdlib
#include <memory>
#include <string>

namespace Falltergeist
{
    namespace VM
    {
        class Script;

        class OpcodeHandler
        {
            public:
                OpcodeHandler(VM::Script *script);

                virtual ~OpcodeHandler();

                void run();

            protected:
                VM::Script *_script;
                unsigned int _offset;

                virtual void _run();

                // print warning message to log
                void _warning(const std::string &message);

                // prints error message to logs and throws VM::ErrorException
                void _error(const std::string &message);
        };
    }
}
