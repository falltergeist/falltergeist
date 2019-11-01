#include "../../Format/Msg/Message.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Msg
        {
            Message::Message()
            {
            }

            Message::~Message()
            {
            }

            void Message::setNumber(unsigned int number)
            {
                _number = number;
            }

            unsigned int Message::number()
            {
                return _number;
            }

            void Message::setSound(std::string sound)
            {
                _sound = sound;
            }

            std::string Message::sound()
            {
                return _sound;
            }

            void Message::setText(std::string text)
            {
                _text = text;
            }

            std::string Message::text()
            {
                return _text;
            }

            std::string* Message::textPointer()
            {
                return &_text;
            }

            Message::operator std::string ()
            {
                return _text;
            }
        }
    }
}
