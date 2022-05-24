#pragma once

// Project includes
#include <string>

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Graphics {
        class ShaderFile final {
        public:
            ShaderFile(const std::string& path);

            const std::string& vertexSection() const;

            const std::string& fragmentSection() const;

        private:
            std::string _vertexSection;

            std::string _fragmentSection;
        };
    }
}
