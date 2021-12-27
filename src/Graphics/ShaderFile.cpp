#include "../Graphics/ShaderFile.h"
#include "../Exception.h"
#include "../ResourceManager.h"
#include <iostream>
#include <sstream>

namespace Falltergeist {
    namespace Graphics {
        enum class ShaderFileSection {
            Fragment,
            Vertex
        };

        ShaderFile::ShaderFile(const std::string &path) {
            auto& vfs = ResourceManager::getInstance()->vfs();
            auto file = vfs.open(path, VFS::IFile::OpenMode::Read);
            if (!file || !file->isOpened()) {
                throw Exception("Can't open shader source " + path);
            }

            std::string content;
            content.resize(file->size());
            file->read(content.data(), file->size());
            vfs.close(file);

            std::istringstream contentStream(content);

            ShaderFileSection currentSection = ShaderFileSection::Vertex;
            std::string fragmentSection;
            std::string vertexSection;

            while (!contentStream.eof()) {
                std::string line;
                std::getline(contentStream, line);

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
        }

        const std::string &ShaderFile::vertexSection() const {
            return _vertexSection;
        }

        const std::string &ShaderFile::fragmentSection() const {
            return _fragmentSection;
        }
    }
}
