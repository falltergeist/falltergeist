#include <memory>
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"
#include <SDL.h>

namespace Falltergeist
{
    namespace Input
    {
        Mouse::Mouse(std::shared_ptr<UI::IResourceManager> resourceManager)
        {
            this->resourceManager = resourceManager;
            SDL_ShowCursor(0); // Hide cursor
        }

        Mouse::~Mouse()
        {
            SDL_ShowCursor(1); // Show cursor
        }

        int Mouse::x() const
        {
            return _position.x();
        }

        int Mouse::y() const
        {
            return _position.y();
        }

        void Mouse::setX(int x)
        {
            setPosition({x, _position.y()});
        }

        void Mouse::setY(int y)
        {
            setPosition({_position.x(), y});
        }

        const Point& Mouse::position() const
        {
            return _position;
        }

        void Mouse::setPosition(const Point& pos)
        {
            _position = pos;
            auto renderer = Game::getInstance()->renderer();
            float scaleX = renderer->scaleX();
            float scaleY = renderer->scaleY();
            SDL_WarpMouseInWindow(renderer->sdlWindow(), (int)(pos.x() * scaleX), (int)(pos.y() * scaleY));
        }

        void Mouse::setState(Cursor state)
        {
            _states.clear();
            pushState(state);
        }

        void Mouse::popState()
        {
            if (_states.size() == 0) {
                return;
            }
            if (_states.size() == 1) {
                _setType(Cursor::NONE);
            } else {
                _setType(_states.at(_states.size() - 2));
            }
            _states.pop_back();
        }

        void Mouse::pushState(Cursor state)
        {
            _setType(state);
            _states.push_back(state);
        }

        Mouse::Cursor Mouse::state() const
        {
            if (_states.empty()) {
                return Cursor::NONE;
            }
            return _states.back();
        }

        void Mouse::_setType(Cursor state)
        {
            if (this->state() == state) {
                return;
            }

            _ui = nullptr;

            switch (state)
            {
                case Cursor::BIG_ARROW:
                    _ui = resourceManager->getImage("art/intrface/stdarrow.frm");
                    break;
                case Cursor::SCROLL_W:
                    _ui = resourceManager->getImage("art/intrface/scrwest.frm");
                    _ui->setOffset(0, -_ui->size().height() / 2);
                    break;
                case Cursor::SCROLL_W_X:
                    _ui = resourceManager->getImage("art/intrface/scrwx.frm");
                    _ui->setOffset(0, -_ui->size().height() / 2);
                    break;
                case Cursor::SCROLL_N:
                    _ui = resourceManager->getImage("art/intrface/scrnorth.frm");
                    _ui->setOffset( -_ui->size().width() / 2, 0);
                    break;
                case Cursor::SCROLL_N_X:
                    _ui = resourceManager->getImage("art/intrface/scrnx.frm");
                    _ui->setOffset( -_ui->size().width() / 2, 0);
                    break;
                case Cursor::SCROLL_S:
                    _ui = resourceManager->getImage("art/intrface/scrsouth.frm");
                    _ui->setOffset( -_ui->size().width() / 2, -_ui->size().height());
                    break;
                case Cursor::SCROLL_S_X:
                    _ui = resourceManager->getImage("art/intrface/scrsx.frm");
                    _ui->setOffset(-_ui->size().width() / 2, -_ui->size().height());
                    break;
                case Cursor::SCROLL_E:
                    _ui = resourceManager->getImage("art/intrface/screast.frm");
                    _ui->setOffset( -_ui->size().width(), -_ui->size().height() / 2);
                    break;
                case Cursor::SCROLL_E_X:
                    _ui = resourceManager->getImage("art/intrface/screx.frm");
                    _ui->setOffset(-_ui->size().width(), -_ui->size().height() / 2);
                    break;
                case Cursor::SCROLL_NW:
                    _ui = resourceManager->getImage("art/intrface/scrnwest.frm");
                    break;
                case Cursor::SCROLL_NW_X:
                    _ui = resourceManager->getImage("art/intrface/scrnwx.frm");
                    break;
                case Cursor::SCROLL_SW:
                    _ui = resourceManager->getImage("art/intrface/scrswest.frm");
                    _ui->setOffset(0, -_ui->size().height());
                    break;
                case Cursor::SCROLL_SW_X:
                    _ui = resourceManager->getImage("art/intrface/scrswx.frm");
                    _ui->setOffset(0, -_ui->size().height());
                    break;
                case Cursor::SCROLL_NE:
                    _ui = resourceManager->getImage("art/intrface/scrneast.frm");
                    _ui->setOffset(-_ui->size().width(), 0);
                    break;
                case Cursor::SCROLL_NE_X:
                    _ui = resourceManager->getImage("art/intrface/scrnex.frm");
                    _ui->setOffset(-_ui->size().width(), 0);
                    break;
                case Cursor::SCROLL_SE:
                    _ui = resourceManager->getImage("art/intrface/scrseast.frm");
                    _ui->setOffset(-_ui->size().width(), -_ui->size().height());
                    break;
                case Cursor::SCROLL_SE_X:
                    _ui = resourceManager->getImage("art/intrface/scrsex.frm");
                    _ui->setOffset(-_ui->size().width(), -_ui->size().height());
                    break;
                case Cursor::HEXAGON_RED:
                    _ui = resourceManager->getImage("art/intrface/msef000.frm");
                    _ui->setOffset(- _ui->size().width() / 2, - _ui->size().height() / 2);
                    break;
                case Cursor::ACTION:
                    _ui = resourceManager->getImage("art/intrface/actarrow.frm");
                    break;
                case Cursor::HAND:
                    _ui = resourceManager->getImage("art/intrface/hand.frm");
                    break;
                case Cursor::SMALL_DOWN_ARROW:
                    _ui = resourceManager->getImage("art/intrface/sdnarrow.frm");
                    _ui->setOffset(-5, -10);
                    break;
                case Cursor::SMALL_UP_ARROW:
                    _ui = resourceManager->getImage("art/intrface/suparrow.frm");
                    _ui->setOffset(-5, 0);
                    break;
                case Cursor::WAIT:
                {
                    auto queue = std::make_unique<UI::AnimationQueue>();
                    queue->animations().push_back(std::make_unique<UI::Animation>("art/intrface/wait.frm"));
                    queue->setRepeat(true);
                    queue->start();
                    _ui = std::move(queue);
                    _ui->setOffset(Point() - _ui->size() / 2);
                    break;
                }
                case Cursor::USE:
                {
                    _ui = resourceManager->getImage("art/intrface/crossuse.frm");
                    _ui->setOffset(-10, -10);
                    break;
                }
                case Cursor::NONE:
                    break;
                default:
                    break;
            }
        }

