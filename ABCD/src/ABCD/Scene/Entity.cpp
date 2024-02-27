#include "abpch.h"
#include "Entity.h"

namespace abcd
{
    Entity::Entity(entt::entity handle, Scene* scene)
        : mEntityHandle(handle), mScene(scene)
    {
    }
}