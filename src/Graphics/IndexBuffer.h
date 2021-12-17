#pragma once

namespace Falltergeist {
    namespace Graphics {
        class IndexBuffer final {
        public:
            IndexBuffer(unsigned int* indexes, unsigned int count);
            ~IndexBuffer();

            void bind() const;
            void unbind() const;
            const unsigned int* indexes() const;
            unsigned int count() const;

        private:
            unsigned int _resourceId;
            const unsigned int* _indexes;
            unsigned int _count;
        };
    }
}
