#pragma once

// Project includes
#include "../../Format/Dat/Item.h"
#include "../../Format/Msg/Message.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Msg
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    Message* message(unsigned int number);

                private:
                    std::vector<Message> _messages;
            };
        }
    }
}
