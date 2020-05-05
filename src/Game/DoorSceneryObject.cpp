#include "../Game/Component/Lockable.h"
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
        DoorSceneryObject::DoorSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::DOOR;
        }

        bool DoorSceneryObject::opened() const
        {
            return getComponent<Component::Lockable>()->isOpened();
        }

        void DoorSceneryObject::setOpened(bool value)
        {
            auto lockable = getComponent<Component::Lockable>();
            // Don't change if door is locked.
            if (!lockable->isLocked()) {
                value ? lockable->open() : lockable->close();
                setCanLightThru(value);

                if (auto queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                    queue->currentAnimation()->setReverse(value);
                }
            }
        }

        void DoorSceneryObject::use_p_proc(CritterObject* usedBy)
        {
            Object::use_p_proc(usedBy);
            if (script() && script()->overrides()) {
                return;
            }

            if (!opened()) {
                if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                    queue->start();
                    queue->animationEndedHandler().add(std::bind(&DoorSceneryObject::onOpeningAnimationEnded, this, std::placeholders::_1));
                    if (_soundId) {
                        Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/sodoors") + _soundId + ".acm");
                    }
                }
            } else {
                if (UI::AnimationQueue* queue = dynamic_cast<UI::AnimationQueue*>(this->ui())) {
                    queue->start();
                    queue->animationEndedHandler().add(std::bind(&DoorSceneryObject::onClosingAnimationEnded, this, std::placeholders::_1));
                    if (_soundId) {
                        Game::getInstance()->mixer()->playACMSound(std::string("sound/sfx/scdoors") + _soundId + ".acm");
                    }
                }
            }
        }

        bool DoorSceneryObject::canWalkThru() const
        {
            return getComponent<Component::Lockable>()->isOpened();
        }

        void DoorSceneryObject::onOpeningAnimationEnded(Event::Event* event)
        {
            auto queue = (UI::AnimationQueue*)event->target();
            setOpened(true);
            queue->animationEndedHandler().clear();
            queue->stop();
            queue->currentAnimation()->setReverse(true);
            Game::getInstance()->locationState()->initLight();
            Logger::info() << "Door opened: " << opened() << std::endl;
        }

        void DoorSceneryObject::onClosingAnimationEnded(Event::Event* event)
        {
            auto queue = (UI::AnimationQueue*)event->target();
            setOpened(false);
            queue->animationEndedHandler().clear();
            queue->stop();
            queue->currentAnimation()->setReverse(false);
            Game::getInstance()->locationState()->initLight();
            Logger::info() << "Door opened: " << opened() << std::endl;
        }
    }
}
