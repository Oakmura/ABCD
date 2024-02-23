#pragma once

#include "ABCD/Renderer/RenderCommand.h"

#include "ABCD/Renderer/OrthographicCamera.h"
#include "ABCD/Renderer/IShader.h"

namespace abcd 
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> sSceneData;
    };
}