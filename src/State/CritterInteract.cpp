#include <cstdio>
#include <memory>
#include "../State/CritterInteract.h"
#include "../Format/Lst/File.h"
#include "../Format/Lip/File.h"
#include "../Game/CritterObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/CritterDialog.h"
#include "../State/CritterDialogReview.h"
#include "../State/CritterBarter.h"
#include "../State/CursorDropdown.h"
#include "../State/Location.h"
#include "../UI/Image.h"
#include "../UI/Animation.h"
#include "../UI/AnimationFrame.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../Audio/Mixer.h"

namespace Falltergeist
{
    namespace State
    {
        using Point = Graphics::Point;

        CritterInteract::CritterInteract(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            Game::CritterObject* critter
        ) : State(mouse), _critter(critter), _resourceManager(resourceManager) {
            _dialog = new CritterDialog(_resourceManager, mouse);
            _review = new CritterDialogReview(_resourceManager, mouse);
            _barter = new CritterBarter(_resourceManager, mouse, critter);
            // pre-init review, so we can push questions/answers to it.
            _review->init();
        }

        CritterInteract::~CritterInteract()
        {
            auto camera = Game::Game::getInstance()->locationState()->camera();
            camera->setCenter(_oldCameraCenter);
            delete _dialog;
            delete _review;
            delete _barter;
        }

        void CritterInteract::onStateActivate(Event::State* event)
        {
            _previousCursor = mouse()->cursor();
            mouse()->setCursor(Input::Mouse::Cursor::BIG_ARROW);
            if (_headID >= 0) {
                // stop music completely
                // TODO: because Dialog state is activated *before* Interact, this stops speech too =/
                //Game::getInstance()->mixer()->stopMusic();
            } else {
                // lower music volume
                Game::Game::getInstance()->mixer()->setMusicVolume(Game::Game::getInstance()->mixer()->musicVolume()/2.0);
            }
        }

        void CritterInteract::onStateDeactivate(Event::State* event)
        {
            mouse()->setCursor(_previousCursor);
            if (_headID >= 0) {
                Game::Game::getInstance()->mixer()->playACMMusic(Game::Game::getInstance()->mixer()->lastMusic(), true);
            } else {
                // restore music volume
                Game::Game::getInstance()->mixer()->setMusicVolume(Game::Game::getInstance()->mixer()->musicVolume()*2.0);
            }
        }

        void CritterInteract::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            setPosition((Game::Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);

            if (backgroundID() >= 0 && headID() >= 0)
            {
                auto lst = ResourceManager::getInstance()->lstFileType("art/backgrnd/backgrnd.lst");
                std::string bgImage = "art/backgrnd/" + lst->strings()->at(backgroundID());
                auto bg = _resourceManager->getImage(bgImage);
                bg->setPosition({128, 15});
                addUI(bg);

                auto headlst = ResourceManager::getInstance()->lstFileType("art/heads/heads.lst");
                std::string headImage = headlst->strings()->at(headID());

                auto fidgets = headImage.substr(headImage.find(",") + 1);

                sscanf(fidgets.c_str(), "%d,%d,%d", &_goodFidgets, &_neutralFidgets, &_badFidgets);

                headImage=headImage.substr(0,headImage.find(","));

                _headName = headImage;

                _fidgetTimer.tickHandler().add([this](Event::Event* evt){
                    uint8_t fidget = rand() % 3 + 1;
                    auto headImage = _headName;
                    switch (_mood)
                    {
                        case CritterInteract::Mood::BAD:
                            headImage+="b";
                            break;
                        case CritterInteract::Mood::NEUTRAL:
                            headImage+="n";
                            break;
                        case CritterInteract::Mood::GOOD:
                            headImage+="g";
                            break;
                    }
                    headImage += "f" + std::to_string(fidget)+".frm";
                    auto head = dynamic_cast<UI::AnimationQueue*>(getUI("head"));
                    head->clear();
                    head->animations().push_back(std::make_unique<UI::Animation>("art/heads/" + headImage));

                    head->start();
                    _fidgetTimer.start(std::rand() % 5000 + 5000);

                });
                headImage+="gf1.frm";

                auto head = new UI::AnimationQueue();
                head->animations().push_back(std::make_unique<UI::Animation>("art/heads/" + headImage));

                int offset = 388/2 - head->currentAnimation()->size().width()/2;
                head->setPosition({128+offset, 15});
                addUI("head",head);
            }

            addUI("background", _resourceManager->getImage("art/intrface/alltlk.frm"));

            auto hilight1 = _resourceManager->getImage("data/hilight1.png");
            hilight1->setPosition({423, 20});
            addUI(hilight1);

            auto hilight2 = _resourceManager->getImage("data/hilight2.png");
            hilight2->setPosition({128, 84});
            addUI(hilight2);

            // Centering camera on critter position
            auto locationState = Game::Game::getInstance()->locationState();
            _oldCameraCenter = locationState->camera()->center();

            locationState->camera()->setCenter(critter()->hexagon()->position() + Point(0, 100));
        }

