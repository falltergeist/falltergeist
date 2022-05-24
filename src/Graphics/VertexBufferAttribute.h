#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Graphics {
        class VertexBufferAttribute final {
        public:
            enum class Type {
                Float
            };

            VertexBufferAttribute(
                unsigned int index,
                unsigned int componentsCount,
                Type type,
                bool normalized = false
            );

            unsigned int index() const;
            unsigned int componentsCount() const;
            Type type() const;
            bool normalized() const;
            unsigned int size() const;
        private:
            unsigned int _index;
            unsigned int _componentsCount;
            Type _type;
            bool _normalized;
        };
    }
}

