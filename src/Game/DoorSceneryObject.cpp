#include "../Game/DoorSceneryObject.h"
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace Game
    {
        DoorSceneryObject::DoorSceneryObject(std::shared_ptr<ILogger> logger) : SceneryObject()
        {
            this->logger = std::move(logger);
            _subtype = Subtype::DOOR;
        }

        bool DoorSceneryObject::opened() const
        {
            return _opened;
        }

        void DoorSceneryObject::setOpened(bool value)
        {
            // Don't change if door is locked.
            if (!_locked) {
                _opened = value;
                setCanLightThru(_opened);

                if (auto queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                    queue->currentAnimation()->setReverse(value);
                }
            }
        }

        bool DoorSceneryObject::locked() const
        {
            return _locked;
        }

        void DoorSceneryObject::setLocked(bool value)
        {
            _locked = value;
        }

        void DoorSceneryObject::use_p_proc(CritterObject* usedBy)
        {
            Object::use_p_proc(usedBy);
            if (script() && script()->overrides()) {
                return;
            }

            if (!_locked) {
                if (!opened()) {
                    if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                        queue->start();
                        queue->animationEndedHandler().add([=](Event::Event*) { onOpeningAnimationEnded(queue); });
                        if (_soundId) {
                            Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/sodoors") + _soundId + ".acm");
                        }
                    }
                } else {
                    if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                        queue->start();
                        queue->animationEndedHandler().add([=](Event::Event*) { onClosingAnimationEnded(queue); });
                        if (_soundId) {
                            Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/scdoors") + _soundId + ".acm");
                        }
                    }
                }
            } else if (_soundId) {
                Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/sldoors") + _soundId + ".acm");
            }
        }

        bool DoorSceneryObject::canWalkThru() const
        {
            return opened();
        }

        void DoorSceneryObject::onOpeningAnimationEnded(UI::AnimationQueue* target)
        {
            setOpened(true);
            target->animationEndedHandler().clear();
            target->stop();
            target->currentAnimation()->setReverse(true);
            Game::getInstance()->locationState()->initLight();
            Logger::info("") << "Door opened: " << opened() << std::endl;
        }

        void DoorSceneryObject::onClosingAnimationEnded(UI::AnimationQueue* target)
        {
            setOpened(false);
            target->animationEndedHandler().clear();
            target->stop();
            target->currentAnimation()->setReverse(false);
            Game::getInstance()->locationState()->initLight();
            Logger::info("") << "Door opened: " << opened() << std::endl;
        }
    }
}
