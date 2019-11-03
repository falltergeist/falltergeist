#pragma once

#include <list>
#include <string>
#include <vector>

namespace Falltergeist
{
    class CrossPlatform
    {
        public:
            CrossPlatform();
            ~CrossPlatform();

            static std::string getVersion();
            static std::string getHomeDirectory();
            static std::string getExecutableDirectory();
            static std::vector<std::string> getCdDrivePaths();
            static std::string findFalloutDataPath();
            static std::vector<std::string> findFalloutDataFiles();
            static std::string findFalltergeistDataPath();
            static std::string getConfigPath();
            static std::vector<std::string> getDataPaths();

            // Create directory at given path with parent directories as needed.
            // Throw runtime_error on failure.
            static void createDirectory(std::string path);

            static bool fileExists(std::string file);

            static float deltaTime();

        protected:
            static std::string _falloutDataPath;
            static std::string _falltergeistDataPath;
            static std::vector<std::string> _dataFiles;
            static std::string _version;
            const static std::vector<std::string> _necessaryDatFiles;

            // Create directory at given path, if not already exists.
            // If directory did exist, then return false, otherwise return true.
            // Throw runtime_error on failure.
            static bool _createDirectory(const char *dir);
    };
}
