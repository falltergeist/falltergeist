#pragma once

namespace Falltergeist {
    namespace Graphics {
        class VertexBuffer final {
        public:
            VertexBuffer(const void* data, unsigned int size);
            ~VertexBuffer();

            void bind() const;
            void unbind() const;
            const void* data() const;
            unsigned int size() const;

        private:
            unsigned int _resourceId;
            const void* _data;
            unsigned int _size;
        };

    }
}
