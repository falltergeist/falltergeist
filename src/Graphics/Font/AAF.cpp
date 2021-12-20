#include <memory>
#include "../../Format/Aaf/Glyph.h"
#include "../../Graphics/Font/AAF.h"
#include "../../Graphics/Pixels.h"
#include "../../ResourceManager.h"

namespace Falltergeist {
    namespace Graphics {
        AAF::AAF(const std::string &filename) : Font() {
            _filename = filename;
            _aaf = ResourceManager::getInstance()->aafFileType(filename);

            unsigned int width = (_aaf->maximumWidth() + 2) * 16u;
            unsigned int height = (_aaf->maximumHeight() + 2) * 16u;

            _texture = std::make_unique<Graphics::Texture>(
                    Pixels(_aaf->rgba(), Size(width, height), Pixels::Format::RGBA)
            );
        }

        unsigned short AAF::horizontalGap() {
            return _aaf->horizontalGap();
        }

        unsigned short AAF::verticalGap() {
            return _aaf->verticalGap();
        }

        unsigned short AAF::spaceWidth() {
            return _aaf->spaceWidth();
        }

        unsigned short AAF::width() {
            return _aaf->maximumWidth();
        }

        unsigned short AAF::height() {
            return _aaf->maximumHeight();
        }

        unsigned short AAF::glyphWidth(uint8_t ch) {
            return _aaf->glyphs().at(ch).width();
        }
    }
}
