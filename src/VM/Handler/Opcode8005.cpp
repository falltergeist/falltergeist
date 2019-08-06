#include "../../VM/Handler/Opcode8005.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutProcedure.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8005::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto functionIndex = context->dataStack()->pop()->asInteger();
                // @TODO: pass arguments and call external procedures
                /*auto argumentCount = _script->dataStack()->popInteger();
                std::vector<int> args;
                for (int i = 0; i < argumentCount; i++)
                {
                    args.push_back(_script->dataStack()->popInteger());
                }*/
                context->setProgramCounter(context->getProcedureByIndex(functionIndex)->bodyOffset());
            }

            int Opcode8005::number()
            {
                return 0x8005;
            }

            std::string Opcode8005::name()
            {
                return "void op_call(int index)";
            }

            std::string Opcode8005::notes()
            {
                return "Partially implemented";
            }
        }
    }
}
