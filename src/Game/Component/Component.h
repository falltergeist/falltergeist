#pragma once

#include <cstdint>
#include <memory>

namespace Falltergeist
{
    namespace Game
    {
        class Entity;

        namespace Component
        {
            typedef uint32_t ComponentID;

            inline ComponentID getNextComponentId()
            {
                static ComponentID lastId = 0;
                // TODO check max components
                return lastId++;
            }

            template <typename T> inline ComponentID getComponentId()
            {
                static ComponentID typeComponentId = getNextComponentId();
                return typeComponentId;
            }

            class Component
            {
                public:
                    virtual ~Component() = default;

                    Entity* getEntity() const;
                    void setEntity(Entity* entity);

                private:
                    Entity* _entity = nullptr;
            };
        }
    }
}
