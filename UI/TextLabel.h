#ifndef FALLTERGEIST_TEXTLABEL_H
#define FALLTERGEIST_TEXTLABEL_H

#include "InteractiveSurface.h"

namespace Falltergeist
{
class AafFileType;

class TextLabel : public InteractiveSurface
{
protected:
    const char * _text;
    AafFileType * _aafFileType;
    Surface * _generateSurface();
public:
    TextLabel(const char * label, int x = 0, int y = 0);
    AafFileType * getAafFileType();
};

}
#endif // FALLTERGEIST_TEXTLABEL_H
