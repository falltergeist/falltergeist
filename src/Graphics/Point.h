#pragma once

namespace Falltergeist
{
    namespace Graphics
    {
        /**
         * Represents a Point on screen: x and y coordinates, in pixels.
         */
        class Point
        {
            public:
                Point() : _x(0), _y(0) {}

                Point(int x, int y) : _x(x), _y(y) {}

                int x() const;
                int y() const;

                // Reference to x coordinate
                int& rx();
                // Reference to y coordinate
                int& ry();

                void setX(int x);
                void setY(int y);

                Point operator +(Point rhs) const;
                Point& operator +=(const Point& rhs);
                Point& operator -=(const Point& rhs);
                Point& operator *=(double rhs);
                Point& operator /=(double rhs);

                bool operator ==(const Point& rhs) const;
                bool operator !=(const Point& rhs) const;

                friend Point operator -(Point lhs, Point rhs);
                friend Point operator *(Point lhs, double rhs);
                friend Point operator /(Point lhs, double rhs);

                // Addition of given Point
                Point add(const Point& rhs) const;
                Point add(int x, int y) const;
                // Subtraction of given Point
                Point sub(const Point& rhs) const;
                // Multiplication by given number
                Point mul(double rhs) const;
                // Division by given number
                Point div(double rhs) const;

            private:
                int _x;
                int _y;
        };
    }
}
