#pragma once

#include "ABCD/Renderer/IRendererAPI.h"

namespace abcd 
{
    class OpenGLRendererAPI : public IRendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        void OpenGLRendererAPI::DrawIndexed(const Ref<IVertexArray>& vertexArray, uint32_t indexCount);
    };
}