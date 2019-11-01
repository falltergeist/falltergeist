#pragma once

#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Msg
        {
            class Message
            {
                public:
                    Message();
                    ~Message();

                    void setNumber(unsigned int number);
                    unsigned int number();

                    void setSound(std::string sound);
                    std::string sound();

                    void setText(std::string text);
                    std::string text();
                    std::string* textPointer();

                    operator std::string();

                protected:
                    unsigned int _number = 0;
                    std::string _sound;
                    std::string _text;
            };
        }
    }
}
