#include "LocationCamera.h"

namespace Falltergeist
{
    LocationCamera::LocationCamera(const Graphics::Size& size, const Graphics::Point& center) {
        setSize(size);
        setCenter(center);
    }

    LocationCamera::~LocationCamera() {
    }

    Graphics::Point LocationCamera::topLeft() const {
        return _center - (_size / 2.0);
    }

    const Graphics::Point& LocationCamera::center() const {
        return _center;
    }

    void LocationCamera::setCenter(const Graphics::Point& pos) {
        _center = pos;
        if (_center.x() < _size.width() / 2) {
            _center.setX(_size.width() / 2);
        }
        if (_center.y() < _size.height() / 2) {
            _center.setY(_size.height() / 2);
        }
    }

    const Graphics::Size& LocationCamera::size() const {
        return _size;
    }

    void LocationCamera::setSize(const Graphics::Size& size) {
        _size = size;
    }
}
