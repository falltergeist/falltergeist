#include "../UI/CombatPanel.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/ImageButton.h"
#include "../UI/ResourceManager.h"
#include "../UI/Base.h"
#include "../UI/Animation.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Event/Keyboard.h"
#include "../Input/Mouse.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Audio/Mixer.h"

namespace Falltergeist
{
    using namespace std;
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace UI
    {
        CombatPanel::CombatPanel(bool enabled, const Point& pos) : Base(pos), _enabled(false)
        {
            _playerTurnSprite = make_shared<Graphics::Sprite>("art/intrface/endltgrn.frm");
            _enemyTurnSprite = make_shared<Graphics::Sprite>("art/intrface/endltred.frm");
            
            resourceManager = std::make_shared<UI::ResourceManager>();
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);

            _panelAnimation = std::shared_ptr<Animation>(new Animation("art/intrface/endanim.frm", 0));
            _panelAnimation->setPosition(position());
            _panelAnimation->animationEndedHandler().add([this](Event::Event* event){
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/icombat2.acm");
                _btnEndTurn->setEnabled(true);
                _btnEndCombat->setEnabled(true);
            });

            _btnEndTurn = std::shared_ptr<ImageButton>(imageButtonFactory->getByType(ImageButtonType::PANEL_END_TURN, position() + Point(11, 6)));
            _btnEndTurn->setEnabled(false);

            
            _btnEndCombat = std::shared_ptr<ImageButton>(imageButtonFactory->getByType(ImageButtonType::PANEL_END_COMBAT, position() + Point(11, 28)));
            _btnEndCombat->setEnabled(false);
        }

        CombatPanel::CombatPanel(const Point& pos) : CombatPanel(false, pos)
        {
        }

        void CombatPanel::handle(Event::Event *event)
        {

            UI::Base::handle(event);
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                mouseEvent->setObstacle(false);
                mouseEvent->setHandled(false);

                if (event->handled()) {
                    return;
                }

                if (activated()) {
                    _btnEndTurn->handle(dynamic_cast<Event::Mouse*>(event));
                    _btnEndCombat->handle(dynamic_cast<Event::Mouse*>(event));
                }
            }

        }


        bool CombatPanel::activated()
        {
            return _enabled;
        }

        void CombatPanel::setActivated(bool activated)
        {
            if (_enabled == activated) return;
            _enabled = activated;
            _panelAnimation->setReverse(!activated);
            _panelAnimation->play();
            if (activated == false) {
                _btnEndTurn->setEnabled(false);
                _btnEndCombat->setEnabled(false);
            }
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/iciboxx1.acm");
        }

        void CombatPanel::think(const float &deltaTime)
        {
            UI::Base::think(deltaTime);
            _panelAnimation->think(deltaTime);
            _btnEndTurn->think(deltaTime);
            _btnEndCombat->think(deltaTime);
        }

        CombatPanel::CombatMode CombatPanel::mode() const
        {
            return _mode;
        }

        void CombatPanel::setMode(CombatPanel::CombatMode mode)
        {
            _mode = mode;
        }

        bool CombatPanel::opaque(const Point &pos)
        {
            if (pos.x() > _size.width() || pos.x()<0 || pos.y() > _size.height() || pos.y()<0) {
                return false;
            }
            return _panelAnimation->opaque(pos);
        }

        void CombatPanel::render(bool eggTransparency)
        {
            _panelAnimation->render();

            if (activated() && _panelAnimation->currentFrame() == 4) {

                if (_mode == CombatMode::ENEMY_TURN) {
                    _enemyTurnSprite->render(position().x(), position().y(), true, false, 0, 0);
                } else if (_mode == CombatMode::PLAYER_TURN) {
                    _playerTurnSprite->render(position().x(), position().y(), true, false, 0, 0);
                }
                _btnEndTurn->render(eggTransparency);
                _btnEndCombat->render(eggTransparency);
            }
        }
    }
}
