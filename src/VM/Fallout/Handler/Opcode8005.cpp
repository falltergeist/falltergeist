#include "../../../VM/Fallout/Handler/Opcode8005.h"
#include "../../../VM/Fallout/IContext.h"
#include "../../../VM/Fallout/IProcedure.h"
#include "../../../VM/Fallout/IStack.h"
#include "../../../VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode8005::applyTo(std::shared_ptr<IContext>& context)
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
}
