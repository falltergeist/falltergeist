#include <cmath>
#include <cstdio>
#include <memory>
#include "../Exception.h"
#include "../Format/Frm/File.h"
#include "../Format/Msg/File.h"
#include "../Format/Msg/Message.h"
#include "../functions.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../Game/CritterObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/Helper/EggHelper.h"
#include "../Game/Object.h"
#include "../Graphics/ObjectUIFactory.h"
#include "../PathFinding/HexagonGrid.h"
#include "../LocationCamera.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        Object::Object() : Event::EventTarget(Game::getInstance()->eventDispatcher())
        {
        }

        Object::Type Object::type() const
        {
            return _type;
        }

        int Object::PID() const
        {
            return _PID;
        }

        void Object::setPID(int value)
        {
            _PID = value;
        }

        int Object::FID() const {
            return _FID;
        }

        void Object::setFID(int value)
        {
            if (_FID == value) {
                return;
            }
            _FID = value;
            _generateUi();
        }

        int Object::SID() const
        {
            return _SID;
        }

        void Object::setSID(int value)
        {
            _SID = value;
        }

        int Object::elevation() const
        {
            return _elevation;
        }

        void Object::setElevation(int value)
        {
            if (value < 0 || value > 3) {
                throw Exception("Object::setElevation() - value out of range: " + std::to_string(value));
            }
            _elevation = value;
        }

        Orientation Object::orientation() const
        {
            return _orientation;
        }

        void Object::setOrientation(Orientation value)
        {
            if (_orientation == value) {
                return;
            }

            _orientation = value;
            _generateUi();
        }

        std::string Object::name() const
        {
            return _name;
        }

        void Object::setName(const std::string &value)
        {
            _name = value;
        }

        std::string Object::scrName() const
        {
            return _scrName;
        }

        void Object::setScrName(const std::string &value)
        {
            _scrName = value;
        }

        std::string Object::description() const
        {
            return _description;
        }

        void Object::setDescription(const std::string &value)
        {
            _description = value;
        }

        VM::Script *Object::script() const
        {
            return _script.get();
        }

        void Object::setScript(VM::Script *script)
        {
            _script.reset(script);
        }

        UI::Base *Object::ui() const
        {
            return _ui.get();
        }

        void Object::_generateUi()
        {
            Graphics::ObjectUIFactory uiFactory;
            _ui = uiFactory.buildByFID(FID(), orientation());
        }

        bool Object::canWalkThru() const
        {
            return _canWalkThru;
        }

        void Object::setCanWalkThru(bool value)
        {
            _canWalkThru = value;
        }

        bool Object::canLightThru() const
        {
            return _canLightThru;
        }

        void Object::setCanLightThru(bool value)
        {
            _canLightThru = value;
        }

        bool Object::canShootThru() const
        {
            return _canShootThru;
        }

        void Object::setCanShootThru(bool value)
        {
            _canShootThru = value;
        }

        bool Object::wallTransEnd() const
        {
            return _wallTransEnd;
        }

        void Object::setWallTransEnd(bool value)
        {
            _wallTransEnd = value;
        }

        Hexagon *Object::hexagon() const
        {
            if (this->position() < 0) {
                return nullptr;
            }

            return Game::getInstance()->locationState()->hexagonGrid()->at(this->position());
        }

        void Object::setHexagon(Hexagon *hexagon)
        {
            setPosition(hexagon->number());
        }

        UI::TextArea *Object::floatMessage() const
        {
            return _floatMessage.get();
        }

        void Object::setFloatMessage(std::unique_ptr<UI::TextArea> message)
        {
            _floatMessage = std::move(message);
        }

        void Object::renderText()
        {
            auto message = floatMessage();
            if (!message) {
                return;
            }
            if (SDL_GetTicks() - message->timestampCreated() >= 7000) {
                setFloatMessage(nullptr);
            } else {
                message->setPosition(_ui->position() + Point(
                        _ui->size().width() / 2 - message->size().width() / 2,
                        -4 - message->textSize().height()
                ));
                message->render();
            }
        }

        void Object::render()
        {
            if (!_ui || !hexagon()) {
                return;
            }

            auto camera = Game::getInstance()->locationState()->camera();
            _ui->setPosition(
                hexagon()->position()
                - camera->topLeft()
                - Point(_ui->size().width() / 2, _ui->size().height())
            );

            // don't draw if outside of screen
            if (!Graphics::Rect::intersects(_ui->position(), _ui->size(), Point(0, 0), camera->size())) {
                setInRender(false);
                return;
            }

            setInRender(true);
            _ui->setLight(true);
            _ui->setLightLevel(hexagon()->light());

            static Helper::EggHelper eggHelper; // TODO remove it when render logic is extracted from object
            _ui->render(eggHelper.isTransparentForEgg(this, Game::getInstance()->player()));
        }

        void Object::think(const float &deltaTime)
        {
            if (_ui) {
                _ui->think(deltaTime);
            }
        }

        void Object::handle(Event::Event *event)
        {
            if (_ui) {
                _ui->handle(event);
            }
        }

        bool Object::inRender() const
        {
            return _inRender;
        }

        void Object::setInRender(bool value)
        {
            _inRender = value;
        }

        void Object::description_p_proc()
        {
            Logger::info("SCRIPT") << "description_p_proc() - 0x" << std::hex << PID() << " " << name() << " "
                                   << (script() ? script()->filename() : "") << std::endl;
            bool useDefault = true;
            if (script() && script()->hasFunction("description_p_proc")) {
                script()
                        ->setSourceObject(Game::getInstance()->player().get())
                        ->call("description_p_proc");
                if (script()->overrides()) {
                    useDefault = false;
                }
            }
            if (useDefault) {
                auto descr = description();
                if (descr.empty()) {
                    descr = _t(MSG_TYPE::MSG_PROTO, 493);
                }
                Game::getInstance()->locationState()->displayMessage(descr);
            }
        }

        void Object::use_p_proc(CritterObject *usedBy)
        {
            if (script() && script()->hasFunction("use_p_proc")) {
                script()
                        ->setSourceObject(usedBy)
                        ->call("use_p_proc");
            }
        }

        void Object::destroy_p_proc()
        {
            if (script() && script()->hasFunction("destroy_p_proc")) {
                script()
                        ->setSourceObject(Game::getInstance()->player().get())
                        ->call("destroy_p_proc");
            }
        }

        void Object::look_at_p_proc()
        {
            bool useDefault = true;
            if (script() && script()->hasFunction("look_at_p_proc")) {
                script()
                        ->setSourceObject(Game::getInstance()->player().get())
                        ->call("look_at_p_proc");
                if (script()->overrides()) {
                    useDefault = false;
                }
            }
            if (useDefault) {
                auto protoMsg = ResourceManager::getInstance()->msgFileType("text/english/game/proto.msg");
                char buf[512];
                sprintf(buf, protoMsg->message(490)->text().c_str(), name().c_str());
                Game::getInstance()->locationState()->displayMessage(std::string(buf));
            }
        }

        void Object::map_enter_p_proc()
        {
            if (script()) {
                script()->call("map_enter_p_proc");
            }
        }

        void Object::map_exit_p_proc()
        {
            if (script()) {
                script()->call("map_exit_p_proc");
            }
        }

        void Object::map_update_p_proc()
        {
            if (script()) {
                script()->call("map_update_p_proc");
            }
        }

        void Object::pickup_p_proc(CritterObject *pickedUpBy)
        {
            if (script() && script()->hasFunction("pickup_p_proc")) {
                script()
                        ->setSourceObject(pickedUpBy)
                        ->call("pickup_p_proc");
            }
            // @TODO: standard handler
        }

        void Object::use_obj_on_p_proc(Object *objectUsed, CritterObject *usedBy)
        {
            if (script() && script()->hasFunction("use_obj_on_p_proc")) {
                script()
                        ->setSourceObject(usedBy)
                        ->setTargetObject(objectUsed)
                        ->call("use_obj_on_p_proc");
            }
            // @TODO: standard handlers for drugs, etc.
        }

        void Object::use_skill_on_p_proc(SKILL skill, Object *objectUsed, CritterObject *usedBy)
        {
            if (script() && script()->hasFunction("use_skill_on_p_proc")) {
                script()
                        ->setSourceObject(usedBy)
                        ->setTargetObject(objectUsed)
                        ->setUsedSkill(skill)
                        ->call("use_skill_on_p_proc");
            }
            // @TODO: standard handlers
        }

        void Object::onUseAnimationActionFrame(Event::Event *event, CritterObject *critter)
        {
            use_p_proc(critter);
            auto animation = dynamic_cast<UI::Animation *>(critter->ui());
            if (animation) {
                animation->actionFrameHandler().clear();
                animation->animationEndedHandler().add([this, critter](Event::Event *event) {
                    this->onUseAnimationEnd(event, critter);
                });
            } else {
                throw Exception("No animation for object!");
            }
        }

        void Object::onUseAnimationEnd(Event::Event *event, CritterObject *critter)
        {
            critter->setActionAnimation("aa")->stop();
        }

        void Object::setTrans(Graphics::TransFlags::Trans value)
        {
            _trans = value;
            if (_ui) {
                _ui->setTrans(value);
            }
        }

        Graphics::TransFlags::Trans Object::trans() const
        {
            return _trans;
        }

        void Object::setLightOrientation(Orientation orientation)
        {
            _lightOrientation = orientation;
        }

        unsigned short Object::lightOrientation() const
        {
            return _lightOrientation;
        }

        void Object::setLightIntensity(unsigned int intensity)
        {
            _lightIntensity = intensity;
        }

        unsigned int Object::lightIntensity() const
        {
            return _lightIntensity;
        }

        void Object::setLightRadius(unsigned int radius)
        {
            _lightRadius = radius;
        }

        unsigned int Object::lightRadius() const
        {
            return _lightRadius;
        }

        void Object::setFlags(unsigned int flags)
        {
            setFlat((flags & 0x00000008));
            setCanWalkThru((flags & 0x00000010));
            setCanLightThru((flags & 0x20000000));
            setCanShootThru((flags & 0x80000000));

            if (flags & 0x00004000) {
                setTrans(Graphics::TransFlags::Trans::RED);
            }
            if (flags & 0x00008000) {
                setTrans(Graphics::TransFlags::Trans::NONE);
            }
            if (flags & 0x00010000) {
                setTrans(Graphics::TransFlags::Trans::WALL);
            }
            if (flags & 0x00020000) {
                setTrans(Graphics::TransFlags::Trans::GLASS);
            }
            if (flags & 0x00040000) {
                setTrans(Graphics::TransFlags::Trans::STEAM);
            }
            if (flags & 0x00080000) {
                setTrans(Graphics::TransFlags::Trans::ENERGY);
            }
            if (flags & 0x10000000) {
                setWallTransEnd(true);
            }
        }

        bool Object::flat() const
        {
            return _flat;
        }

        void Object::setFlat(bool value)
        {
            _flat = value;
        }

        unsigned int Object::defaultFrame()
        {
            return _defaultFrame;
        }

        void Object::setDefaultFrame(unsigned int frame)
        {
            _defaultFrame = frame;
            if (_ui) {
                if (auto anim = dynamic_cast<UI::AnimationQueue *>(_ui.get())) {
                    anim->currentAnimation()->setCurrentFrame(_defaultFrame);
                }
            }
        }

        void Object::renderOutline(int type)
        {
            if (!_ui || !hexagon()) {
                return;
            }

            auto camera = Game::getInstance()->locationState()->camera();
            _ui->setPosition(
                    hexagon()->position()
                    - camera->topLeft()
                    - Point(_ui->size().width() / 2, _ui->size().height())
            );

            // don't draw if outside of screen
            if (!Graphics::Rect::intersects(_ui->position(), _ui->size(), Point(0, 0), camera->size())) {
                setInRender(false);
                return;
            }

            _ui->setOutline(type);
            _ui->render(false);
            _ui->setOutline(0);
        }

        int Object::position() const
        {
            return _position;
        }

        void Object::setPosition(int position)
        {
            _position = position;
        }
    }
}
