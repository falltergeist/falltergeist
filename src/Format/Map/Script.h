#pragma once

// Project includes

// Third-party includes

// stdlib
#include <cstdint>

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            class Script
            {
                public:
                    enum class Type
                    {
                        SYSTEM = 0,
                        SPATIAL,
                        TIMER,
                        ITEM,
                        CRITTER

                    };

                    int32_t PID() const;
                    void setPID(int32_t PID);

                    int32_t scriptId() const;
                    void setScriptId(int32_t value);

                    Type type() const;
                    void setType(Type type);

                    void setSpatialTile(uint32_t tile);
                    uint32_t spatialTile() const;

                    void setSpatialRadius(uint32_t radius);
                    uint32_t spatialRadius() const;

                    void setTimerTime(uint32_t time);
                    uint32_t timerTime() const;

                private:
                    int32_t _PID = 0;
                    int32_t _scriptId = -1;
                    uint32_t _spatialTile = 0;
                    uint32_t _spatialRadius = 0;
                    uint32_t _timerTime = 0;

                    Type _type;
            };
        }
    }
}
