#pragma once

#include "ABCD/Renderer/IBuffer.h"

namespace abcd 
{
    class OpenGLVertexBuffer : public IVertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return mLayout; }
        virtual void SetLayout(const BufferLayout& layout) override { mLayout = layout; }
    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

    class OpenGLIndexBuffer : public IIndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

        virtual uint32_t GetCount() const { return mCount; }
    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };

}