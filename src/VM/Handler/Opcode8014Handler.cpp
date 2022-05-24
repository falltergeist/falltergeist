// Project includes
#include "../../VM/Handler/Opcode8014Handler.h"
#include "../../Format/Int/File.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8014::Opcode8014(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8014::_run()
            {
                auto &debug = logger->debug();
                debug << "[8014] [+] value = op_fetch_external(name)" << std::endl;
                auto game = Game::Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                std::string name;
                auto nameValue = _script->dataStack()->pop();
                switch (nameValue.type()) {
                    case StackValue::Type::INTEGER:
                        name = _script->script()->identifiers().at((unsigned int) nameValue.integerValue());
                        break;
                    case StackValue::Type::STRING: {
                        name = nameValue.stringValue();
                        break;
                    }
                    default:
                        _error(std::string("op_fetch_external - invalid argument type: ") + nameValue.typeName());
                }
                debug << " name = " << name;
                if (EVARS->find(name) == EVARS->end()) {
                    _error(std::string() + "op_fetch_external: exported variable \"" + name + "\" not found.");
                }
                auto value = EVARS->at(name);
                debug << ", type = " << value.typeName() << ", value = " << value.toString() << std::endl;
                _script->dataStack()->push(value);
            }

        }
    }
}
