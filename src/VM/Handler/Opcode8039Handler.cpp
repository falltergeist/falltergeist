// Project includes
#include "../../VM/Handler/Opcode8039Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8039::Opcode8039(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8039::_run(VM::Script& script) {
                auto &debug = _logger->debug();
                debug << "[8039] [*] op_add(aValue, bValue)" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                debug << "    types: " << aValue.typeName() << " + " << bValue.typeName() << std::endl;
                switch (bValue.type()) {
                    case StackValue::Type::INTEGER: // INTEGER
                    {
                        int arg2 = bValue.integerValue();
                        switch (aValue.type()) {
                            case StackValue::Type::INTEGER: // INTEGER + INTEGER
                            {
                                script.dataStack()->push(aValue.integerValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + INTEGER
                            {
                                script.dataStack()->push(aValue.floatValue() + (float) arg2);
                                break;
                            }
                            case StackValue::Type::STRING: // STRING + INTEGER
                            {
                                std::string arg1 = aValue.stringValue();
                                script.dataStack()->push(arg1 + bValue.toString());
                                break;
                            }
                            default: {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    case StackValue::Type::STRING: {
                        auto arg2 = bValue.stringValue();
                        switch (aValue.type()) {
                            case StackValue::Type::STRING: // STRING + STRING
                            {
                                script.dataStack()->push(aValue.stringValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + STRING
                            {
                                _error("op_add - FLOAT+STRING not allowed");
                                break;
                            }
                            case StackValue::Type::INTEGER: // INTEGER + STRING
                            {
                                _error("op_add - INTEGER+STRING not allowed");
                                break;
                            }
                            default: {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    case StackValue::Type::FLOAT: // FLOAT
                    {
                        auto arg2 = bValue.floatValue();
                        switch (aValue.type()) {
                            case StackValue::Type::INTEGER: // INTEGER + FLOAT
                            {
                                script.dataStack()->push((float) aValue.integerValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + FLOAT
                            {
                                script.dataStack()->push(aValue.floatValue() + arg2);
                                break;
                            }
                            case StackValue::Type::STRING: // STRING + FLOAT
                            {
                                auto arg1 = aValue.stringValue();
                                script.dataStack()->push(arg1 + bValue.toString());
                                break;
                            }
                            default: {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    default: {
                        _error(std::string("op_add - invalid right argument type: ") + bValue.typeName());
                    }
                }
            }
        }
    }
}
