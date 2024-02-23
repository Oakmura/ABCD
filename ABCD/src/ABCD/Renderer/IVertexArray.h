#pragma once

#include <memory>
#include "ABCD/Renderer/IBuffer.h"

namespace abcd 
{
    class IVertexArray
    {
    public:
        virtual ~IVertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<IVertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IIndexBuffer>& GetIndexBuffer() const = 0;

        static Ref<IVertexArray> Create();
    };

}