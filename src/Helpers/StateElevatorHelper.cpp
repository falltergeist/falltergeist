#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Game/Elevator.h"
#include "../Helpers/StateElevatorHelper.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../Format/Dat/MiscFile.h"
#include "../Ini/File.h"
#include "../Ini/Parser.h"

namespace Falltergeist
{
    namespace Helpers
    {
        StateElevatorHelper::StateElevatorHelper(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);

            auto elevatorscfg = ResourceManager::getInstance()->miscFileType("data/elevators.txt");

            elevatorscfg->stream().setPosition(0);
            std::istream str(&elevatorscfg->stream());
            auto inifile = new Ini::Parser(str);
            auto ini = inifile->parse();

            for (auto i = 0; i < ini->sections()->size(); i++) {
                std::string sectionName = "elevator " + std::to_string(i);

                if (ini->hasSection(sectionName)) {

                    auto section = ini->section(sectionName);
                    auto elevator = new Game::Elevator();
                    auto panelArtIdx = -1;
                    auto labelsArtIdx = -1;
                    auto buttonsCount = 0;

                    Logger::info("") << "section=" << sectionName << std::endl;

                    if (section->hasProperty("panel_art_idx")) {
                        panelArtIdx = section->propertyInt("panel_art_idx", -1);
                        Logger::info("") << "panel_art_idx=" << panelArtIdx << std::endl;
                        elevator->setPanelFID(panelArtIdx);
                    }

                    if (section->hasProperty("labels_art_idx")) {
                        labelsArtIdx = section->propertyInt("labels_art_idx", -1);
                        Logger::info("") << "labels_art_idx=" << labelsArtIdx << std::endl;
                        elevator->setLabelsFID(labelsArtIdx);
                    }

                    if (section->hasProperty("buttons_count")) {
                        buttonsCount = section->propertyInt("buttons_count", 0);
                        Logger::info("") << "buttons_count=" << buttonsCount << std::endl;
                        elevator->setSize(buttonsCount);
                    }

                    for (auto i = 0; i < 4; i++) {
                        std::string buttonprop = "button_" + std::to_string(i);
                         Logger::info("") << "buttonprop=" << buttonprop << std::endl;
                        if (section->hasProperty(buttonprop)) {
                            auto buttonparams = section->propertyArray(buttonprop);

                            if (buttonparams.size() == 3) {
                                auto floor = new Game::ElevatorFloor;

                                floor->mapId = buttonparams[0].intValue();
                                floor->elevation = buttonparams[1].intValue();
                                floor->position = buttonparams[2].intValue();
                                elevator->addFloor(floor);
                            }

                            
                        }
                    }

                    _elevators.push_back(elevator);


                    auto floors = elevator->floors();

                    Logger::info("") << "size=" << floors.size() << std::endl;
                    for (auto i = 0; i < floors.size(); i++) {
                        auto fl = floors.at(i);
                        Logger::info("") << "loaded elevator: map=" << fl->mapId << " elevation=" << fl->elevation << " position=" << fl->position << std::endl;
                    }

                }

                
                
            }

        }

        Game::Elevator* StateElevatorHelper::getByType(uint32_t type)
        {
            if (type < _elevators.size()) {
                return _elevators.at((size_t)type);
            }
            return nullptr;
        }
    }
}
