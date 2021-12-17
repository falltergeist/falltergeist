#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBufferLayout.h"
#include "../Graphics/GLCheck.h"
#include <stdexcept>

namespace Falltergeist {
    namespace Graphics {
        VertexArray::VertexArray() {
            GL_CHECK(glGenVertexArrays(1, &_resourceId));
            GL_CHECK(glBindVertexArray(_resourceId));
        }

        VertexArray::~VertexArray() {
            GL_CHECK(glDeleteVertexArrays(1, &_resourceId));
        }

        void VertexArray::bind() const {
            GL_CHECK(glBindVertexArray(_resourceId));
        }

        void VertexArray::unbind() const {
            GL_CHECK(glBindVertexArray(0));
        }

        void VertexArray::addBuffer(const std::unique_ptr<VertexBuffer>& buffer, const VertexBufferLayout &bufferLayout) {
            bind();
            buffer->bind();
            unsigned int offset = 0;
            for (auto &attribute : bufferLayout.attributes()) {
                GL_CHECK(glEnableVertexAttribArray(attribute.index()));

                unsigned int glType;
                switch (attribute.type()) {
                    case VertexBufferAttribute::Type::Float:
                        glType = GL_FLOAT;
                        break;
                    default:
                        throw std::logic_error("Unsupported attribute glType");
                }

                GL_CHECK(glVertexAttribPointer(
                    attribute.index(),
                    attribute.componentsCount(),
                    glType,
                    attribute.normalized() ? GL_TRUE : GL_FALSE,
                    attribute.stride(),
                    (const void *) offset
                ));
                offset += attribute.size();
            }
        }
    }
}
