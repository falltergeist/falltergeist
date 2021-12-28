#include "../UI/AnimationQueue.h"
#include "../Event/Event.h"
#include "../UI/Animation.h"
#include <memory>

namespace Falltergeist {
    namespace UI {
        AnimationQueue::AnimationQueue() : Base(Point(0, 0)) {
        }

        std::vector<std::unique_ptr<Animation>>& AnimationQueue::animations() {
            return _animations;
        }

        void AnimationQueue::clear() {
            _currentAnimation = 0;
            _playing = false;
            _repeat = false;
            _animations.clear();
        }

        void AnimationQueue::stop() {
            _playing = false;
            _currentAnimation = 0;
            currentAnimation()->stop();
        }

        void AnimationQueue::start() {
            _playing = true;
        }

        void AnimationQueue::setRepeat(bool value) {
            _repeat = value;
        }

        void AnimationQueue::render(bool eggTransparency) {
            currentAnimation()->setLightLevel(_lightLevel);
            currentAnimation()->setLight(light());
            currentAnimation()->setTrans(_trans);
            currentAnimation()->setPosition(position() + offset());
            currentAnimation()->render(eggTransparency);
        }

        void AnimationQueue::think(const float& deltaTime) {
            if (_playing) {
                if (currentAnimation()->ended()) {
                    // not last animation in queue
                    if (_currentAnimation < _animations.size() - 1) {
                        _currentAnimation++;
                        currentAnimation()->stop(); // rewind
                        currentAnimation()->play();
                    } else {
                        if (!_repeat) {
                            emitEvent(std::make_unique<Event::Event>("animationEnded"), animationEndedHandler());
                            currentAnimation()->stop();
                            _playing = false;
                            return;
                        } else {
                            _currentAnimation = 0;
                            currentAnimation()->stop();
                            currentAnimation()->play();
                        }
                    }
                } else if (!currentAnimation()->playing()) {
                    currentAnimation()->play();
                }

                currentAnimation()->think(deltaTime);
            }
        }

        Animation* AnimationQueue::currentAnimation() const {
            return _animations.at(_currentAnimation).get();
        }

        const Size& AnimationQueue::size() const {
            return currentAnimation()->size();
        }

        const Point& AnimationQueue::offset() const {
            return currentAnimation()->offset();
        }

        Event::Handler& AnimationQueue::animationEndedHandler() {
            return _animationEndedHandler;
        }

        bool AnimationQueue::opaque(const Point& pos) {
            currentAnimation()->setPosition(this->position());
            return currentAnimation()->opaque(pos);
        }
    }
}
