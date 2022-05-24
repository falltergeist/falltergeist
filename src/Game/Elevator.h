#pragma once

// Project includes

// Third-party includes

// stdlib
#include <vector>
#include <memory>

namespace Falltergeist
{
    namespace Game
    {

        typedef struct {
            uint32_t mapId;
            uint32_t elevation;
            uint32_t position;
            size_t size;
        } ElevatorFloor;

        class Elevator
        {
            public:

                uint32_t panelFID();
                void setPanelFID(uint32_t fid);
                uint32_t labelsFID();
                void setLabelsFID(uint32_t fid);
                void addFloor(ElevatorFloor* floor);
                size_t size();
                void setSize(size_t size);
                std::vector<ElevatorFloor*> floors();

                Elevator();


            private:
                uint32_t _panelFID;
                uint32_t _labelsFID;
                size_t _size;
                std::vector<ElevatorFloor*> _floors;

        };


    }
}
