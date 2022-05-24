#pragma once

// Project includes
#include "../Dat/Item.h"
#include "../Dat/Stream.h"
#include "../Enums.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Mve
        {
            class Chunk;

            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    std::unique_ptr<Chunk> getNextChunk();

                    // set the position of underlying stream
                    void setPosition(unsigned int position);

                protected:
                    Dat::Stream _stream;
            };
        }
    }
}
