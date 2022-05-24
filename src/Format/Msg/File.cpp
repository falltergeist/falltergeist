// Project includes
#include "../../Exception.h"
#include "../../Format/Msg/File.h"
#include "../../Format/Dat/Stream.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Msg
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                /*
                 * Because of bug in CMBATAI2.MSG in messages #1382 and #32020 we need to explode each line with '{' symbol
                 * Any extra '}' symbols must be trimed from exploded parts
                 */

                while (stream.position() < stream.size())
                {
                    uint8_t chr = stream.uint8();
                    if (chr == '{')
                    {
                        std::string number;
                        std::string sound;
                        std::string text;
                        chr = 0;
                        // number
                        while (chr != '{')
                        {
                            chr = stream.uint8();
                            if (chr != '{' && chr != '}')
                            {
                                number += chr;
                            }
                        }

                        // sound
                        chr = 0;
                        while (chr != '{')
                        {
                            chr = stream.uint8();
                            if (chr != '{' && chr != '}')
                            {
                                sound += chr;
                            }
                        }

                        chr = 0;
                        // text
                        while (chr != '}' && chr != '{' && stream.position() < stream.size())
                        {
                            chr = stream.uint8();
                            if (chr != '{' && chr != '}')
                            {
                                text += chr;
                            }
                        }

                        // "put back" last character
                        stream.setPosition(stream.position() - 1);

                        while (text.find("\n") != std::string::npos)
                        {
                            text.replace(text.find("\n"), 1, "");
                        }
                        while (text.find("\r") != std::string::npos)
                        {
                            text.replace(text.find("\r"), 1, "");
                        }

                        Message message;
                        message.setNumber(std::stoi(number));
                        message.setSound(sound);
                        message.setText(text);
                        _messages.push_back(message);
                    }
                }
            }

            Message* File::message(unsigned int number)
            {
                for (auto& message : _messages)
                {
                    if (message.number() == number)
                    {
                        return &message;
                    }
                }
                throw Exception("File::message() - number is out of range: " + std::to_string(number));
            }
        }
    }
}
