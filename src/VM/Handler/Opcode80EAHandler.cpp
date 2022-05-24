// Project includes
#include "../../VM/Handler/Opcode80EAHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode80EA::Opcode80EA(VM::Script* script, std::shared_ptr<ILogger> logger, std::shared_ptr<Game::Time> time)
                : OpcodeHandler(script), _logger(logger), _time(time) {
            }

            void Opcode80EA::_run() {
                _logger->debug() << "[80EA] [*] int gameTime()" << std::endl;
                _script->dataStack()->push((int)_time->ticks());
            }
        }
    }
}