        int CritterInteract::backgroundID()
        {
            return _backgroundID;
        }

        void CritterInteract::setBackgroundID(int backgroundID)
        {
            _backgroundID = backgroundID;
        }

        int CritterInteract::headID()
        {
            return _headID;
        }

        void CritterInteract::setHeadID(int headID)
        {
            _headID = headID;
        }

        CritterInteract::Mood CritterInteract::mood()
        {
            return _mood;
        }

        void CritterInteract::setMood(Mood mood)
        {
            _mood = mood;
        }

        Game::CritterObject* CritterInteract::critter()
        {
            return _critter;
        }

        int CritterInteract::msgFileID()
        {
            return _msgFileID;
        }

        void CritterInteract::setMsgFileID(int value)
        {
            _msgFileID = value;
        }

        VM::Script* CritterInteract::script()
        {
            return _script;
        }

        void CritterInteract::setScript(VM::Script* script)
        {
            _script = script;
        }

        void CritterInteract::playSpeech(const std::string &speech)
        {
            _fidgetTimer.stop();
            Game::Game::getInstance()->mixer()->playACMSpeech(_headName+"/"+speech+".acm");
            // start timer
            _startTime = SDL_GetTicks();
            _nextIndex = 0;
            _phase = Phase::TALK;

            _lips = ResourceManager::getInstance()->lipFileType("sound/speech/"+_headName+"/"+speech+".lip");
            auto head = dynamic_cast<UI::AnimationQueue*>(getUI("head"));
            head->stop();
            head->clear();
            std::string headImage = _headName;
            switch (_mood)
            {
                case CritterInteract::Mood::BAD:
                    headImage+="b";
                    break;
                case CritterInteract::Mood::NEUTRAL:
                    headImage+="n";
                    break;
                case CritterInteract::Mood::GOOD:
                    headImage+="g";
                    break;
            }
            headImage+="p.frm";
            head->animations().push_back(std::make_unique<UI::Animation>("art/heads/" + headImage));
        }

        static inline int _phonemeToFrame(unsigned int phoneme)
        {
            static const int8_t frames[] = {0,3,1,1,3,1,1,1,7,8,7,3,1,8,1,7,7,6,6,2,2,2,2,4,4,5,5,2,2,2,2,2,6,2,2,5,8,2,2,2,2,8};
            if (phoneme<=41)
            {
                return frames[phoneme];
            }
            return 0;
        }

