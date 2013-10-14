#ifndef FALLTERGEIST_ANIMATEDPALETTE_H
#define FALLTERGEIST_ANIMATEDPALETTE_H

namespace Falltergeist
{

class AnimatedPalette
{
protected:
    unsigned int * _slimePalette;
    unsigned int _slimeTicks;
    unsigned int _slimeCounter;

    unsigned int * _fireSlowPalette;
    unsigned int _fireSlowTicks;
    unsigned int _fireSlowCounter;

    unsigned int * _fireFastPalette;
    unsigned int _fireFastTicks;
    unsigned int _fireFastCounter;

    unsigned int * _monitorsPalette;
    unsigned int _monitorsTicks;
    unsigned int _monitorsCounter;

    unsigned int * _shorePalette;
    unsigned int _shoreTicks;
    unsigned int _shoreCounter;

    unsigned char _blinkingRed;
    unsigned int _blinkingRedTicks;
    unsigned char _blinkingRedCounter;

public:
    AnimatedPalette();
    ~AnimatedPalette();
    void think();
    unsigned int color(unsigned char index);
};

}

#endif // FALLTERGEIST_ANIMATEDPALETTE_H
