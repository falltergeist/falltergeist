#include "Game/Game.h"
#include "State/Location.h"
#include "Opcode8016.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8016::applyTo(std::shared_ptr<IContext> context)
            {
                auto name = context->dataStack()->pop()->asString();
                auto EVARS = Game::getInstance()->locationState()->EVARS();
                if (EVARS->find(name) == EVARS->end()) {
                    EVARS->insert(std::make_pair(name, std::make_shared<StackValue>((int)0)));
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
