#include "Opcode8013.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8013::applyTo(std::shared_ptr<IContext> context)
            {
                auto number = context->dataStack()->pop()->asInteger();
                auto value = context->dataStack()->pop();
                context->dataStack()->at(context->dataStack()->stackBase() + number) = value;

//                auto &debug = Logger::debug("SCRIPT");
//
//                debug << "[8013] [*] op_store_global" << std::endl
//                      << "      num: " << number << std::endl;
//                //<< "     type: " << value.typeName() << std::endl
//                //<< "    value: " << value.toString();
//
//                debug << std::endl;
            }

            int Opcode8013::number()
            {
                return 0x8013;
            }

            std::string Opcode8013::name()
            {
                return "void op_store_global(int number, mixed value)";
            }

            std::string Opcode8013::notes()
            {
                return "";
            }
        }
    }
}
