#include "abpch.h"
#include "Scene.h"

#include "Components.h"
#include "ABCD/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

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

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { mRegistry.create(), this };
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;

        return entity;
    }

    void Scene::OnUpdate(Timestep ts)
    {
        // Render 2D
        Camera* mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        {
            auto group = mRegistry.view<TransformComponent, CameraComponent>();
            for (auto entity : group)
            {
                auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    cameraTransform = &transform.Transform;
                    break;
                }
            }
        }

        if (mainCamera)
        {
            Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

            auto group = mRegistry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(transform, sprite.Color);
            }

            Renderer2D::EndScene();
        }
    }
}