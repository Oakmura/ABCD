#pragma once

#include "Scene.h"

#include "entt.hpp"

namespace abcd 
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            AB_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
            T& component = mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
            mScene->OnComponentAdded<T>(*this, component);
            return component;
        }

        template<typename T>
        T& GetComponent()
        {
            AB_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
            return mScene->mRegistry.get<T>(mEntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            // #TODO consider changing it to any_of?
            return mScene->mRegistry.all_of<T>(mEntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            AB_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
            mScene->mRegistry.remove<T>(mEntityHandle);
        }

        operator bool() const { return mEntityHandle != entt::null; }
        operator entt::entity() const { return mEntityHandle; }
        operator uint32_t() const { return (uint32_t)mEntityHandle; }

        bool operator==(const Entity& other) const
        {
            return mEntityHandle == other.mEntityHandle && mScene == other.mScene;
        }

        bool operator!=(const Entity& other) const
        {
            return !(*this == other);
        }
    private:
        entt::entity mEntityHandle{ entt::null };
        Scene* mScene = nullptr;
    };
}