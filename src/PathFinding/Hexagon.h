#pragma once

#include <array>
#include <list>
#include "../Game/Object.h"
#include "../Graphics/Point.h"

#define HEX_SIDES 6
#define HEX_WIDTH 16
#define HEX_HEIGHT 12

namespace Falltergeist
{
    namespace Game
    {
        class Object;
    }

    using Graphics::Point;

    class Hexagon
    {
        public:
            Hexagon() = default;
            explicit Hexagon(unsigned int number);

            const Point& position() const;
            void setPosition(const Point& pos);

            inline bool inRender()
            {
                return _inRender;
            }

            inline void setInRender(bool value)
            {
                _inRender = value;
            }

            inline unsigned int number()
            {
                return _number;
            }

            inline void setNumber(unsigned int value)
            {
                _number = value;
            }

            inline unsigned int heuristic()
            {
                return _heuristic;
            }

            inline void setHeuristic(unsigned int value)
            {
                _heuristic = value;
            }

            inline int cubeX()
            {
                return _cubeX;
            }

            inline void setCubeX(unsigned int value)
            {
                _cubeX = value;
            }

            inline int cubeY()
            {
                return _cubeY;
            }

            inline void setCubeY(unsigned int value)
            {
                _cubeY = value;
            }

            inline int cubeZ()
            {
                return _cubeZ;
            }

            inline void setCubeZ(unsigned int value)
            {
                _cubeZ = value;
            }

            unsigned int addLight(unsigned int light);
            unsigned int subLight(unsigned int light);
            unsigned int setLight(unsigned int light);
            unsigned int light();

            bool canWalkThru();

            std::array<Hexagon*, HEX_SIDES>& neighbors();

            std::list<Game::Object*>* objects();

            Game::Orientation orientationTo(Hexagon *hexagon);

        protected:
            std::array<Hexagon*, HEX_SIDES> _neighbors = {};
            std::list<Game::Object*> _objects;
            unsigned int _number = 0; // position in hexagonal grid

            Point _position;

            int _cubeX = 0;
            int _cubeY = 0;
            int _cubeZ = 0;

            unsigned int _heuristic = 0;

            bool _inRender = false;

            unsigned int _light = 655;
    };
}
