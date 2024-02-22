#pragma once

#include "ABCD/Renderer/IVertexArray.h"

namespace abcd 
{
    class OpenGLVertexArray : public IVertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const { return mVertexBuffers; }
        virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }
    private:
        uint32_t mRendererID;
        uint32_t mVertexBufferIndex = 0;

        std::vector<std::shared_ptr<IVertexBuffer>> mVertexBuffers;
        std::shared_ptr<IIndexBuffer> mIndexBuffer;
    };
}