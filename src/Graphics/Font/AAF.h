#pragma once

#include "../../Format/Aaf/File.h"
#include "../../Graphics/Font.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class AAF : public Graphics::Font
        {
            public:
                AAF(const std::string& filename);
                ~AAF();

                unsigned short horizontalGap() override;
                unsigned short verticalGap() override;
                unsigned short spaceWidth() override;
                unsigned short width() override;
                unsigned short height() override;
                unsigned short glyphWidth(uint8_t ch) override;

                virtual std::string filename() const { return _filename; }
                virtual Graphics::Texture *texture() { return _texture.get(); }

            private:
                Format::Aaf::File* _aaf = nullptr;
                std::unique_ptr<Graphics::Texture> _texture = nullptr;
                std::string _filename;
        };
    }
}