        void Mouse::render()
        {
            if (state() == Cursor::NONE) {
                return;
            }

            if (_ui) {
                if (state() != Cursor::HEXAGON_RED) {
                    _ui->setPosition(position());
                }
                _ui->render();
            }
        }

        void Mouse::think(const float &deltaTime)
        {
            SDL_GetMouseState(&_position.rx(), &_position.ry());
            _position = Point(
                static_cast<int>(_position.x() / Game::getInstance()->renderer()->scaleX()),
                static_cast<int>(_position.y() / Game::getInstance()->renderer()->scaleY())
            );
            if (_ui) {
                _ui->think(deltaTime);
            }
        }

        bool Mouse::scrollState()
        {
            switch(this->state())
            {
                case Cursor::SCROLL_W:
                case Cursor::SCROLL_N:
                case Cursor::SCROLL_E:
                case Cursor::SCROLL_S:
                case Cursor::SCROLL_W_X:
                case Cursor::SCROLL_NW:
                case Cursor::SCROLL_NW_X:
                case Cursor::SCROLL_N_X:
                case Cursor::SCROLL_NE:
                case Cursor::SCROLL_NE_X:
                case Cursor::SCROLL_E_X:
                case Cursor::SCROLL_SE:
                case Cursor::SCROLL_SE_X:
                case Cursor::SCROLL_S_X:
                case Cursor::SCROLL_SW:
                case Cursor::SCROLL_SW_X:
                    return true;
                default:
                    return false;
            }
        }

        UI::Base* Mouse::ui()
        {
            return _ui.get();
        }

        std::vector<Mouse::Cursor>* Mouse::states()
        {
            return &_states;
        }

        void Mouse::renderOutline()
        {
            if (state() == Cursor::NONE) {
                return;
            }

            if (_ui) {
                if (state() != Cursor::HEXAGON_RED) {
                    _ui->setPosition(position());
                }
                _ui->setOutline(1);
                _ui->render();
                _ui->setOutline(0);
            }
        }
    }
}
