#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace VFS {
        struct DatArchiveEntry {
            unsigned int packedSize = 0;

            unsigned int unpackedSize = 0;

            unsigned int dataOffset = 0;

            bool isCompressed = false;
        };
    }
}
