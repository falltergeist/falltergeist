#include "../Graphics/IndexBuffer.h"
#include "../Graphics/GLCheck.h"

namespace Falltergeist {
    namespace Graphics {
        IndexBuffer::IndexBuffer(unsigned int* indexes, unsigned int count) {
            _indexes = indexes;
            _count = count;
            GL_CHECK(glGenBuffers(1, &_resourceId));
            GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _resourceId));
            GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indexes, GL_DYNAMIC_DRAW));
        }

        IndexBuffer::~IndexBuffer() {
            GL_CHECK(glDeleteBuffers(1, &_resourceId));
        }

        void IndexBuffer::bind() const {
            GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _resourceId));
        }

        void IndexBuffer::unbind() const {
            GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        const unsigned int *IndexBuffer::indexes() const {
            return _indexes;
        }

        unsigned int IndexBuffer::count() const {
            return _count;
        }
    }
}
