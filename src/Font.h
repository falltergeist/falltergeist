#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Graphics/Texture.h"
#include "Format/Aaf/File.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Aaf
        {
            class File;
        }
    }

    class Font
    {
        public:
            Font(const std::string& filename, unsigned int color);
            ~Font();

            unsigned int color();

            unsigned short horizontalGap();

            unsigned short verticalGap();

            unsigned short spaceWidth();

            unsigned short width();
            unsigned short height();

            std::string filename() const;

            Graphics::Texture* texture();

            Format::Aaf::File* aaf();

        private:
            unsigned int _color = 0;
            Format::Aaf::File* _aaf = nullptr;
            std::unique_ptr<Graphics::Texture> _texture = nullptr;
            std::string _filename;
    };
}
