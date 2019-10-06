#include "Game/DudeObject.h"
#include "VM/Fallout/Handler/Opcode80A1.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode80A1::applyTo(std::shared_ptr<IContext>& context)
                {
                    auto points = context->dataStack()->pop()->asInteger();
                    context->player()->setExperience(context->player()->experience() + points);
                }

                int Opcode80A1::number()
                {
                    return 0x80A1;
                }

                std::string Opcode80A1::name()
                {
                    return "void give_exp_points(int points)";
                }

                std::string Opcode80A1::notes()
                {
                    return "implemented";
                }
            }
        }
    }
}
