#pragma once

namespace Falltergeist
{
    namespace Game
    {
        /**
         * represents orientation in hexagonal space
         */
        class Orientation
        {
            public:
                enum
                {
                    NS = 0, EW, NC, SC, EC, WC
                };

                Orientation(unsigned char value = NS);
                Orientation& operator =(unsigned char value);
                operator unsigned char() const;

            private:
                unsigned char _dir;
        };
    }
}
