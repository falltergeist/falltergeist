// Project includes
#include "../Graphics/VertexBufferLayout.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Graphics {
        VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferAttribute>&& attributes)
        : _attributes(attributes) {
        }

        const std::vector<VertexBufferAttribute> &VertexBufferLayout::attributes() const {
            return _attributes;
        }

        void VertexBufferLayout::addAttribute(const VertexBufferAttribute &attribute) {
            _attributes.emplace_back(attribute);
        }
    }
}
