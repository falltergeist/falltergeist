#include "../../VM/Handler/Opcode80A8.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A8::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto dataStack = context->dataStack();
                // TODO
                dataStack->pop()->asInteger();
                dataStack->pop()->asInteger();
                dataStack->pop()->asInteger();
                dataStack->pop()->asInteger();
            }

            int Opcode80A8::number()
            {
                return 0x80A8;
            }

            std::string Opcode80A8::name()
            {
                return "void set_map_start(int x, int y, int elev, int rot)";
            }

            std::string Opcode80A8::notes()
            {
                return "";
            }
        }
    }
}


