#pragma once

#include "../../Base/Buffer.h"
#include "../Dat/Item.h"
#include "../Enums.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Rix
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    uint16_t width() const;
                    uint16_t height() const;

                    uint32_t* rgba();

                protected:
                    uint16_t _width = 0;
                    uint16_t _height = 0;
                    Base::Buffer<uint32_t> _rgba;
            };
        }
    }
}
