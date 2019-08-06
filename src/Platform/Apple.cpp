#if defined (__APPLE__)

#include <mach/mach_time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/param.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/ucred.h>
#include "../Logger.h"
#include "../Platform/Apple.h"

namespace Falltergeist
{
    namespace Platform
    {
        std::string Apple::name()
        {
            return "Apple";
        }

        std::vector<std::string> Apple::compactDiscDrivePaths()
        {
            Logger::warning() << "CD-ROM detection not supported" << std::endl;
            return std::vector<std::string>();
        }

        uint32_t Apple::microtime()
        {
            static mach_timebase_info_data_t timebase;
            if ( timebase.denom == 0 ) {
                (void) mach_timebase_info(&timebase);
            }

            uint64_t time = mach_absolute_time();
            return static_cast<uint32_t>(((double)time * (double)timebase.numer) / ((double)timebase.denom));
        }

        std::string Apple::applicationDataPath()
        {
            return getHomeDirectory() + "/Library/Application Support/falltergeist";
        }
    }
}
#endif
