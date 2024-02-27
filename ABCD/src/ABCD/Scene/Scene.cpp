#include "abpch.h"
#include "Scene.h"

#include "Components.h"
#include "ABCD/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace abcd
{
    static void DoMath(const glm::mat4& transform)
    {

    }

    static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
    {

    }

    Scene::Scene()
    {
#if ENTT_EXAMPLE_CODE
        entt::entity entity = mRegistry.create();
        mRegistry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

        mRegistry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


        if (mRegistry.has<TransformComponent>(entity))
            TransformComponent& transform = mRegistry.get<TransformComponent>(entity);


        auto view = mRegistry.view<TransformComponent>();
        for (auto entity : view)
        {
            TransformComponent& transform = view.get<TransformComponent>(entity);
        }

        auto group = mRegistry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto entity : group)
        {
            auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
        }
#endif
    }

    Scene::~Scene()
    {
    }

    entt::entity Scene::CreateEntity()
    {
        return mRegistry.create();
    }

    void Scene::OnUpdate(Timestep ts)
    {
        auto group = mRegistry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }
    }
}