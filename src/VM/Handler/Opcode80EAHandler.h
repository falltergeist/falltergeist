#pragma once

// Project includes
#include "../../Game/Time.h"
#include "../../ILogger.h"
#include "../../VM/OpcodeHandler.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode80EA final : public OpcodeHandler {
            public:
                Opcode80EA(std::shared_ptr<ILogger> logger, std::shared_ptr<Game::Time> time);

            private:
                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<Game::Time> _time;

                void _run(VM::Script& script) override;
            };
        }
    }
}
