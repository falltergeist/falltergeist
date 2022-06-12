// Project includes
#include "../../UI/ImageButton.h"
#include "../../UI/Factory/ImageButtonFactory.h"

// Third-party includes

// stdlib
#include <map>

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            ImageButtonFactory::ImageButtonFactory(std::shared_ptr<IResourceManager> uiResourceManager)
            {
                this->uiResourceManager = uiResourceManager;

                buttonUpSpriteFilenames = std::map<Type, std::string>{
                    {Type::SMALL_RED_CIRCLE, "art/intrface/lilredup.frm"},
                    {Type::BIG_RED_CIRCLE, "art/intrface/bigredup.frm"},
                    {Type::MENU_RED_CIRCLE, "art/intrface/menuup.frm"},
                    {Type::ELEVATOR_CIRCLE, "art/intrface/ebut_out.frm"},
                    {Type::SKILL_TOGGLE, "art/intrface/tgskloff.frm"},
                    {Type::PLUS, "art/intrface/splsoff.frm"},
                    {Type::MINUS, "art/intrface/snegoff.frm"},
                    {Type::LEFT_ARROW, "art/intrface/slu.frm"},
                    {Type::RIGHT_ARROW, "art/intrface/sru.frm"},
                    {Type::CHECKBOX, "art/intrface/prfxout.frm"},
                    {Type::PLAYER_NAME, "art/intrface/nameoff.frm"},
                    {Type::PLAYER_AGE, "art/intrface/ageoff.frm"},
                    {Type::PLAYER_GENDER, "art/intrface/sexoff.frm"},
                    {Type::PANEL_INVENTORY, "art/intrface/invbutup.frm"},
                    {Type::PANEL_OPTIONS, "art/intrface/optiup.frm"},
                    {Type::PANEL_ATTACK, "art/intrface/sattkbup.frm"},
                    {Type::PANEL_MAP, "art/intrface/mapup.frm"},
                    {Type::PANEL_CHA, "art/intrface/chaup.frm"},
                    {Type::PANEL_PIP, "art/intrface/pipup.frm"},
                    {Type::OPTIONS_BUTTON, "art/intrface/opbtnoff.frm"},
                    {Type::SKILLDEX_BUTTON, "art/intrface/skldxoff.frm"},
                    {Type::INVENTORY_UP_ARROW, "art/intrface/invupout.frm"},
                    {Type::INVENTORY_DOWN_ARROW, "art/intrface/invdnout.frm"},
                    {Type::INVENTORY_TAKE_ALL, "art/intrface/invmaup.frm"},
                    {Type::PIPBOY_ALARM_BUTTON, "art/intrface/alarmout.frm"},
                    {Type::DIALOG_RED_BUTTON, "art/intrface/di_rdbt2.frm"},
                    {Type::DIALOG_REVIEW_BUTTON, "art/intrface/di_rest1.frm"},
                    {Type::DIALOG_DONE_BUTTON, "art/intrface/di_done1.frm"},
                    {Type::DIALOG_BIG_UP_ARROW, "art/intrface/di_bgup1.frm"},
                    {Type::DIALOG_BIG_DOWN_ARROW, "art/intrface/di_bgdn1.frm"},
                    {Type::DIALOG_UP_ARROW, "art/intrface/di_up1.frm"},
                    {Type::DIALOG_DOWN_ARROW, "art/intrface/di_down1.frm"},
                    {Type::SMALL_UP_ARROW, "art/intrface/uparwoff.frm"},
                    {Type::SMALL_DOWN_ARROW, "art/intrface/dnarwoff.frm"},
                    {Type::MAP_HOTSPOT, "art/intrface/hotspot1.frm"},
                };

                buttonDownSpriteFilenames = std::map<Type, std::string>{
                    {Type::SMALL_RED_CIRCLE, "art/intrface/lilreddn.frm"},
                    {Type::BIG_RED_CIRCLE, "art/intrface/bigreddn.frm"},
                    {Type::MENU_RED_CIRCLE, "art/intrface/menudown.frm"},
                    {Type::ELEVATOR_CIRCLE, "art/intrface/ebut_in.frm"},
                    {Type::SKILL_TOGGLE, "art/intrface/tgsklon.frm"},
                    {Type::PLUS, "art/intrface/splson.frm"},
                    {Type::MINUS, "art/intrface/snegon.frm"},
                    {Type::LEFT_ARROW, "art/intrface/sld.frm"},
                    {Type::RIGHT_ARROW, "art/intrface/srd.frm"},
                    {Type::CHECKBOX, "art/intrface/prfxin.frm"},
                    {Type::PLAYER_NAME, "art/intrface/nameon.frm"},
                    {Type::PLAYER_AGE, "art/intrface/ageon.frm"},
                    {Type::PLAYER_GENDER, "art/intrface/sexon.frm"},
                    {Type::PANEL_INVENTORY, "art/intrface/invbutdn.frm"},
                    {Type::PANEL_OPTIONS, "art/intrface/optidn.frm"},
                    {Type::PANEL_ATTACK, "art/intrface/sattkbdn.frm"},
                    {Type::PANEL_MAP, "art/intrface/mapdn.frm"},
                    {Type::PANEL_CHA, "art/intrface/chadn.frm"},
                    {Type::PANEL_PIP, "art/intrface/pipdn.frm"},
                    {Type::OPTIONS_BUTTON, "art/intrface/opbtnon.frm"},
                    {Type::SKILLDEX_BUTTON, "art/intrface/skldxon.frm"},
                    {Type::INVENTORY_UP_ARROW, "art/intrface/invupin.frm"},
                    {Type::INVENTORY_DOWN_ARROW, "art/intrface/invdnin.frm"},
                    {Type::INVENTORY_TAKE_ALL, "art/intrface/invmadn.frm"},
                    {Type::PIPBOY_ALARM_BUTTON, "art/intrface/alarmin.frm"},
                    {Type::DIALOG_RED_BUTTON, "art/intrface/di_rdbt1.frm"},
                    {Type::DIALOG_REVIEW_BUTTON, "art/intrface/di_rest2.frm"},
                    {Type::DIALOG_DONE_BUTTON, "art/intrface/di_done2.frm"},
                    {Type::DIALOG_BIG_UP_ARROW, "art/intrface/di_bgup2.frm"},
                    {Type::DIALOG_BIG_DOWN_ARROW, "art/intrface/di_bgdn2.frm"},
                    {Type::DIALOG_UP_ARROW, "art/intrface/di_up2.frm"},
                    {Type::DIALOG_DOWN_ARROW, "art/intrface/di_down2.frm"},
                    {Type::SMALL_UP_ARROW, "art/intrface/uparwon.frm"},
                    {Type::SMALL_DOWN_ARROW, "art/intrface/dnarwon.frm"},
                    {Type::MAP_HOTSPOT, "art/intrface/hotspot2.frm"},
                };

                buttonDownSoundFilenames = std::map<Type, std::string>{
                    {Type::SMALL_RED_CIRCLE, "sound/sfx/ib1p1xx1.acm"},
                    {Type::BIG_RED_CIRCLE, "sound/sfx/ib2p1xx1.acm"},
                    {Type::MENU_RED_CIRCLE, "sound/sfx/nmselec0.acm"},
                    {Type::ELEVATOR_CIRCLE, "sound/sfx/ib1p1xx1.acm"},
                    {Type::LEFT_ARROW, "sound/sfx/ib2p1xx1.acm"},
                    {Type::RIGHT_ARROW, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_INVENTORY, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_OPTIONS, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_ATTACK, "sound/sfx/ib3p1xx1.acm"},
                    {Type::PANEL_MAP, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_CHA, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_PIP, "sound/sfx/ib2p1xx1.acm"},
                    {Type::OPTIONS_BUTTON, "sound/sfx/ib3p1xx1.acm"},
                    {Type::SKILLDEX_BUTTON, "sound/sfx/ib2lu1x1.acm"},
                    {Type::INVENTORY_UP_ARROW, "sound/sfx/ib1p1xx1.acm"},
                    {Type::INVENTORY_DOWN_ARROW, "sound/sfx/ib1p1xx1.acm"},
                    {Type::INVENTORY_TAKE_ALL, "sound/sfx/ib1p1xx1.acm"},
                    {Type::DIALOG_RED_BUTTON, "sound/sfx/ib2p1xx1.acm"},
                    {Type::DIALOG_UP_ARROW, "sound/sfx/ib1p1xx1.acm"},
                    {Type::DIALOG_DOWN_ARROW, "sound/sfx/ib1p1xx1.acm"},
                };

                buttonUpSoundFilenames = std::map<Type, std::string>{
                    {Type::SMALL_RED_CIRCLE, "sound/sfx/ib1lu1x1.acm"},
                    {Type::BIG_RED_CIRCLE, "sound/sfx/ib2lu1x1.acm"},
                    {Type::MENU_RED_CIRCLE, "sound/sfx/nmselec1.acm"},
                    {Type::ELEVATOR_CIRCLE, "sound/sfx/ib1lu1x1.acm"},
                    {Type::LEFT_ARROW, "sound/sfx/ib2lu1x1.acm"},
                    {Type::RIGHT_ARROW, "sound/sfx/ib2lu1x1.acm"},
                    {Type::CHECKBOX, "sound/sfx/ib2p1xx1.acm"},
                    {Type::PANEL_INVENTORY, "sound/sfx/ib2lu1x1.acm"},
                    {Type::PANEL_OPTIONS, "sound/sfx/ib2lu1x1.acm"},
                    {Type::PANEL_ATTACK, "sound/sfx/ib3lu1x1.acm"},
                    {Type::PANEL_MAP, "sound/sfx/ib2lu1x1.acm"},
                    {Type::PANEL_CHA, "sound/sfx/ib2lu1x1.acm"},
                    {Type::PANEL_PIP, "sound/sfx/ib2lu1x1.acm"},
                    {Type::OPTIONS_BUTTON, "sound/sfx/ib3lu1x1.acm"},
                    {Type::SKILLDEX_BUTTON, "sound/sfx/ib1p1xx1.acm"},
                    {Type::INVENTORY_UP_ARROW, "sound/sfx/ib1lu1x1.acm"},
                    {Type::INVENTORY_DOWN_ARROW, "sound/sfx/ib1lu1x1.acm"},
                    {Type::INVENTORY_TAKE_ALL, "sound/sfx/ib1lu1x1.acm"},
                    {Type::DIALOG_RED_BUTTON, "sound/sfx/ib2lu1x1.acm"},
                    {Type::DIALOG_UP_ARROW, "sound/sfx/ib1lu1x1.acm"},
                    {Type::DIALOG_DOWN_ARROW, "sound/sfx/ib1lu1x1.acm"},
                };
            }

            std::shared_ptr<ImageButton> ImageButtonFactory::getByType(Type type, const Graphics::Point &position)
            {
                auto buttonUpSprite = uiResourceManager->getSprite(buttonUpSpriteFilenames.at(type));
                auto buttonDownSprite = uiResourceManager->getSprite(buttonDownSpriteFilenames.at(type));

                std::string buttonDownSoundFilename;
                if (buttonDownSoundFilenames.find(type) != buttonDownSoundFilenames.end()) {
                    buttonDownSoundFilename = buttonDownSoundFilenames.at(type);
                }

                std::string buttonUpSoundFilename;
                if (buttonUpSoundFilenames.find(type) != buttonUpSoundFilenames.end()) {
                    buttonUpSoundFilename = buttonUpSoundFilenames.at(type);
                }

                bool checkboxMode = (type == Type::CHECKBOX);

                return std::make_shared<ImageButton>(
                    position,
                    buttonUpSprite,
                    buttonDownSprite,
                    buttonUpSoundFilename,
                    buttonDownSoundFilename,
                    checkboxMode
                );
            }
        }
    }
}
