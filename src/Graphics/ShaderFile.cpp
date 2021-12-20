#include "../Graphics/ShaderFile.h"
#include "../Exception.h"
#include <fstream>
#include <iostream>

namespace Falltergeist {
    namespace Graphics {
        enum class ShaderFileSection {
            Fragment,
            Vertex
        };

        ShaderFile::ShaderFile(const std::string &file) {
            std::ifstream ifstream(file);
            if (!ifstream.is_open()) {
                throw Exception("Can't open shader source " + file);
            }

            ShaderFileSection currentSection = ShaderFileSection::Vertex;
            std::string fragmentSection;
            std::string vertexSection;

            while (!ifstream.eof()) {
                std::string line;
                std::getline(ifstream, line);

                if (line.find("#shader vertex") != std::string::npos) {
                    currentSection = ShaderFileSection::Vertex;
                    continue; // Skip shader section definition
                }

                if (line.find("#shader fragment") != std::string::npos) {
                    currentSection = ShaderFileSection::Fragment;
                    continue; // Skip shader section definition
                }

                if (currentSection == ShaderFileSection::Fragment) {
                    fragmentSection += line + '\n';
                } else {
                    vertexSection += line + '\n';
                }
            }
            _fragmentSection = fragmentSection;
            _vertexSection = vertexSection;
            ifstream.close();
        }

        const std::string &ShaderFile::vertexSection() const {
            return _vertexSection;
        }

        const std::string &ShaderFile::fragmentSection() const {
            return _fragmentSection;
        }
    }
}
