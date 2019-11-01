#pragma once

#include "../../Format/Fon/File.h"
#include "../../Graphics/Font.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class FON : public Graphics::Font
        {
            public:
                FON(const std::string& filename);
                ~FON();

                unsigned short horizontalGap() override;
                unsigned short verticalGap() override;
                unsigned short spaceWidth() override;
                unsigned short width() override;
                unsigned short height() override;
                unsigned short glyphWidth(uint8_t ch) override;

                virtual std::string filename() const { return _filename; }
                virtual Graphics::Texture *texture() { return _texture.get(); }

            private:
                Format::Fon::File* _fon = nullptr;
                std::unique_ptr<Graphics::Texture> _texture = nullptr;
                std::string _filename;
        };
    }
}
