#include "Exception.h"
#include "Game/Game.h"
#include "State/Location.h"
#include "Opcode8014.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8014::applyTo(std::shared_ptr<IContext> context)
            {
                //auto &debug = Logger::debug("SCRIPT");
                //debug << "[8014] [+] value = op_fetch_external(name)" << std::endl;
                auto game = Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                std::string name;
                auto nameValue = context->dataStack()->pop();
                switch (nameValue->type()) {
                    case IStackValue::Type::INTEGER:
                        name = context->getIdentifierByIndex((unsigned int) nameValue->asInteger());
                        break;
                    case IStackValue::Type::STRING: {
                        name = nameValue->asString();
                        break;
                    }
                    default:
                        throw Exception("op_fetch_external - invalid argument type: ");
                }
                //debug << " name = " << name;
                if (EVARS->find(name) == EVARS->end()) {
                    throw Exception(std::string() + "op_fetch_external: exported variable \"" + name + "\" not found.");
                }
                auto value = EVARS->at(name);
                //debug << ", type = " << value.typeName() << ", value = " << value.toString() << std::endl;
                context->dataStack()->push(value);
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
