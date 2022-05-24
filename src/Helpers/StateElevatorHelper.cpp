// Project includes
#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Game/Elevator.h"
#include "../Helpers/StateElevatorHelper.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../Ini/File.h"
#include "../Exception.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Helpers
    {
        StateElevatorHelper::StateElevatorHelper(std::shared_ptr<ILogger>& logger)
            : _logger(logger) {
            auto& vfs = ResourceManager::getInstance()->vfs();
            auto file = vfs->open("data/elevators.txt", VFS::IFile::OpenMode::Read);
            if (!file || !file->isOpened()) {
                throw Exception("Could not open elevators file");
            }

            std::string content;
            content.resize(file->size());
            file->read(content.data(), file->size());
            vfs->close(file);

            std::istringstream contentStream(content);
            auto inifile = new Ini::Parser(contentStream);
            auto ini = inifile->parse();

            for (size_t i = 0; i < ini->sections()->size(); i++) {
                std::string sectionName = "elevator " + std::to_string(i);

                if (ini->hasSection(sectionName)) {

                    auto section = ini->section(sectionName);
                    auto elevator = new Game::Elevator();
                    auto panelArtIdx = -1;
                    auto labelsArtIdx = -1;
                    auto buttonsCount = 0;

                    if (section->hasProperty("panel_art_idx")) {
                        panelArtIdx = section->propertyInt("panel_art_idx", -1);
                        elevator->setPanelFID(panelArtIdx);
                    }

                    if (section->hasProperty("labels_art_idx")) {
                        labelsArtIdx = section->propertyInt("labels_art_idx", -1);
                        elevator->setLabelsFID(labelsArtIdx);
                    }

                    if (section->hasProperty("buttons_count")) {
                        buttonsCount = section->propertyInt("buttons_count", 0);
                        elevator->setSize(buttonsCount);
                    }

                    for (auto i = 0; i < 4; i++) {
                        std::string buttonprop = "button_" + std::to_string(i);
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

                    for (size_t i = 0; i < floors.size(); i++) {
                        auto fl = floors.at(i);
                        _logger->debug() << " loaded elevator: map=" << fl->mapId << " elevation=" << fl->elevation << " position=" << fl->position << std::endl;
                    }
                }
            }
        }

        Game::Elevator* StateElevatorHelper::getByType(uint32_t type) {
            if (type < _elevators.size()) {
                return _elevators.at((size_t)type);
            }
            return nullptr;
        }
    }
}
