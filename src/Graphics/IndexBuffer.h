#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Graphics {
        class IndexBuffer final {
        public:
            enum class UsagePattern {
                StaticDraw,
                DynamicDraw
            };

            IndexBuffer(unsigned int* indexes, unsigned int count, UsagePattern usagePattern = UsagePattern::StaticDraw);
            ~IndexBuffer();

            void bind() const;
            void unbind() const;
            const unsigned int* indexes() const;
            unsigned int count() const;

        private:
            unsigned int _resourceId = 0;
            const unsigned int* _indexes;
            unsigned int _count;
        };
    }
}
