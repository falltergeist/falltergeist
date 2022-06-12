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
                OpcodeHandler() = default;

                virtual ~OpcodeHandler() = default;

                void run(VM::Script& script);

            protected:
                virtual void _run(VM::Script& script);

                // print warning message to log
                void _warning(VM::Script& script, const std::string &message);

                // prints error message to logs and throws VM::ErrorException
                void _error(const std::string& message);
        };
    }
}
