#pragma once

#include "../Graphics/Sprite.h"
#include "../UI/Base.h"
#include "../UI/Animation.h"
#include "../UI/ImageButton.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
    }
    namespace UI
    {


        namespace Factory
        {
            class ImageButtonFactory;
        }

        class Image;

        class CombatPanel : public UI::Base
        {
            public:

                enum CombatMode
                {
                    ENEMY_TURN = 0,
                    PLAYER_TURN,
                };

                CombatPanel(const Point& pos = Point(0, 0));
                CombatPanel(bool enabled, const Point& pos = Point(0, 0));

                CombatPanel::CombatMode mode() const;
                void setMode(CombatPanel::CombatMode mode);
                bool activated();
                void setActivated(bool activated);
                void handle(Event::Event *event) override;
                void think(const float &deltaTime) override;
                bool opaque(const Point &pos) override;
                void render(bool eggTransparency) override;
                std::shared_ptr<UI::ImageButton> _btnEndTurn;
                std::shared_ptr<UI::ImageButton> _btnEndCombat;

            protected:
                CombatPanel::CombatMode _mode;
                Size _size;
                bool _enabled;
                std::shared_ptr<Graphics::Sprite> _playerTurnSprite;
                std::shared_ptr<Graphics::Sprite> _enemyTurnSprite;
                std::vector<SDL_Rect> _rects;
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
                std::shared_ptr<UI::Animation> _panelAnimation;
        };
    }
}
