#ifndef FALLTERGEIST_BIGDIGITROLLER_H
#define	FALLTERGEIST_BIGDIGITROLLER_H

#include "Engine/InteractiveSurface.h"

namespace Falltergeist
{
    
class BigDigitRoller : public InteractiveSurface
{
protected:
    unsigned int _value;
public:
    BigDigitRoller(int x, int y);
    virtual ~BigDigitRoller();
};

}
#endif	/* FALLTERGEIST_BIGDIGITROLLER_H */

