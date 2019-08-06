#include "../../VM/Handler/Opcode8014.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8014::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto &debug = Logger::debug("SCRIPT");
                debug << "[8014] [+] value = op_fetch_external(name)" << std::endl;
                auto game = Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                std::string name;
                auto nameValue = _script->dataStack()->pop();
                switch (nameValue->type()) {
                    case IFalloutValue::Type::INTEGER:
                        name = _script->script()->identifiers().at((unsigned int) nameValue->asInteger());
                        break;
                    case IFalloutValue::Type::STRING: {
                        name = nameValue->asString();
                        break;
                    }
                    default:
                        _error(std::string("op_fetch_external - invalid argument type: ")); // + nameValue.typeName());
                }
                debug << " name = " << name;
                if (EVARS->find(name) == EVARS->end()) {
                    _error(std::string() + "op_fetch_external: exported variable \"" + name + "\" not found.");
                }
                auto value = EVARS->at(name);
                //debug << ", type = " << value.typeName() << ", value = " << value.toString() << std::endl;
                _script->dataStack()->push(value);
            }

            int Opcode8014::number()
            {
                return 0x8014;
            }

            std::string Opcode8014::name()
            {
                return "mixed op_fetch_external(int|string name)";
            }

            std::string Opcode8014::notes()
            {
                return "";
            }
        }
    }
}
