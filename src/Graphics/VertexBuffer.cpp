#include "../Graphics/VertexBuffer.h"
#include "../Graphics/GLCheck.h"
#include <stdexcept>

namespace Falltergeist {
    namespace Graphics {
        VertexBuffer::VertexBuffer(const void *data, unsigned int size, UsagePattern usagePattern) {
            _data = data;
            _size = size;

            unsigned int usage;
            switch (usagePattern) {
                case UsagePattern::DynamicDraw:
                    usage = GL_DYNAMIC_DRAW;
                    break;
                case UsagePattern::StaticDraw:
                    usage = GL_STATIC_DRAW;
                    break;
                default:
                    throw std::logic_error("Unsupported usage pattern");
            }

            GL_CHECK(glGenBuffers(1, &_resourceId));
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _resourceId));
            GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
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
