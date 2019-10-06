#include <cmath>
#include "../Game/DoorSceneryObject.h"
#include "../PathFinding/Hexagon.h"

namespace Falltergeist
{
    Hexagon::Hexagon(unsigned int number)
    {
        // Init hex's grid position
        setNumber(number);
    }

    std::array<Hexagon*, HEX_SIDES>& Hexagon::neighbors()
    {
        return _neighbors;
    }

    std::list<Game::Object*>* Hexagon::objects()
    {
        return &_objects;
    }

    const Point& Hexagon::position() const
    {
        return _position;
    }

    void Hexagon::setPosition(const Point& pos)
    {
        _position = pos;
    }

    bool Hexagon::canWalkThru()
    {
        // Search hex for any blocking objects...
        for (const auto object : _objects) {
            if (!object->canWalkThru()) {
                return false;
            }
        }
        return true;
    }

    Game::Orientation Hexagon::orientationTo(Hexagon *hexagon)
    {
        Point delta = hexagon->position() - _position;
        int dx = delta.x();
        int dy = delta.y();

        unsigned char result;

        if (dx) {
            // trigonometry magic.
            // basically, we try to find angle to second hex in circle, where first hex is center
            // and then find out to which of 60� slices it belongs

            double degree = atan2((double)-dy, (double)dx) * 180.0 * 0.3183098862851122; //  180 * 1/PI

            result = (360 - ((signed int)degree + 180) - 90 + ((char)-(360 - ((signed int)degree + 180) - 90 < 0) & 360)) / 60;
            if (result > 5) {
                result = 5;
            }
        } else if (dy < 0) {
            result = 0;
        } else {
            result = 2;
        }

        return Game::Orientation(result); // TODO: this is wrong. orientation!=direction
    }

    unsigned int Hexagon::addLight(unsigned int light)
    {
        _light += light;
        if (_light > 65536) {
            _light = 65536;
        }
        return _light;
    }

    unsigned int Hexagon::subLight(unsigned int light)
    {
        _light -= light;
        if ((int)_light < 655) {
            _light = 655;
        }
        return _light;
    }

    unsigned int Hexagon::light()
    {
        return _light;
    }

    unsigned int Hexagon::setLight(unsigned int light)
    {
        _light = light;
        return _light;
    }
}
