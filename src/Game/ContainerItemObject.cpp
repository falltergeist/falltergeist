// Project includes
#include "../Game/ContainerItemObject.h"
#include "../Game/Game.h"
#include "../State/Container.h"
#include "../UI/ResourceManager.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        ContainerItemObject::ContainerItemObject() : ItemObject()
        {
            _subtype = Subtype::CONTAINER;
        }

        std::vector<ItemObject*>* ContainerItemObject::inventory()
        {
            return &_inventory;
        }

        void ContainerItemObject::use_p_proc(CritterObject* usedBy)
        {
            auto state = new State::Container(std::make_shared<UI::ResourceManager>());
            state->setObject(this);
            Game::getInstance()->pushState(state);
        }

        void ContainerItemObject::setLocked(bool locked)
        {
            this->_locked = locked;
        }

        bool ContainerItemObject::locked() const
        {
            return _locked;
        }

        void ContainerItemObject::setOpened(bool opened)
        {
            this->_opened = opened;
        }

        bool ContainerItemObject::opened() const
        {
            return _opened;
        }
    }
}
