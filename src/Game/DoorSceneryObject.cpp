// Project includes
#include "../Game/DoorSceneryObject.h"
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        DoorSceneryObject::DoorSceneryObject(std::shared_ptr<ILogger> logger) : SceneryObject()
        {
            this->logger = std::move(logger);
            _subtype = Subtype::DOOR;
        }

        bool DoorSceneryObject::closed() const
        {
            return _closed;
        }

        void DoorSceneryObject::open() {
            if (locked()) {
                return;
            }

            _closed = false;
            setCanLightThru(!closed());

            if (auto queue = ui<UI::AnimationQueue>()) {
                queue->currentAnimation()->setReverse(!closed());
            }
        }

        void DoorSceneryObject::close()
        {
            if (locked()) {
                return;
            }

            _closed = true;
            setCanLightThru(!closed());

            if (auto queue = ui<UI::AnimationQueue>()) {
                queue->currentAnimation()->setReverse(!closed());
            }
        }

        bool DoorSceneryObject::locked() const {
            return _locked;
        }

        void DoorSceneryObject::lock() {
            _locked = true;
        }

        void DoorSceneryObject::unlock() {
            _locked = false;
        }

        void DoorSceneryObject::use_p_proc(CritterObject* usedBy)
        {
            Object::use_p_proc(usedBy);
            if (script() && script()->overrides()) {
                return;
            }

            if (!locked()) {
                if (closed()) {
                    if (auto queue = ui<UI::AnimationQueue>()) {
                        queue->start();
                        queue->animationEndedHandler().add([=](Event::Event*) { onOpeningAnimationEnded(queue); });
                        if (_soundId) {
                            Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/sodoors") + _soundId + ".acm");
                        }
                    }
                } else {
                    if (auto queue = ui<UI::AnimationQueue>()) {
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
            return !closed();
        }

        void DoorSceneryObject::onOpeningAnimationEnded(std::shared_ptr<UI::AnimationQueue> target)
        {
            open();
            target->animationEndedHandler().clear();
            target->stop();
            target->currentAnimation()->setReverse(true);
            Game::getInstance()->locationState()->initLight();
            Logger::info("") << "Door closed: " << closed() << std::endl;
        }

        void DoorSceneryObject::onClosingAnimationEnded(std::shared_ptr<UI::AnimationQueue> target)
        {
            close();
            target->animationEndedHandler().clear();
            target->stop();
            target->currentAnimation()->setReverse(false);
            Game::getInstance()->locationState()->initLight();
            Logger::info("") << "Door closed: " << closed() << std::endl;
        }
    }
}
