#include "../Game/Elevator.h"

namespace Falltergeist
{
    namespace Game
    {
        Elevator::Elevator()
        {
            _size = 0;
            _panelFID = -1;
            _labelsFID = -1;
        }

        uint32_t Elevator::panelFID()
        {
            return _panelFID;
        }

        void Elevator::setPanelFID(uint32_t fid)
        {
            _panelFID = fid;
        }

        uint32_t Elevator::labelsFID()
        {
            return _labelsFID;
        }

        void Elevator::setLabelsFID(uint32_t fid)
        {
            _labelsFID = fid;
        }

        void Elevator::addFloor(Game::ElevatorFloor* floor)
        {
            _floors.push_back(floor);
        }

        size_t Elevator::size()
        {
            return _size;
        }

        void Elevator::setSize(size_t size)
        {
            _size = size;
        }

        std::vector<Game::ElevatorFloor*> Elevator::floors()
        {
            return _floors;
        }
    }
}
