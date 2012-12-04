#ifndef FALLTERGEIST_PLAYER_H
#define	FALLTERGEIST_PLAYER_H
#include "../Fallout/GcdFileType.h"

namespace Falltergeist
{
    
class Player
{
protected:
    // text from .bio file
    char * _bio;
    char * _name;
public:
    // primary stats
    unsigned int strength;
    unsigned int perception;
    unsigned int endurance;
    unsigned int charisma;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int luck;
    unsigned int freeStatsPoints;
    
    Player();
    Player(GcdFileType * gcd);
    virtual ~Player();
    void setBio(const char * text);
    void setName(const char * name);
    const char * getBio();
    const char * getName();
};

}
#endif	/* FALLTERGEIST_PLAYER_H */

