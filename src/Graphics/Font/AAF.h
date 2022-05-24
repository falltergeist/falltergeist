#pragma once

// Project includes
#include "../../Format/Aaf/File.h"
#include "../../Graphics/Font.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        class AAF : public Graphics::Font
        {
            public:
                explicit AAF(const std::string& filename);
                ~AAF() override = default;

                unsigned short horizontalGap() override;
                unsigned short verticalGap() override;
                unsigned short spaceWidth() override;
                unsigned short width() override;
                unsigned short height() override;
                unsigned short glyphWidth(uint8_t ch) override;

            private:
                Format::Aaf::File* _aaf = nullptr;
        };
    }
}
