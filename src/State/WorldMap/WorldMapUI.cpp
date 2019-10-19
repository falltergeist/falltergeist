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
                panelBorder = 0;
                panelX = renderWidth - fullscreenSidepanelWidth;
                panelY = 0;
                panelSize = Graphics::Size(fullscreenSidepanelWidth, renderHeight);
            }
            else
            {
                _panel = new UI::Image(fullPanelSprite);
                mapWidth = 450;   // fallout 2 map screen width
                mapHeight = 442;  // fallout 2 map screen height
                mapMinX = (renderWidth - 640)/2 + panelBorder;
                mapMinY = (renderHeight - 480)/2 + panelBorder;
                panelX = (renderWidth - _panel->size().width()) / 2;
                panelY = (renderHeight - _panel->size().height()) / 2;
                panelSize = Graphics::Size(_panel->size().width(), _panel->size().height());
            }
        };

        void WorldMap::setPanelOffset()
        {
            if (!Game::getInstance()->settings()->worldMapFullscreen()) {
                offsetX = (Game::getInstance()->renderer()->width() - _panel->size().width()) / 2;
                offsetY = (Game::getInstance()->renderer()->height() - _panel->size().height()) / 2;
            }
        };

        void WorldMap::renderHotspot()
        {
            _hotspot->setPosition(Point(mapMinX + worldMapX - deltaX, mapMinY + worldMapY - deltaY));
            _hotspot->render();
        }

        void WorldMap::renderPanel()
        {
            _panel->setPosition(Point(panelX, panelY));
            _panel->render(panelSize);
        }
    }
}
