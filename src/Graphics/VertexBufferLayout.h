#pragma once

#include "../Graphics/VertexBufferAttribute.h"
#include <vector>

namespace Falltergeist {
    namespace Graphics {
        class VertexBufferLayout final {
        public:
            const std::vector<VertexBufferAttribute>& attributes() const;
            void addAttribute(const VertexBufferAttribute& attribute);
        private:
            std::vector<VertexBufferAttribute> _attributes;
        };
    }
}
