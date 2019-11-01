#pragma once

#include <string>
#include <vector>
#include "../Dat/Item.h"
#include "../Dat/Stream.h"
#include "../Map/Elevation.h"
#include "../Map/Script.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Pro
        {
            class File;
        }

        namespace Map
        {
            class Object;

            typedef Pro::File* (*ProFileTypeLoaderCallback)(uint32_t);

            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    // TODO: get rid of two-step initialization
                    void init(ProFileTypeLoaderCallback callback);

                    const std::vector<Elevation>& elevations() const;
                    const std::vector<Script>& scripts() const;
                    const std::vector<int32_t>& LVARS() const;
                    const std::vector<int32_t>& MVARS() const;

                    uint32_t defaultPosition() const;
                    uint32_t defaultElevation() const;
                    uint32_t defaultOrientation() const;
                    uint32_t elevationFlags() const;
                    uint32_t mapId() const;
                    uint32_t version() const;
                    uint32_t timeSinceEpoch() const;

                    int32_t scriptId() const;
                    int32_t unknown1() const;

                    std::string name() const;

                private:
                    Dat::Stream _stream;

                    bool _initialized = false;

                    std::vector<Elevation> _elevations;
                    std::vector<Script> _scripts;
                    std::vector<int32_t> _MVARS;
                    std::vector<int32_t> _LVARS;

                    uint32_t _version = 0;
                    uint32_t _defaultPosition = 0;
                    uint32_t _defaultElevation = 0;
                    uint32_t _defaultOrientaion = 0;
                    uint32_t _MVARsize = 0;
                    uint32_t _LVARsize = 0;
                    uint32_t _elevationFlags = 0;
                    uint32_t _mapId = 0;
                    uint32_t _timeSinceEpoch = 0;

                    int32_t _unknown1 = 1;
                    int32_t _scriptId = -1;

                    std::string _name;

                    std::unique_ptr<Object> _readObject(Dat::Stream& stream, ProFileTypeLoaderCallback callback);
            };
        }
    }
}
