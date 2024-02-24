#include "abpch.h"

#include "ABCD/Renderer/Renderer.h"
#include "ABCD/Renderer/Renderer2D.h"

namespace abcd 
{
    Scope<Renderer::SceneData> Renderer::sSceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        AB_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        sSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();

        shader->SetMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}