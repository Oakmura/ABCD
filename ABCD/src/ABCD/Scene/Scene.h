#pragma once

#include "ABCD/Core/Timestep.h"
#include "ABCD/Renderer/EditorCamera.h"

#include "entt.hpp"

namespace abcd 
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());
        void DestroyEntity(Entity entity);

        void OnUpdateRuntime(Timestep ts);
        void OnUpdateEditor(Timestep ts, EditorCamera& camera);
        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();
    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);

    private:
        entt::registry mRegistry;
        uint32_t mViewportWidth = 0, mViewportHeight = 0;

        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    };
}