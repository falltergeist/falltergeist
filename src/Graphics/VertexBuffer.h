#pragma once

namespace Falltergeist {
    namespace Graphics {
        class VertexBuffer final {
        public:
            enum class UsagePattern {
                StaticDraw,
                DynamicDraw
            };

            VertexBuffer(const void* data, unsigned int size, UsagePattern usagePattern = UsagePattern::StaticDraw);
            ~VertexBuffer();

            void bind() const;
            void unbind() const;
            const void* data() const;
            unsigned int size() const;

        private:
            unsigned int _resourceId = 0;
            const void* _data;
            unsigned int _size;
        };

    }
}
