#pragma once

// Project includes
#include "../Graphics/Size.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Graphics {
        class Pixels final {
        public:
            enum class Format {
                RGB,
                RGBA
            };

            Pixels(const void* data, const Size& size, Format format);
            Pixels(const void* data, const Size&& size, Format format);

            const void* data() const;
            const Size& size() const;
            Format format() const;

        private:
            const void* _data;
            const Size _size;
            const Format _format;
        };
    }
}
