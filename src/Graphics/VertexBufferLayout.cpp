#include "../Graphics/VertexBufferLayout.h"

namespace Falltergeist {
    namespace Graphics {
        const std::vector<VertexBufferAttribute> &VertexBufferLayout::attributes() const {
            return _attributes;
        }

        void VertexBufferLayout::addAttribute(const VertexBufferAttribute &attribute) {
            _attributes.emplace_back(attribute);
        }
    }
}
