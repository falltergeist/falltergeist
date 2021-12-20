#pragma once

#include <string>

namespace Falltergeist{
    namespace Graphics {
        class ShaderFile final {
        public:
            ShaderFile(const std::string& file);
            const std::string& vertexSection() const;
            const std::string& fragmentSection() const;

        private:
            std::string _vertexSection;
            std::string _fragmentSection;
        };
    }
}
