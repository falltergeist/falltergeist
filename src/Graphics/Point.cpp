#include "../Graphics/Point.h"

namespace Falltergeist
{
    namespace Graphics
    {
        int Point::x() const
        {
            return _x;
        }

        int Point::y() const
        {
            return _y;
        }

        int& Point::rx()
        {
            return _x;
        }

        int& Point::ry()
        {
            return _y;
        }

        void Point::setX(int x)
        {
            _x = x;
        }

        void Point::setY(int y)
        {
            _y = y;
        }

        Point Point::operator +(Point rhs) const
        {
            rhs += *this;
            return rhs;
        }

        Point& Point::operator +=(const Point& rhs)
        {
            _x += rhs._x;
            _y += rhs._y;
            return *this;
        }

        Point& Point::operator -=(const Point& rhs)
        {
            _x -= rhs._x;
            _y -= rhs._y;
            return *this;
        }

        Point& Point::operator *=(double rhs)
        {
            _x = static_cast<int>(_x * rhs);
            _y = static_cast<int>(_y * rhs);
            return *this;
        }

        Point& Point::operator /=(double rhs)
        {
            _x = static_cast<int>(_x / rhs);
            _y = static_cast<int>(_y / rhs);
            return *this;
        }

        bool Point::operator ==(const Point& rhs) const
        {
            return _x == rhs._x && _y == rhs._y;
        }

        bool Point::operator !=(const Point& rhs) const
        {
            return !(*this == rhs);
        }

        Point operator -(Point lhs, Point rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        Point operator *(Point lhs, double rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        Point operator /(Point lhs, double rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        Point Point::add(const Point& rhs) const
        {
            return *this + rhs;
        }

        Point Point::add(int x, int y) const
        {
            return add({x, y});
        }

        Point Point::sub(const Point& rhs) const
        {
            return *this - rhs;
        }

        Point Point::mul(double rhs) const
        {
            return *this * rhs;
        }

        Point Point::div(double rhs) const
        {
            return *this / rhs;
        }
    }
}
