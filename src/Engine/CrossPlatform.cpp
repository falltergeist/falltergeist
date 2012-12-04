#include "../Engine/CrossPlatform.h"
#include <iostream>
#include <stdlib.h>



namespace Falltergeist
{
namespace CrossPlatform
{

const char * getHomePath()
{
    char const * home = getenv("HOME");
    return home;
}



}
}
