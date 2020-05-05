#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <memory>
#include "../Game/Component/Component.h"

namespace Falltergeist
{
    namespace Game
    {
        constexpr uint32_t maxComponents = 32;

        typedef std::bitset<maxComponents> ComponentBitset;

        typedef std::array<std::shared_ptr<Component::Component>, maxComponents> ComponentArray;

        class Entity
        {
            public:
                virtual ~Entity() = default;

                template <typename T> bool hasComponent()
                {
                    return _componentBitset.test(Component::getComponentId<T>());
                }

                template <typename T> void removeComponent()
                {
                    _componentArray.at(Component::getComponentId<T>()).reset();
                    _componentBitset.reset(Component::getComponentId<T>());
                }

                template <typename T> void addComponent(const std::shared_ptr<Component::Component> &component)
                {
                    component->setEntity(this);
                    _componentArray.at(Component::getComponentId<T>()) = component;
                    _componentBitset.set(Component::getComponentId<T>()) = true;
                }

                template <typename T> std::shared_ptr<T> getComponent() const
                {
                    return std::static_pointer_cast<T>(_componentArray.at(Component::getComponentId<T>()));
                }

            private:
                ComponentArray _componentArray;
                ComponentBitset _componentBitset;
        };
    }
}
