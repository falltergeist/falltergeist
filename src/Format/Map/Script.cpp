// Project includes
#include "../Map/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            int32_t Script::PID() const
            {
                return _PID;
            }

            void Script::setPID(int32_t PID)
            {
                _PID = PID;
            }

            int32_t Script::scriptId() const
            {
                return _scriptId;
            }

            void Script::setScriptId(int32_t value)
            {
                _scriptId = value;
            }

            Script::Type Script::type() const
            {
                return _type;
            }

            void Script::setType(Script::Type type)
            {
                _type = type;
            }

            void Script::setSpatialTile(uint32_t tile)
            {
                _spatialTile = tile;
            }

            uint32_t Script::spatialTile() const
            {
                return _spatialTile;
            }

            void Script::setSpatialRadius(uint32_t radius)
            {
                _spatialRadius = radius;
            }

            uint32_t Script::spatialRadius() const
            {
                return _spatialRadius;
            }

            void Script::setTimerTime(uint32_t time)
            {
                _timerTime = time;
            }

            uint32_t Script::timerTime() const
            {
                return _timerTime;
            }
        }
    }
}
