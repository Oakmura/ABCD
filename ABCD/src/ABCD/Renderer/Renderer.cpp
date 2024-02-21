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

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<IVertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}