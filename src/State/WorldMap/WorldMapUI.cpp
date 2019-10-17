#include "./WorldMap.h"
#include "../../Game/Game.h"
#include "../../Settings.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {

        void WorldMap::initHotspot()
        {
            _hotspot = new UI::ImageButton(UI::ImageButton::Type::MAP_HOTSPOT, 0, 0);
        }

        void WorldMap::initPanel()
        {
            unsigned int renderWidth = Game::getInstance()->renderer()->width();
            unsigned int renderHeight = Game::getInstance()->renderer()->height();
            if (Game::getInstance()->settings()->worldMapFullscreen())
            {
                _panel = new UI::Image(sidePanelSprite);
                fullscreenSidepanelWidth = renderWidth/5;
                mapWidth = renderWidth - fullscreenSidepanelWidth;
                mapHeight = renderHeight;
                mapMinX = 0;
                mapMinY = 0;
            }
            else
            {
                _panel = new UI::Image(fullPanelSprite);
                mapWidth = 450;   // fallout 2 map screen width
                mapHeight = 442;  // fallout 2 map screen height
                mapMinX = (renderWidth - 640)/2 + 22;
                mapMinY = (renderHeight - 480)/2 + 21;
            }
        };

        void WorldMap::renderHotspot()
        {
            _hotspot->setPosition(Point(mapMinX + worldMapX - deltaX, mapMinY + worldMapY - deltaY));
            _hotspot->render();
        }

        void WorldMap::renderPanel()
        {
            unsigned int renderWidth = Game::getInstance()->renderer()->width();
            unsigned int renderHeight = Game::getInstance()->renderer()->height();
            unsigned int panelX;
            unsigned int panelY;
            if (Game::getInstance()->settings()->worldMapFullscreen())
            {
                panelSize = Graphics::Size(fullscreenSidepanelWidth, renderHeight);
                panelX = renderWidth - fullscreenSidepanelWidth;
                panelY = 0;
            }
            else
            {
                panelSize = Graphics::Size(_panel->size().width(), _panel->size().height());
                panelX = (renderWidth - _panel->size().width()) / 2;
                panelY = (renderHeight - _panel->size().height()) / 2;
            }
            _panel->setPosition(Point(panelX, panelY));
            _panel->render(panelSize);
        }
    }
}
