#include "Opcode80A8.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A8::applyTo(std::shared_ptr<IContext> context)
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


