#pragma once

// Project includes
#include "../../Format/Fon/File.h"
#include "../../Graphics/Font.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        class FON : public Graphics::Font
        {
            public:
                explicit FON(const std::string& filename);
                ~FON() override = default;

                unsigned short horizontalGap() override;
                unsigned short verticalGap() override;
                unsigned short spaceWidth() override;
                unsigned short width() override;
                unsigned short height() override;
                unsigned short glyphWidth(uint8_t ch) override;

            private:
                Format::Fon::File* _fon = nullptr;
        };
    }
}
