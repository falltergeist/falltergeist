#include <memory>
#include "../../Format/Fon/Glyph.h"
#include "../../Graphics/Font/FON.h"
#include "../../ResourceManager.h"

namespace Falltergeist
{
    namespace Graphics
    {
        FON::FON(const std::string& filename) : Font()
        {
            _filename = filename;
            _fon = ResourceManager::getInstance()->fonFileType(filename);

            unsigned int width = (_fon->maximumWidth()+2)*16u;
            unsigned int height = (_fon->maximumHeight()+2)*16u;


            _texture = std::make_unique<Graphics::Texture>(width, height);
            _texture->loadFromRGBA(_fon->rgba());
        }

        unsigned short FON::horizontalGap()
        {
            return _fon->horizontalGap();
        }

        unsigned short FON::verticalGap()
        {
            return _fon->verticalGap();
        }

        unsigned short FON::spaceWidth()
        {
            return _fon->spaceWidth();
        }

        unsigned short FON::width()
        {
            return _fon->maximumWidth();
        }

        unsigned short FON::height()
        {
            return _fon->maximumHeight();
        }

        unsigned short FON::glyphWidth(uint8_t ch)
        {
            return _fon->glyphs().at(ch).width();
        }
    }
}
