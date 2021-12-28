#include "../UI/ImageButton.h"
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../ResourceManager.h"

namespace Falltergeist {
    namespace UI {
        ImageButton::ImageButton(const Point& pos, std::shared_ptr<Graphics::Sprite> buttonUpSprite,
                                 std::shared_ptr<Graphics::Sprite> buttonDownSprite, std::string buttonUpSoundFilename,
                                 std::string buttonDownSoundFilename, bool checkBoxMode)
            : Base(pos), _checkboxMode(checkBoxMode), _buttonDownSoundFilename(buttonDownSoundFilename),
              _buttonUpSoundFilename(buttonUpSoundFilename), _buttonUpSprite(buttonUpSprite), _buttonDownSprite(buttonDownSprite) {
            mouseClickHandler().add([=](Event::Mouse*) { _onMouseClick(); });
            mouseDownHandler().add([=](Event::Mouse* event) { _onMouseDown(event); });
        }

        void ImageButton::_onMouseClick() {
            if (!_enabled) {
                return;
            }
            if (_checkboxMode) {
                _checked = !_checked;
            }
            if (!_buttonUpSoundFilename.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(_buttonUpSoundFilename);
            }
        }

        void ImageButton::_onMouseDown(Event::Mouse* event) {
            if (!event->leftButton() || !_enabled) {
                return;
            }

            if (!_buttonDownSoundFilename.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(_buttonDownSoundFilename);
            }
        }

        bool ImageButton::checked() {
            return _checked;
        }

        void ImageButton::setChecked(bool checked) {
            _checked = checked;
        }

        bool ImageButton::enabled() {
            return _enabled;
        }

        void ImageButton::setEnabled(bool enabled) {
            _enabled = enabled;
        }

        void ImageButton::handle(Event::Mouse* mouseEvent) {
            if (!_enabled) {
                return;
            }
            // disable right button clicks
            _rightButtonPressed = false;
            Base::handle(mouseEvent);
        }

        void ImageButton::render(bool eggTransparency) {
            if (!_enabled) {
                return;
            }
            if ((_checkboxMode && _checked) || (_leftButtonPressed)) {
                _buttonDownSprite->render(position());
                return;
            }

            _buttonUpSprite->render(position());
        }

        bool ImageButton::opaque(const Point& pos) {
            if ((_checkboxMode && _checked) || (_hovered && _leftButtonPressed)) {
                return _buttonDownSprite->opaque(pos);
            }

            return _buttonUpSprite->opaque(pos);
        }
    }
}
