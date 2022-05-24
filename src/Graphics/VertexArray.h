#pragma once

// Project includes
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/VertexBufferLayout.h"

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist {
    namespace Graphics {
        class VertexArray final {
        public:
            VertexArray();
            ~VertexArray();

            void bind() const;
            void unbind() const;

            void addBuffer(const std::unique_ptr<VertexBuffer>& buffer, const VertexBufferLayout& bufferLayout);
        private:
            unsigned int _resourceId;
        };
    }
}
