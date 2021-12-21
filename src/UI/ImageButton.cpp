#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../ResourceManager.h"
#include "../UI/ImageButton.h"

namespace Falltergeist
{
    using namespace std;

    namespace UI
    {
        ImageButton::ImageButton(
            const Point &pos,
            std::shared_ptr<Graphics::Sprite> buttonUpSprite,
            std::shared_ptr<Graphics::Sprite> buttonDownSprite,
            std::string buttonUpSoundFilename,
            std::string buttonDownSoundFilename,
            bool checkBoxMode
        ) : Base(pos)
        {
            this->buttonUpSprite = std::move(buttonUpSprite);
            this->buttonDownSprite = std::move(buttonDownSprite);
            this->buttonUpSoundFilename = std::move(buttonUpSoundFilename);
            this->buttonDownSoundFilename = std::move(buttonDownSoundFilename);
            this->checkboxMode = checkBoxMode;

            mouseClickHandler().add(std::bind(&ImageButton::_onMouseClick, this, std::placeholders::_1));
            mouseDownHandler().add(std::bind(&ImageButton::_onMouseDown, this, std::placeholders::_1));
            mouseOutHandler().add(std::bind(&ImageButton::_onMouseOut, this, std::placeholders::_1));
        }

        void ImageButton::_onMouseClick(Event::Mouse* event)
        {
            if(!_enabled) {
                return;
            }
            auto sender = dynamic_cast<ImageButton*>(event->target());
            if (sender->checkboxMode) {
                sender->_checked = !sender->_checked;
            }
            if (!sender->buttonUpSoundFilename.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(sender->buttonUpSoundFilename);
            }
        }

        void ImageButton::_onMouseDown(Event::Mouse* event)
        {
            if (!event->leftButton() || !_enabled) {
                return;
            }

            auto sender = dynamic_cast<ImageButton*>(event->target());
            if (!sender->buttonDownSoundFilename.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(sender->buttonDownSoundFilename);
            }
        }


        void ImageButton::_onMouseOut(Event::Mouse* event)
        {
        //    if(!_enabled) return;
        //    auto sender = dynamic_cast<ImageButton*>(event->target());
        //    if (_leftButtonPressed && !sender->buttonUpSoundFilename.empty())
        //    {
        //        Game::getInstance()->mixer()->playACMSound(sender->buttonUpSoundFilename);
        //    }
        }


        bool ImageButton::checked()
        {
            return _checked;
        }

        void ImageButton::setChecked(bool checked)
        {
            _checked = checked;
        }

        bool ImageButton::enabled()
        {
            return _enabled;
        }

        void ImageButton::setEnabled(bool enabled)
        {
            _enabled = enabled;
        }

        void ImageButton::handle(Event::Mouse* mouseEvent)
        {
            if (!_enabled) {
                return;
            }
            // disable right button clicks
            _rightButtonPressed = false;
            Base::handle(mouseEvent);
        }

        void ImageButton::render(bool eggTransparency)
        {
            if(!_enabled) {
                return;
            }
            if ((checkboxMode && _checked) || (_leftButtonPressed)) {
                buttonDownSprite->render(position());
                return;
            }

            buttonUpSprite->render(position());
        }

        bool ImageButton::opaque(const Point &pos)
        {
            if ((checkboxMode && _checked) || (_hovered && _leftButtonPressed)) {
                return buttonDownSprite->opaque(pos);
            }

            return buttonUpSprite->opaque(pos);
        }
    }
}
