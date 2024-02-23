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

        virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;

        virtual const std::vector<Ref<IVertexBuffer>>& GetVertexBuffers() const { return mVertexBuffers; }
        virtual const Ref<IIndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }
    private:
        uint32_t mRendererID;
        uint32_t mVertexBufferIndex = 0;

        std::vector<Ref<IVertexBuffer>> mVertexBuffers;
        Ref<IIndexBuffer> mIndexBuffer;
    };
}