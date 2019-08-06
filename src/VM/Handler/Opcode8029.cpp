#include "../../VM/Handler/Opcode8029.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8029::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                _script->setDVARBase(static_cast<size_t>(context->returnStack()->pop()->asInteger()));
            }

            int Opcode8029::number()
            {
                return 0x8029;
            }

            std::string Opcode8029::name()
            {
                return "void op_pop_base()";
            }

            std::string Opcode8029::notes()
            {
                return "";
            }
        }
    }
}
