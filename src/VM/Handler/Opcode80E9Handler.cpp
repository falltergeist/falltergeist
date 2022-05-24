// Project includes
#include "../../VM/Handler/Opcode80E9Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E9::Opcode80E9(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E9::_run()
            {
                logger->debug() << "[80E9] [*] void set_light_level(int level)" << std::endl;
                auto level = _script->dataStack()->popInteger();

                if (level > 100 || level < 0) {
                    _warning("set_light_level: level should be 0-100");
                    return;
                }

                unsigned int light = 0;
                if (level < 50) {
                    light = 0x4000 + level * 0x6000 / 100;
                } else if (level == 50) {
                    light = 0xA000;
                } else {
                    light = 0xA000 + level * 0x6000 / 100;
                }

                Game::Game::getInstance()->locationState()->setLightLevel(light);
            }
        }
    }
}
