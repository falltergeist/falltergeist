#include "../../VM/Handler/Opcode810BHandler.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Object.h"
#include "../../Game/SceneryObject.h"
#include "../../Game/ElevatorSceneryObject.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../PathFinding/Hexagon.h"
#include "../../State/ElevatorDialog.h"
#include "../../UI/ResourceManager.h"

#define PID_ELEVATOR_STUB (33555725)

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810B::Opcode810B(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode810B::_run()
            {
                logger->debug() << "[810B] [*] int metarule(int type, value)" << std::endl;
                auto value = _script->dataStack()->pop();
                auto type = _script->dataStack()->popInteger();

                int result = 0;
                auto object = (Game::Object*)_script->sourceObject();

                switch (type) {
                    case 14: // METARULE_TEST_FIRSTRUN
                        result = 1;
                        break;
                    case 15: // METARULE_ELEVATOR
                        logger->info() << "[ELEVATOR] metarule value = " << value.toString() << std::endl;

                        if (auto critter = dynamic_cast<Game::CritterObject *>(object)) {
                            logger->info() << "Triggered critter PID = " << critter->PID() << std::endl;

                            bool found = false;
                            for (int i = 1; i < 6; i++) {
                                if (!found) {
                                    auto hexagons = Game::Game::getInstance()->locationState()->hexagonGrid()->ring(critter->hexagon(), i);

                                    for (auto hexagon: hexagons) {
                                        if (!found) {
                                            auto position = hexagon->number();
                                            auto objects = Game::Game::getInstance()->locationState()->hexagonGrid()->at(position)->objects();

                                            for (auto object : *objects) {
                                                if (object->type() == Game::Object::Type::SCENERY && object->PID() == PID_ELEVATOR_STUB) {
                                                    if (auto elevatorStub = dynamic_cast<Game::ElevatorSceneryObject *>(object)) {
                                                        logger->info() << "[ELEVATOR] stub found: type = " << (uint32_t)elevatorStub->elevatorType() << " level = " << (uint32_t)elevatorStub->elevatorLevel() << std::endl;
                                                        found = true;
                                                        auto elevatorDialog = new State::ElevatorDialog(std::make_shared<UI::ResourceManager>(), this->logger, elevatorStub->elevatorType(), elevatorStub->elevatorLevel());
                                                        Game::Game::getInstance()->pushState(elevatorDialog);
                                                    }
                                                }
                                            }        
                                        }
                                    }
                                }
                            }
                        } 

                        result = -1;
                        break;
                    case 16: // METARULE_PARTY_COUNT
                        result = 0;
                        break;
                    case 17: //  METARULE_AREA_KNOWN
                        result = 1;
                        break;
                    case 18: // METARULE_WHO_ON_DRUGS
                        result = 0;
                        break;
                    case 19: // METARULE_MAP_KNOWN
                        result = 1;
                        break;
                    case 22: // METARULE_IS_LOADGAME
                        result = 0;
                        break;
                    case 30: // METARULE_CAR_CURRENT_TOWN
                        result = 0;
                        break;
                    case 40: // METARULE_SKILL_CHECK_TAG
                        result = 0;
                        break;
                    case 44: // METARULE_GET_WORLDMAP_XPOS
                        result = 300;
                        break;
                    case 45: // METARULE_GET_WORLDMAP_YPOS
                        result = 300;
                        break;
                    case 46: // METARULE_CURRENT_TOWN
                        result = 0;
                        break;
                    default:
                        _error("metarule - unimplemented type: " + std::to_string(type));
                }

                _script->dataStack()->push(result);
            }
        }
    }
}
