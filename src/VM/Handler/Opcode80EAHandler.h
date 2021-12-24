#pragma once

#include "../../Game/Time.h"
#include "../../ILogger.h"
#include "../../VM/OpcodeHandler.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode80EA : public OpcodeHandler {
            public:
                Opcode80EA(VM::Script* script, std::shared_ptr<ILogger> logger, std::shared_ptr<Game::Time> time);

            private:
                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<Game::Time> _time;

                void _run() override;
            };
        }
    }
}
