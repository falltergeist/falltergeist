#include "../Graphics/VertexBufferAttribute.h"
#include <stdexcept>

namespace Falltergeist {
    namespace Graphics {
        VertexBufferAttribute::VertexBufferAttribute(
            unsigned int index,
            unsigned int componentsCount,
            Type type,
            bool normalized,
            unsigned int stride
        ) {
            _index = index;
            _componentsCount = componentsCount;
            _type = type;
            _normalized = normalized;
            _stride = stride;
        }

        unsigned int VertexBufferAttribute::index() const {
            return _index;
        }

        unsigned int VertexBufferAttribute::componentsCount() const {
            return _componentsCount;
        }

        VertexBufferAttribute::Type VertexBufferAttribute::type() const {
            return _type;
        }

        bool VertexBufferAttribute::normalized() const {
            return _normalized;
        }

        unsigned int VertexBufferAttribute::stride() const {
            return _stride;
        }

        unsigned int VertexBufferAttribute::size() const {
            switch (type()) {
                case Type::Float:
                    return sizeof(float) * componentsCount();
                default:
                    throw std::logic_error("Unsupported type");
            }
        }
    }
}
