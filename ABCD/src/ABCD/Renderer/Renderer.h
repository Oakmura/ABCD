#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "IShader.h"

namespace abcd 
{
    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<IShader>& shader, const std::shared_ptr<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* sSceneData;
    };
}