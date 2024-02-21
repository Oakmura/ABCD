#include "abpch.h"
#include "Renderer.h"

namespace abcd 
{
    Renderer::SceneData* Renderer::sSceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        sSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<IVertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}