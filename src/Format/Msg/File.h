#pragma once

#include <vector>
#include "../../Format/Dat/Item.h"
#include "../../Format/Msg/Message.h"

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
