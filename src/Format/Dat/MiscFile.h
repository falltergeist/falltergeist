#pragma once

#include <fstream>
#include <string>
#include <memory>
#include "../../Format/Dat/Item.h"
#include "../../Format/Dat/Stream.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            // A simple file
            class MiscFile : public Item
            {
                public:
                    MiscFile(Stream&& stream);

                    Stream& stream();

                protected:
                    Stream _stream;
            };
        }
    }
}
