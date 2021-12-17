#include "../Graphics/VertexBuffer.h"
#include "../Graphics/GLCheck.h"

namespace Falltergeist {
    namespace Graphics {
        VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
            _data = data;
            _size = size;
            GL_CHECK(glGenBuffers(1, &_resourceId));
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _resourceId));
            GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
        }

        VertexBuffer::~VertexBuffer() {
            GL_CHECK(glDeleteBuffers(1, &_resourceId));
        }

        void VertexBuffer::bind() const {
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _resourceId));
        }

        void VertexBuffer::unbind() const {
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        const void* VertexBuffer::data() const {
            return _data;
        }

        unsigned int VertexBuffer::size() const {
            return _size;
        }
    }
}
