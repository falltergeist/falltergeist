#include "../../Format/Dat/Stream.h"
#include "../../Format/Bio/File.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Bio
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);
                for (unsigned i = 0; i != stream.size(); ++i) {
                    _text += stream.uint8();
                }
            }

            std::string File::text()
            {
                return _text;
            }
        }
    }
}
