#pragma once

#include "../Graphics/Point.h"

namespace Falltergeist {
    namespace Graphics {
        /**
         * Represents a Size of a rectangular object: width and height, in pixels.
         */
        class Size {
        public:
            Size() : _width(0), _height(0) {
            }

            Size(int width, int height);

            explicit Size(const Point& rhs);

            Size& operator=(const Point& rhs);

            // Implicit conversion to Point
            operator Point() const;

            int width() const;

            int height() const;

            void setWidth(int width);

            void setHeight(int height);

            Size& operator+=(const Size& rhs);

            Size& operator-=(const Size& rhs);

            Size& operator*=(double rhs);

            Size& operator/=(double rhs);

            bool operator==(const Size& rhs) const;

            bool operator!=(const Size& rhs) const;

            friend Size operator+(Size lhs, const Size& rhs);

            friend Size operator-(Size lhs, const Size& rhs);

            friend Size operator*(Size lhs, double rhs);

            friend Size operator/(Size lhs, double rhs);

        private:
            int _width;

            int _height;
        };
    }
}