        void CritterInteract::think(const float &deltaTime)
        {
            State::think(deltaTime);

            // switch state
            switch (_phase)
            {
                case Phase::FIDGET:
                    _fidgetTimer.think(deltaTime);
                    break;
                case Phase::TALK:
                    // if playing speech - set phoneme frame


                    if (_nextIndex < _lips->phonemes().size() && SDL_GetTicks()-_startTime>=_lips->timestamps().at(_nextIndex))
                    {
                        //set frame
                        auto head = dynamic_cast<UI::AnimationQueue*>(getUI("head"));
                        head->currentAnimation()->setCurrentFrame(_phonemeToFrame(_lips->phonemes().at(_nextIndex)));
                        _nextIndex++;
                    }
                    if (SDL_GetTicks()-_startTime>= (_lips->acmSize()*1000 / 22050 /2))
                    {
                        _phase = Phase::FIDGET;
                        _fidgetTimer.start(0);
                    }
                    break;
                case Phase::TRANSITION:
                    break;
            }
        }

        CritterDialog* CritterInteract::dialog()
        {
            return _dialog;
        }

        CritterDialogReview* CritterInteract::dialogReview()
        {
            return _review;
        }

        CritterBarter* CritterInteract::barter()
        {
            return _barter;
        }

        void CritterInteract::switchSubState(CritterInteract::SubState state)
        {
            Game::Game::getInstance()->mixer()->stopMusic();
            _phase = Phase::FIDGET;
            _fidgetTimer.start(0);
            if (_state!=SubState::NONE)
            {
                Game::Game::getInstance()->popState(false);
            }
            _state = state;
            switch (state)
            {
                case SubState::DIALOG:
                    Game::Game::getInstance()->pushState(_dialog);
                    break;
                case SubState::BARTER:
                    Game::Game::getInstance()->pushState(_barter);
                    break;
                case SubState::REVIEW:
                    Game::Game::getInstance()->pushState(_review);
                    break;
                default:
                    break;
            }
        }


        void CritterInteract::transition(Reaction reaction)
        {
            Game::Game::getInstance()->mixer()->stopMusic();
            auto newmood = _mood;

            if (headID()!= -1)
            {

                switch (reaction)
                {
                    case Reaction::BAD:
                        switch (_mood)
                        {
                            case Mood::NEUTRAL:
                                newmood = Mood::BAD;
                                break;
                            case Mood::GOOD:
                                newmood = Mood::NEUTRAL;
                                break;
                            case Mood::BAD:
                                break;
                        }
                        break;
                    case Reaction::GOOD:
                        switch (_mood)
                        {
                            case Mood::NEUTRAL:
                                newmood = Mood::GOOD;
                                break;
                            case Mood::GOOD:
                                break;
                            case Mood::BAD:
                                newmood = Mood::NEUTRAL;
                                break;
                        }
                        break;
                    case Reaction::NEUTRAL:
                        // neutral answers doesn't affect mood
                        break;
                }

            }
            if (headID()!=-1 && newmood != _mood)
            {

                auto head = dynamic_cast<UI::AnimationQueue *>(getUI("head"));
                std::string headImage = _headName;
                switch (_mood)
                {
                    case Mood::BAD:
                        headImage+="b";
                        break;
                    case Mood::NEUTRAL:
                        headImage+="n";
                        break;
                    case Mood::GOOD:
                        headImage+="g";
                        break;
                }

                switch (newmood)
                {
                    case Mood::BAD:
                        headImage+="b";
                        break;
                    case Mood::NEUTRAL:
                        headImage+="n";
                        break;
                    case Mood::GOOD:
                        headImage+="g";
                        break;
                }

                _mood = newmood;
                headImage += ".frm";
                if (_phase == Phase::TALK)
                {
                    head->stop();
                    head->animations().clear();
                }
                _phase = Phase::TRANSITION;
                head->animations().push_back(std::make_unique<UI::Animation>("art/heads/" + headImage));
                head->animationEndedHandler().add(std::bind(&CritterInteract::onMoodTransitionEnded, this, std::placeholders::_1));
                head->start();
            }
            else
            {
                script()->run();
            }
        }


        void CritterInteract::onMoodTransitionEnded(Event::Event *event)
        {
            auto head = dynamic_cast<UI::AnimationQueue *>(getUI("head"));
            head->animationEndedHandler().clear();
            script()->run();
        }
    }
}
