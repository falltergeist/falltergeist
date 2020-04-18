#pragma once

#include "../../Graphics/Point.h"
#include "../../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        class ImageButton;

        namespace Factory
        {
            class ImageButtonFactory final
            {
                public:
                    enum class Type
                    {
                        SMALL_RED_CIRCLE = 1,
                        BIG_RED_CIRCLE,
                        MENU_RED_CIRCLE,
                        SKILL_TOGGLE,
                        PLUS,
                        MINUS,
                        LEFT_ARROW,
                        RIGHT_ARROW,
                        CHECKBOX,
                        PLAYER_NAME,
                        PLAYER_AGE,
                        PLAYER_GENDER,
                        PANEL_INVENTORY,
                        PANEL_OPTIONS,
                        PANEL_ATTACK,
                        PANEL_MAP,
                        PANEL_CHA,
                        PANEL_PIP,
                        OPTIONS_BUTTON,
                        SKILLDEX_BUTTON,
                        INVENTORY_UP_ARROW,
                        INVENTORY_DOWN_ARROW,
                        INVENTORY_TAKE_ALL,
                        PIPBOY_ALARM_BUTTON,
                        DIALOG_RED_BUTTON,
                        DIALOG_REVIEW_BUTTON,
                        DIALOG_DONE_BUTTON,
                        DIALOG_BIG_UP_ARROW,
                        DIALOG_BIG_DOWN_ARROW,
                        DIALOG_UP_ARROW,
                        DIALOG_DOWN_ARROW,
                        SMALL_UP_ARROW,
                        SMALL_DOWN_ARROW,
                        MAP_HOTSPOT
                    };

                    ImageButtonFactory(std::shared_ptr<IResourceManager> uiResourceManager);

                    std::unique_ptr<ImageButton> getByType(Type type, const Graphics::Point &position);

                private:
                    std::shared_ptr<IResourceManager> uiResourceManager;
                    std::map<Type, std::string> buttonUpSpriteFilenames;
                    std::map<Type, std::string> buttonDownSpriteFilenames;
                    std::map<Type, std::string> buttonDownSoundFilenames;
                    std::map<Type, std::string> buttonUpSoundFilenames;
            };
        }
    }
}
