#include "../Graphics/Pixels.h"

namespace Falltergeist {
    namespace Graphics {
        Pixels::Pixels(const void *data, const Size &size, Pixels::Format format)
                : _data(data), _size(size), _format(format) {
        }

        Pixels::Pixels(const void *data, const Size &&size, Pixels::Format format)
                : _data(data), _size(size), _format(format) {
        }

        const void *Pixels::data() const {
            return _data;
        }

        const Size &Pixels::size() const {
            return _size;
        }

        Pixels::Format Pixels::format() const {
            return _format;
        }
    }
}
