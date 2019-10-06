#include <memory>
#include "Opcode810A.h"
#include "Game/Object.h"
#include "UI/TextArea.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/Exception.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810A::applyTo(std::shared_ptr<IContext> context)
            {
                int type = context->dataStack()->pop()->asInteger();
                SDL_Color color = {0x00, 0x00, 0x00, 0xff};
                switch (type) {
                    case -2:
                        // CAPITAL RED LETTERS  FF 00 00
                        color = {0xff, 0x00, 0x00, 0xff};
                        break;
                    case -1:
                        // Self-rotating colors @todo
                        color = {0xff, 0x00, 0x00, 0xff}; // temporary taken from -2
                        break;
                    case 0:
                    case 8:
                    case 13:
                        color = {0xff, 0xff, 0x7f, 0xff};
                        break;
                    case 1:
                    case 5:
                    case 10:
                        color = {0x55, 0x55, 0x55, 0xff};
                        break;
                    case 2:
                        color = {0xff, 0x00, 0x00, 0xff};
                        break;
                    case 3:
                        color = {0x3c, 0xfb, 0x00, 0xff};
                        break;
                    case 4:
                        color = {0x30, 0x59, 0x8e, 0xff};
                        break;
                    case 6:
                        color = {0xa2, 0xa2, 0xa2, 0xff};
                        break;
                    case 7:
                        color = {0xff, 0x49, 0x49, 0xff};
                        break;
                    case 9:
                        color = {0xff, 0xff, 0xff, 0xff};
                        break;
                    case 11:
                        color = {0x3c, 0x3c, 0x3c, 0xff};
                        break;
                    case 12:
                        color = {0x75, 0x75, 0x75, 0xff};
                        break;
                    default:
                        throw Exception("float_msg - wrong type: " + std::to_string(type));
                }

                auto string = context->dataStack()->pop()->asString();
                auto object = context->dataStack()->pop()->asObject();

                auto floatMessage = std::make_unique<UI::TextArea>(string);
                floatMessage->setWidth(200);
                floatMessage->setWordWrap(true);
                floatMessage->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
                floatMessage->setOutlineColor({0x00, 0x00, 0x00, 0xFF});
                floatMessage->setFont("font1.aaf", color);
                object->setFloatMessage(std::move(floatMessage));
            }

            int Opcode810A::number()
            {
                return 0x810A;
            }

            std::string Opcode810A::name()
            {
                return "void float_msg(object who, string msg, int type)";
            }

            std::string Opcode810A::notes()
            {
                return "";
            }
        }
    }
}
