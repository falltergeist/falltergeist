#pragma once

#include "../Graphics/VertexBufferAttribute.h"
#include <vector>

namespace Falltergeist {
    namespace Graphics {
        class VertexBufferLayout final {
        public:
            VertexBufferLayout() = default;
            VertexBufferLayout(const std::vector<VertexBufferAttribute>&& attributes);
            const std::vector<VertexBufferAttribute>& attributes() const;
            void addAttribute(const VertexBufferAttribute& attribute);
        private:
            std::vector<VertexBufferAttribute> _attributes;
        };
    }
}
