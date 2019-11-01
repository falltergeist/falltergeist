#include "LocationCamera.h"

namespace Falltergeist
{
    LocationCamera::LocationCamera(const Size& size, const Point& center)
    {
        setSize(size);
        setCenter(center);
    }

    LocationCamera::~LocationCamera()
    {
    }

    Point LocationCamera::topLeft() const
    {
        return _center - (_size / 2.0);
    }

    const Point& LocationCamera::center() const
    {
        return _center;
    }

    void LocationCamera::setCenter(const Point& pos)
    {
        _center = pos;
        if (_center.x() < _size.width() / 2)
        {
            _center.setX(_size.width() / 2);
        }
        if (_center.y() < _size.height() / 2)
        {
            _center.setY(_size.height() / 2);
        }
    }

    const Size& LocationCamera::size() const
    {
        return _size;
    }

    void LocationCamera::setSize(const Size& size)
    {
        _size = size;
    }
}
