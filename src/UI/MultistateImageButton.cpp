#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Texture.h"
#include "../UI/Image.h"
#include "../UI/MultistateImageButton.h"

namespace Falltergeist
{
    using namespace std;

    namespace UI
    {
        MultistateImageButton::MultistateImageButton(Type type, const Point& pos) : Falltergeist::UI::Base(pos)
        {
            mouseClickHandler() += std::bind(&MultistateImageButton::_onMouseClick, this, std::placeholders::_1);
            mouseUpHandler().add(std::bind(&MultistateImageButton::_onMouseUp, this, std::placeholders::_1));
            switch (type)
            {
                case Type::BIG_SWITCH:
                {
                    _sprite = make_shared<Graphics::Sprite>("art/intrface/prfbknbs.frm");
                    _rects.emplace_back(Point(0,0*47), Size(46,47));
                    _rects.emplace_back(Point(0,1*47), Size(46,47));
                    _rects.emplace_back(Point(0,2*47), Size(46,47));
                    _rects.emplace_back(Point(0,3*47), Size(46,47));
                    _maxState = 4;
                    _size = Size(46,47);

                    _downSound = "sound/sfx/ib3p1xx1.acm";
                    _upSound = "sound/sfx/ib3lu1x1.acm";
                    break;
                }
                case Type::SMALL_SWITCH:
                {
                    _sprite = make_shared<Graphics::Sprite>("art/intrface/prflknbs.frm");
                    _rects.emplace_back(Point(0,0*25), Size(22,25));
                    _rects.emplace_back(Point(0,1*25), Size(22,25));
                    _maxState = 2;
                    _size = Size(22,25);

                    _downSound = "sound/sfx/ib2p1xx1.acm";
                    _upSound = "sound/sfx/ib2lu1x1.acm";
                    break;
                }
                default:
                    throw Exception("MultistateImageButton::MultistateImageButton(unsigned int type, x, y) - unsupported type");
            }
        }

        unsigned int MultistateImageButton::state() const
        {
            return _currentState;
        }

        void MultistateImageButton::setState(unsigned int state)
        {
            _currentState = state;
        }

        void MultistateImageButton::setMode(Mode mode)
        {
            _mode = mode;
        }

        MultistateImageButton::Mode MultistateImageButton::mode() const
        {
            return _mode;
        }

        void MultistateImageButton::_onMouseClick(Event::Mouse* event)
        {
            auto sender = dynamic_cast<MultistateImageButton*>(event->target());

            if (sender->mode() == Mode::PROGRESSION) {
                if (sender->modeFactor() > 0) {
                    sender->_currentState = (sender->_currentState < sender->_maxState - 1) ? sender->_currentState + sender->modeFactor() : 0;
                } else {
                    sender->_currentState = (sender->_currentState > 0) ? sender->_currentState + sender->modeFactor() : sender->_maxState - 1;
                }
            } else { // Mode::CYCLIC
                if (sender->modeFactor() > 0) {
                    if (sender->_currentState == sender->_maxState - 1) {
                        sender->setModeFactor(-sender->modeFactor());
                    }
                } else {
                    if (sender->_currentState == 0) {
                        sender->setModeFactor(-sender->modeFactor());
                    }
                }
                sender->_currentState += sender->modeFactor();
            }
        }

        void MultistateImageButton::_onMouseUp(Event::Mouse* event)
        {
            if (!event->leftButton()) {
                return;
            }

            auto sender = dynamic_cast<MultistateImageButton*>(event->target());

            if (!sender->_downSound.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(sender->_downSound);
            }
            if (!sender->_upSound.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(sender->_upSound);
            }
        }

        void MultistateImageButton::setModeFactor(int factor)
        {
            _modeFactor = factor;
        }

        int MultistateImageButton::modeFactor() const
        {
            if (_modeFactor >= 0) {
                return 1;
            }
            return -1;
        }

        void MultistateImageButton::setMaxState(unsigned int value)
        {
            _maxState = value;
            if (_currentState > _maxState) {
                _currentState = _maxState;
            }
        }

        unsigned int MultistateImageButton::maxState() const
        {
            return _maxState;
        }

        void MultistateImageButton::setMinState(unsigned int value)
        {
            _minState = value;
            if (_currentState < _minState) {
                _currentState = _minState;
            }
        }

        unsigned int MultistateImageButton::minState() const
        {
            return _minState;
        }

        void MultistateImageButton::handle(Event::Mouse* mouseEvent)
        {
            // disable right button clicks
            _rightButtonPressed = false;
            Base::handle(mouseEvent);
        }

        void MultistateImageButton::render(bool eggTransparency)
        {
            _sprite->renderCropped(position(), _rects.at(_currentState));
        }

        bool MultistateImageButton::opaque(const Point &pos)
        {
            if (pos.x() > _size.width() || pos.x()<0 || pos.y() > _size.height() || pos.y()<0) {
                return false;
            }

            return _sprite->opaque(_rects.at(_currentState).position() + pos);
        }

        Size MultistateImageButton::size() const
        {
            return _size;
        }
    }
}
