#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Handler/Opcode8016.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/FalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8016::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto name = context->dataStack()->pop()->asString();
                auto EVARS = Game::getInstance()->locationState()->EVARS();
                if (EVARS->find(name) == EVARS->end()) {
                    EVARS->insert(std::make_pair(name, std::make_shared<FalloutValue>((int)0)));
                }
            }

            int Opcode8016::number()
            {
                return 0x8016;
            }

            std::string Opcode8016::name()
            {
                return "void op_export_var(string name)";
            }

            std::string Opcode8016::notes()
            {
                return "";
            }
        }
    }
}
