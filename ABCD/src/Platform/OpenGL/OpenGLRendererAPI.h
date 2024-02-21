#pragma once

#include "ABCD/Renderer/RendererAPI.h"

namespace abcd 
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray) override;
    };
}