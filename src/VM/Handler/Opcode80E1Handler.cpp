#include "../../VM/Handler/Opcode80E1Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80E1::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // @TODO: add implementation
                Logger::debug("SCRIPT") << "[80E1] [*] int metarule3(int meta, int p1, int p2, int p3)" << std::endl;
                auto dataStack = _script->dataStack();

                auto arg3 = dataStack->pop();
                auto arg2 = dataStack->pop();
                auto arg1 = dataStack->pop();
                auto meta = dataStack->popInteger();
                int result = 0;
                switch (meta) {
                    case 100: // rm_fixed_timer_event(object, fixed_param, 0)
                    {
                        auto state = Game::Game::getInstance()->locationState();
                        if (state) {
                            state->removeTimerEvent(arg1.objectValue(), arg2.integerValue());
                        }
                        break;
                    }
                    case 101: // mark subtile visited on worldmap - mark_world_subtile_visited(x, y, radius)
                        break;
                    case 102: // METARULE3_SET_WM_MUSIC - (map index, ACM file name)
                        break;
                    case 103: // player_kill_count(critterType)
                        break;
                    case 104: // int mark_map_entrance_state(int map_idx, int state, int elev); elev -1 means for all elevations
                        break;
                    case 105: // int wm_get_subtile_state(int xPos, int yPos)  (0 - unknown, 1 - known, 2 - visited)
                        break;
                    case 106: // ObjectPtr tile_get_next_critter(int tile_num, int elev, ObjectPtr last_critter)
                        break;
                    case 107: // int art_change_fid_num(ObjectPtr who, int fid) - change base FID num for object
                        break;
                    case 108: // void tile_set_center(int tileNum) - center camera on given tile
                    {
                        auto state = Game::Game::getInstance()->locationState();
                        if (state) {
                            state->centerCameraAtHexagon(arg1.integerValue());
                        }
                        break;
                    }
                    default:
                        _error("metarule3 - unknown meta: " + std::to_string(meta));
                        break;
                }
                dataStack->push(result);
            }
        }
    }
}
